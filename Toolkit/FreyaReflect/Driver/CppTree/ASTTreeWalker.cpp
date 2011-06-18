/* File         : FreyaReflectBinary: ASTTreeWalker.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "CppTree/ASTTreeWalker.h"

#include "CppTree/CppNode.h"
#include "CppTree/CppType.h"
#include "CppTree/CppTree.h"

#include <clang/AST/DeclTemplate.h>

#include <boost/algorithm/string.hpp>

#include <llvm/Support/FileSystem.h>

using namespace clang;

class treewalk_exception : public std::exception
{
	const char * m_ExceptionMsg; 
public:
	treewalk_exception(const char* exception) throw() : m_ExceptionMsg ( m_ExceptionMsg ) {}
  	virtual const char* what() const throw() { return m_ExceptionMsg; }

};

ASTTreeWalker::ASTTreeWalker() : clang::ASTConsumer(), tree_ptr(new CppTree) 
{ 
	m_RootNode  = tree_ptr->getRootNode();
	node_stack.push(m_RootNode);
	decl_stack.push(NULL);
}


void ASTTreeWalker::HandleTopLevelDecl( clang::DeclGroupRef d )
{
	
	for(DeclGroupRef::iterator it = d.begin(), end = d.end(); it != end; ++it)
	{
		Decl* decl = *it;
		chooseVisitor(decl);

	}
}

bool ASTTreeWalker::isDeclFromUserFile( clang::SourceLocation loc )
{
	FileID file_id = source_manager->getFileID(loc);
	SrcMgr::SLocEntry loc_entry = source_manager->getSLocEntry(file_id);

	if(!loc_entry.isFile())
		return false;

	//Check, if the declaration is in system header
	if(source_manager->isInSystemHeader(loc))
		return false;

	std::string filename ( source_manager->getBufferName(loc) );

	llvm::Twine twine_repr( filename );

        bool t = false;
//TODO: Find a better way to implement me
	for( location_container_t::iterator it = locations_to_parse.begin(); it != locations_to_parse.end(); ++it )
	{
		llvm::sys::fs::equivalent(twine_repr,llvm::Twine(it->str()), t);
		if(t)
			return true;
	}

	return false;
}


void ASTTreeWalker::chooseVisitor( Decl* decl )
{
	switch(decl->getKind())
	{
	case Decl::Namespace:
		visitNamespaceDecl(static_cast<NamespaceDecl*>(decl));
		break;
	case Decl::Enum:
		if(static_cast<EnumDecl*>(decl)->isDefinition())
			visitEnum(static_cast<EnumDecl*>(decl));
		break;
	case Decl::CXXRecord:
	case Decl::Record:
	case Decl::ClassTemplateSpecialization:
			visitClass(static_cast<RecordDecl*>(decl));
		break;
	case Decl::Var:
	case Decl::Field:
		visitVarDecl(static_cast<DeclaratorDecl*>(decl));
		break;
	case Decl::Typedef:
		visitTypedef(static_cast<TypedefDecl*>(decl));
		break;
	case Decl::Function:
	case Decl::CXXConstructor:
	case Decl::CXXDestructor:
	//case Decl::CXXConversion:
	case Decl::CXXMethod:
		visitFunction(static_cast<FunctionDecl*>(decl));
		break;
	case Decl::ClassTemplate:
		visitClass(static_cast<ClassTemplateDecl*>(decl)->getTemplatedDecl());
		break;
	default:
		//std::clog << "Unknown decl type " << decl->getDeclKindName() << std::endl;
		break;
	}
}


void ASTTreeWalker::visitNamespaceDecl( clang::NamespaceDecl* decl )
{
	//Create a new namespace node here
	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_NAMESPACE)
	{
		CppNodeNamespace * parent = static_cast<CppNodeNamespace*>(node_stack.top());
		CppNodeNamespace* node = NULL;
		CppNodePtr found  = parent->getChildByName( decl->getName() );

		if(!found && (parent->getNodeName() == decl->getName()))
		{
			//std::clog << "Already in the scope!" << std::endl;
			m_DirectSearchMap[decl] = parent;
			return;
		}

		if(!found)
		{
			CppNodePtr nodeptr = CppNodePtr(new CppNodeNamespace(decl->getName(),node_stack.top()));
			if(isDeclFromUserFile(decl->getLocation()))
				nodeptr->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);
			node = nodeptr->cast_to<CppNodeNamespace>();
			parent->addChild(nodeptr);
			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
			//std::clog << "Namespace: " << decl->getName().str() << " user_supplied " << (isDeclFromUserFile(decl->getLocation()) ? "true" : "false") << std::endl;
		}
		else if(found->getNodeType() & CppNode::NODE_TYPE_NAMESPACE)
			node = static_cast<CppNodeNamespace*>(found.get());
		else
			throw treewalk_exception("node with the same name of different type found");

		node_stack.push(node);
		decl_stack.push(decl);
		//Iterate through children
		visitDeclContext(static_cast<DeclContext*>(decl));
		decl_stack.pop();
		node_stack.pop();
	}
	else
		throw treewalk_exception("namespace node is expected");
}

void ASTTreeWalker::visitDeclContext( clang::DeclContext* decl )
{
	for(DeclContext::decl_iterator it = decl->decls_begin(), end = decl->decls_end(); it != end; ++it)
		//if(*it != decl_stack.top() && !it->isImplicit())
			chooseVisitor(*it);
}

void ASTTreeWalker::visitEnum( clang::EnumDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeEnum*	node = NULL;
		CppNodePtr		found = parent->getChildByName( decl->getName() );

		if(!found && (parent->getNodeName() == decl->getName()))
		{
		//	std::clog << "Already in the scope!" << std::endl;
			m_DirectSearchMap[decl] = parent;
			return;
		}

		bool			user_supplied_enum = false;
		if( !found )
		{
			CppNodePtr nodeptr (new CppNodeEnum(decl->getName(),parent));
			if(isDeclFromUserFile(decl->getLocation()))
			{
				nodeptr->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);
				user_supplied_enum = true;
			}

			node = nodeptr->cast_to<CppNodeEnum>();
			parent->addChild(nodeptr);

			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
		}
		else
			node = static_cast<CppNodeEnum*>(found.get());

		if(spec == AS_protected)
			node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);
		else if(spec == AS_private)
			node->setAccessType(CppNode::ACCESS_TYPE_PRIVATE);

		//Add children
		for(EnumDecl::enumerator_iterator it = decl->enumerator_begin(), end = decl->enumerator_end();
			it != end; ++it)
		{
			EnumConstantDecl* val = *it;
			if(node->getChildByName(val->getName()))
				continue;
			CppNodeEnumValue* eval = new CppNodeEnumValue(val->getName(),*val->getInitVal().getRawData(),node);
			
			node->addChild(CppNodePtr(eval));
			if(user_supplied_enum)
				eval->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);

			//Register search map for improved type resolving
			m_DirectSearchMap[val] = eval;
			m_ReverseSearchMap[eval] = val;
		}
	}
	else
		throw treewalk_exception("scope node is expected");
}

void ASTTreeWalker::visitClass( clang::RecordDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	bool specialization_defined = false;

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		//Ok, this is much more complicated, than the previous cases
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeScope*	node = NULL; //We do not know, what real type is it.
		CppNodePtr		found = parent->getChildByName( decl->getName() );

		if(!found && ( parent->getNodeName() == decl->getName() ))
		{
			//std::clog << "Already in the scope!" << std::endl;
			m_DirectSearchMap[decl] = parent;
			return;
		}

		if( !found || clang::ClassTemplateSpecializationDecl::classof(decl))
		{
			//Ok, we could not find a specific node
			//First of all, we do not separate class and struct.
			//Yet we do separate union, anonymous struct and class template specialization
			//Also, union is not derived from class, as it lacks support of methods
			//Lets chose the correct base for the node
			CppNodePtr	__managed_node;
			if(!clang::ClassTemplateSpecializationDecl::classof(decl))
			{
				if(decl->isClass() || decl->isStruct())
				{
					if(!decl->isAnonymousStructOrUnion())
						__managed_node = CppNodePtr(new CppNodeClass(decl->getName(),parent));
					else
						__managed_node = CppNodePtr(new CppNodeAnonymousStruct(parent));
				}
				else //This is a union, as enums a handled separately
				{
					if(!decl->isAnonymousStructOrUnion())
						__managed_node = CppNodePtr(new CppNodeUnion(decl->getName(),parent));
					else
						__managed_node = CppNodePtr(new CppNodeAnonymousUnion(parent));
				}
			}
			else //Template specialization
			{
				//Read template types
				ClassTemplateSpecializationDecl* tdecl = static_cast<ClassTemplateSpecializationDecl*>(decl);
				const TemplateArgumentList& t_args = tdecl->getTemplateInstantiationArgs();
				//We need to deduce the correct parent
				clang::DeclContext* decl_context = decl->getDeclContext();
				//This one is either NamespaceDecl, either RecordDecl context

				CppNode* new_parent = NULL;

				if(llvm::dyn_cast<NamespaceDecl>(decl_context))
					new_parent = m_DirectSearchMap[static_cast<NamespaceDecl*>(decl_context)];
				else if(llvm::dyn_cast<RecordDecl>(decl_context))
					new_parent = m_DirectSearchMap[static_cast<RecordDecl*>(decl_context)];
				if(new_parent && (new_parent->getNodeType() & CppNode::NODE_TYPE_SCOPE))
					parent = static_cast<CppNodeScope*>(new_parent);

				boost::shared_ptr<CppNodeClassTemplateSpecialization> m_TemplateSpecialization(new CppNodeClassTemplateSpecialization(decl->getName(),parent));
				for(size_t ta_i = 0; ta_i < t_args.size(); ++ta_i)
				{
					const TemplateArgument& arg = t_args[ta_i];
					//Get the argument type
					TemplateArgument::ArgKind arg_kind = arg.getKind();
					
					switch(arg_kind)
					{
					case TemplateArgument::Type:
					{
						clang::QualType type = arg.getAsType();
						CppTypePtr	qual_type = resolveQualType(&type);
						assert(qual_type);
						
						CppNodeClassTemplateSpecialization::TemplateArgumentPtr a_ptr(new CppNodeClassTemplateSpecialization::TemplateArgument(qual_type));

						m_TemplateSpecialization->addTemplateArgument(a_ptr);
					}
						break;
					case TemplateArgument::Integral:
						m_TemplateSpecialization->addTemplateArgument(CppNodeClassTemplateSpecialization::TemplateArgumentPtr(
							new CppNodeClassTemplateSpecialization::TemplateArgument(*arg.getAsIntegral()->getRawData())));
						break;
					case TemplateArgument::Template:
						m_TemplateSpecialization->addTemplateArgument(CppNodeClassTemplateSpecialization::TemplateArgumentPtr(
							new CppNodeClassTemplateSpecialization::TemplateArgument(arg.getAsTemplate().getAsTemplateDecl()->getName())));
						break;
					default:
						{
							static const char* __names[] = {
								"NULL",
								"TYPE",
								"DECLARATION",
								"INTEGRAL",
								"TEMPLATE",
								"TEMPLATEEXPANSION",
								"EXPRESSION",
								"PACK"
							};
							throw treewalk_exception( (std::string("Unresolved parameter type: ") + __names[arg_kind]).c_str() );
						}
					}
				} // Loop through template arguments
				//Check, if current specialization exists

				if(!m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()])
				{
					m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()] = m_TemplateSpecialization;
					__managed_node = m_TemplateSpecialization;
					specialization_defined = false;
				}
				else
					__managed_node = m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()];
			} //end node deduction

			node = __managed_node->cast_to<CppNodeScope>();

			////Deduce correct namespace
			parent->addChild(__managed_node);

			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;

			if(isDeclFromUserFile(decl->getLocation()))
				node->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);

		//	std::clog << "Class (union) " << node->getScopedName() << std::endl;

			//Parse bases:
			if( CXXRecordDecl::classof(decl) && (decl->isDefinition() || specialization_defined) )
			{
				CXXRecordDecl* cxx_decl = static_cast<CXXRecordDecl*>(decl);
				if(!decl->isDefinition())
				{
				/*	if(decl->getDefinition() && CXXRecordDecl::classof(decl->getDefinition()))
						cxx_decl = static_cast<CXXRecordDecl*>(decl->getDefinition());
					else
						cxx_decl = NULL;*/
					ClassTemplateSpecializationDecl* tdecl = static_cast<ClassTemplateSpecializationDecl*>(decl);
					cxx_decl = tdecl->getSpecializedTemplate()->getTemplatedDecl()->getDefinition();
				/*	if(cxx_decl)
						std::clog << "tdecl-> " << cxx_decl->getNameAsString() << std::endl;
					else
						std::clog << "tdecl not defined: " << decl->getNameAsString() << std::endl;*/
				}

				if(cxx_decl)
				{
					for( CXXRecordDecl::base_class_iterator it = cxx_decl->bases_begin(), end = cxx_decl->bases_end(); it != end; ++it )
					{
						CXXBaseSpecifier& base_class = *it;
						clang::QualType base_type = base_class.getType();
						CppNode::ACCESS_TYPE access = base_class.getAccessSpecifier() == AS_public ? CppNode::ACCESS_TYPE_PUBLIC :
							(base_class.getAccessSpecifier() == AS_protected ? CppNode::ACCESS_TYPE_PROTECTED : CppNode::ACCESS_TYPE_PRIVATE );
						static_cast<CppNodeClass*>(node)->addBaseClass(CppNodeClass::base_type_t(std::make_pair(resolveQualType(&base_type), access)));
					}

					for( CXXRecordDecl::base_class_iterator it = cxx_decl->vbases_begin(), end = cxx_decl->vbases_end(); it != end; ++it )
					{
						CXXBaseSpecifier& base_class = *it;
						clang::QualType base_type = base_class.getType();
						CppNode::ACCESS_TYPE access = base_class.getAccessSpecifier() == AS_public ? CppNode::ACCESS_TYPE_PUBLIC :
							(base_class.getAccessSpecifier() == AS_protected ? CppNode::ACCESS_TYPE_PROTECTED : CppNode::ACCESS_TYPE_PRIVATE );
						static_cast<CppNodeClass*>(node)->addBaseClass(CppNodeClass::base_type_t(std::make_pair(resolveQualType(&base_type), access)));
					}
				}
				else
					specialization_defined = false;
			}
		}
		else
		{
			node = found->cast_to<CppNodeScope>();
			m_DirectSearchMap[decl] = node;
		}

		//Push class on top
		if( decl->isDefinition()  || specialization_defined ) 
		{
			node_stack.push(node);
			decl_stack.push(decl);
			if(decl->isDefinition())
				visitDeclContext(static_cast<DeclContext*>(decl));
			else
				visitDeclContext(static_cast<DeclContext*>(static_cast<ClassTemplateSpecializationDecl*>(decl)->getSpecializedTemplate()->getTemplatedDecl()->getDefinition()));
			//Remove class from the stack
			decl_stack.pop();
			node_stack.pop();
		}
	}
	else
		throw treewalk_exception("scope node is expected");
}

CppTypePtr ASTTreeWalker::resolveQualType( clang::QualType* type )
{
	const Type* type_s =  type->getTypePtr();
	//Ok, check the map
	std::string qualified_name;
	if(!TypeOfType::classof(type_s) && !TypeOfExprType::classof(type_s) && !BuiltinType::classof(type_s) && !DecltypeType::classof(type_s))
		qualified_name = type->getAsString();
	else
	{
		if(TypeOfType::classof(type_s))
			qualified_name = static_cast<const TypeOfType*>(type_s)->desugar().getAsString();
		else if(TypeOfExprType::classof(type_s))
			qualified_name = static_cast<const TypeOfExprType*>(type_s)->desugar().getAsString();
		else if(BuiltinType::classof(type_s))
			qualified_name = static_cast<const BuiltinType*>(type_s)->desugar().getAsString();
		else
			qualified_name = static_cast<const DecltypeType*>(type_s)->desugar().getAsString();
	}
	

	boost::erase_range(qualified_name, boost::find_first(qualified_name,std::string("class ") ) );
	boost::erase_range(qualified_name, boost::find_first(qualified_name,std::string("struct ") ) );
	boost::erase_range(qualified_name, boost::find_first(qualified_name,std::string("union ") ) );
	boost::erase_range(qualified_name, boost::find_first(qualified_name,std::string("enum ") ) );
	boost::erase_range(qualified_name, boost::find_first(qualified_name,std::string("typename ") ) );
	
	CppTypePtr type_ptr = tree_ptr->getTypeBySignature(qualified_name);

	if( !type_ptr )
	{
		type_ptr = CppTypePtr( new CppType() );

		if( type_s->isBuiltinType() || type_s->isVoidPointerType()) //void* is not really builtin. Yet no need to resove it further recursively
		{
			type_ptr->m_TypeHeader.is_builtin = true;
			type_ptr->m_ASTNode = NULL;
		}
		else 
		{
			//Search the AST
			if(type_s->hasPointerRepresentation())
			{
				clang::QualType pointee_type = type_s->getPointeeType();
				CppTypePtr base_type = resolveQualType(&pointee_type);
				assert(base_type.get());
				//Try to get the Pointer/Reference from tree
				CppNodePtr ptr = tree_ptr->findNodeBySignature(type->getLocalUnqualifiedType().getAsString());

				if(ptr)
					type_ptr->m_ASTNode = ptr.get();
				else 
				{
					if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
					{
						//Ok, this is much more complicated, than the previous cases
						CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
						CppNodePtr		node;

						std::string node_name = type->getAsString();

						//size_t pos = node_name.find_last_of(":");
						//if( pos != std::string::npos )
						//	node_name.erase( 0, pos + 1 );

						if(type_s->isReferenceType())
						{
							node = CppNodePtr( new CppNodeReference(parent) );
							node->cast_to<CppNodeReference>()->setReferencedType(base_type);
							node->cast_to<CppNodeReference>()->setReferenceType(type_s->isLValueReferenceType() ? 
								CppNodeReference::REFERENCE_TYPE_LVALUE : CppNodeReference::REFERENCE_TYPE_RVALUE);

							type_ptr->m_TypeHeader.is_reference = true;
							type_ptr->m_TypeHeader.is_constant_reference = type->isLocalConstQualified();
						}
						else if( type_s->isPointerType() )
						{
							node = CppNodePtr( new CppNodePointer(parent) );
							node->cast_to<CppNodePointer>()->setPointeeType(base_type);
							node->cast_to<CppNodePointer>()->setDeclaredAsArray(type_s->isArrayType());

							type_ptr->m_TypeHeader.is_pointer = true;
							type_ptr->m_TypeHeader.is_constant_pointer = type->isLocalConstQualified();
							type_ptr->m_TypeHeader.is_array = type_s->isArrayType();
							type_ptr->m_TypeHeader.is_volatile_pointer = type->isLocalVolatileQualified();
						}
						else
						{
							type_ptr->m_TypeHeader.is_unresolved_usertype = true;
							type_ptr->m_ASTNode = NULL;
						}

						if(node)
						{
							node->m_NodeName = node_name;
							tree_ptr->getRootNode()->cast_to<CppNodeScope>()->addChild(node);
							type_ptr->m_ASTNode = node.get();
						}
						//if(qualified_name.find("complex<double>") != std::string::npos)
						//	std::cout << "Break" << std::endl;
					}
					else
						throw treewalk_exception("scope node is expected");
				}
			} // Pointer type
			else
			{
				//This one is the most general case.
				if( type_s->isTemplateTypeParmType() ||
					 (
					 type_s->isRecordType() && 
					  (
					   type_s->getAs<TagType>()->getDecl()->getKind() == Decl::ClassTemplate || 
					   type_s->getAs<TagType>()->getDecl()->getKind() == Decl::ClassTemplatePartialSpecialization
					   )
					  )
					)
				{
					type_ptr->m_TypeHeader.is_user_type = false;
					type_ptr->m_TypeHeader.is_template_parameter = true;
					type_ptr->m_ASTNode = NULL;
					//std::clog << type->getAsString() << std::endl;
				}
				else if(type_s->isMemberPointerType())
				{
					//type_s->castAs<MemberPointerType>()->
					//CppNodePtr node = CppNodePtr( new CppNodeClassMemberPointer(parent) );
					//std::cout << "\nMember pointer!!!\n" << std::endl;
					type_ptr->m_TypeHeader.is_unresolved_usertype = true;
				}
				else if(type_s->isFunctionType())
				{
					//std::cout << "Function typed!!!" << std::endl;
					type_ptr->m_TypeHeader.is_unresolved_usertype = true;
				}
				else if(type_s->isRecordType() || type_s->isEnumeralType())
				{
					//Get underlying type
					CppNode* underl = m_DirectSearchMap[type_s->getAs<TagType>()->getDecl()];
					if(underl)
						type_ptr->m_ASTNode = underl;
					else 
					{	
						chooseVisitor(type_s->getAs<TagType>()->getDecl());

						underl = m_DirectSearchMap[type_s->getAs<TagType>()->getDecl()];
						if(underl)
							type_ptr->m_ASTNode = underl;
						else if( node_stack.top()->getNodeName() == type_s->getAs<TagType>()->getDecl()->getNameAsString() )
							underl = node_stack.top();
						else 
						{
							std::clog << "[ERROR]: Decl not found: " << type_s->getAs<TagType>()->getDecl()->getNameAsString() << std::endl;
							std::clog << "[ERROR]: Stack top: " << node_stack.top()->getNodeName() << std::endl; 
							throw treewalk_exception((std::string("Underlying type failed to resolve: ") + type->getAsString()).c_str());
						}
					}

					type_ptr->m_TypeHeader.is_constant = type->isLocalConstQualified();
					type_ptr->m_TypeHeader.is_volatile = type->isLocalVolatileQualified();
				}
				else
				{
					type_ptr->m_TypeHeader.is_unresolved_usertype = true;
					type_ptr->m_ASTNode = NULL;
				}
			} // General case
		} // Non built in type
		//Generate name

		type_ptr->m_QualifiedName = qualified_name;

		type_ptr->m_TypeHeader.is_stl_type = (type_ptr->m_QualifiedName.find("std::") != std::string::npos);
		type_ptr->m_TypeHeader.is_user_type = !(type_ptr->m_TypeHeader.is_builtin && type_ptr->m_TypeHeader.is_stl_type);

		//CppTypePtr second_lookup
		//if(tree_ptr->getTypeBySignature(type_ptr->m_QualifiedName));
		tree_ptr->addType(type_ptr);

		return type_ptr;
		//std::clog << "Resolve qtype " << type->getAsString() << " -> " << type_ptr->getQualifiedName() << " ( " 
		//	<< (type_ptr->m_ASTNode ? type_ptr->m_ASTNode->getScopedName() : (type_ptr->m_TypeHeader.is_user_type && !type_ptr->m_TypeHeader.is_builtin ? "unresolved" : "builtin")) 
		//	<< " ) " << std::endl;
	} // Type not found

	return type_ptr;
}

void ASTTreeWalker::visitVarDecl( clang::DeclaratorDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		//Ok, this is much more complicated, than the previous cases
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeVariableDecl*	node = NULL; //We do not know, what real type is it.
		CppNodePtr		found = parent->getChildByName( decl->getName() );
		if( !found )
		{

			CppNodePtr nodeptr;
			//= CppNodePtr(new CppNodeTypedef(decl->getName(),node_stack.top()));
			if(decl->isCXXClassMember())
			{
				nodeptr = CppNodePtr( new CppNodeClassMember(decl->getName(), parent) );
				if(clang::VarDecl::classof(decl) && static_cast<clang::VarDecl*>(decl)->isStaticDataMember())
					nodeptr->cast_to<CppNodeClassMember>()->setStatic( true );
				else
					nodeptr->cast_to<CppNodeClassMember>()->setStatic( false );
				nodeptr->cast_to<CppNodeClassMember>()->setHasValue( false );
			}
			else if(clang::VarDecl::classof(decl) && static_cast<clang::VarDecl*>(decl)->hasGlobalStorage())
			{
				if(decl->getType().isConstQualified())
				{
					nodeptr = CppNodePtr( new CppNodeGlobalConstant(decl->getName(), parent) );
					nodeptr->cast_to<CppNodeGlobalConstant>()->setHasValue(true);
				}
				else
				{
					nodeptr = CppNodePtr( new CppNodeGlobalVariable(decl->getName(), parent) );
					nodeptr->cast_to<CppNodeGlobalVariable>()->setHasValue(false);
				}
			}
			else
			{
				nodeptr = CppNodePtr( new CppNodeVariableDecl(parent, CppNode::NODE_TYPE_VARIABLE_DECL, decl->getName()) );
				nodeptr->cast_to<CppNodeVariableDecl>()->setHasValue(false);
			}
			if(isDeclFromUserFile(decl->getLocation()))
				nodeptr->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);
			node = nodeptr->cast_to<CppNodeVariableDecl>();
			if(!(parent->getNodeType() & CppNode::NODE_TYPE_CLASS))
				parent->addChild(nodeptr);
			else
				static_cast<CppNodeClass*>(parent)->addMember(CppNodeClassMemberPtr(nodeptr, boost::detail::static_cast_tag()));
			if(spec == AS_protected)
				node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);
			else if(spec == AS_private)
				node->setAccessType(CppNode::ACCESS_TYPE_PRIVATE);

			clang::QualType	decl_type = decl->getType();
			node->setType(resolveQualType(&decl_type));

			//std::clog << "var " << node->getScopedName() << " -> " << node->getCppType()->getQualifiedName() << std::endl;

			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
		}
	}
	else
		throw treewalk_exception("scope node is expected");
}

void ASTTreeWalker::visitTypedef( clang::TypedefDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		//Ok, this is much more complicated, than the previous cases
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeTypedef*	node = NULL; //We do not know, what real type is it.
		CppNodePtr		found = parent->getChildByName( decl->getName() );
		if( !found )
		{
			CppNodePtr nodeptr = CppNodePtr(new CppNodeTypedef(decl->getName(),node_stack.top()));
			if(isDeclFromUserFile(decl->getLocation()))
				nodeptr->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);
			node = nodeptr->cast_to<CppNodeTypedef>();
			parent->addChild(nodeptr);
			if(spec == AS_protected)
				node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);
			else if(spec == AS_private)
				node->setAccessType(CppNode::ACCESS_TYPE_PRIVATE);

			//if( decl->getUnderlyingType().getAsString().find("integral_constant") != std::string::npos )
			//{
				//std::clog << "!!Rejected " << decl->getUnderlyingType().getAsString() << std::endl;
			//}
			clang::QualType	underl_type = decl->getUnderlyingType();
			node->setAliasType(resolveQualType(&underl_type));

			//std::clog << "typedef " << node->getScopedName() << " -> " << node->getAliasType()->getQualifiedName() << std::endl;

			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
		}
	}
	else
		throw treewalk_exception("scope node is expected");
}

void ASTTreeWalker::visitFunction( clang::FunctionDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(decl->getBuiltinID())
		return; //Nope, there is definitely no interest in built ins
	//Ok, this case is rather difficult. Lets start from the very basic check
	CppNode* parent = node_stack.top();
	if(parent->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		std::string func_name = decl->getNameAsString();
		//Now, we should first generate real prototype of the function
		typedef boost::shared_ptr<CppNodeFunctionProto> func_node_ptr_t;
		func_node_ptr_t func_node;

		//First of all, choose the correct type based on declaration kind
		switch(decl->getKind())
		{
		case Decl::Function:
			func_node = func_node_ptr_t ( new CppNodeFunction( func_name, parent ) );
			break;
		case Decl::CXXMethod:
			if(!static_cast<CXXMethodDecl*>(decl)->isCopyAssignmentOperator())
				func_node = func_node_ptr_t ( new CppNodeClassMethod( func_name, parent ) );
			else
				func_node = func_node_ptr_t ( new CppNodeClassOperatorEqual( parent ) );
			break;
		case Decl::CXXConstructor:
			if(!static_cast<CXXConstructorDecl*>(decl)->isCopyOrMoveConstructor())
				func_node = func_node_ptr_t ( new CppNodeClassConstructor( parent ) );
			else
				func_node = func_node_ptr_t ( new CppNodeClassCopyConstructor( parent ) );
			break;
		case Decl::CXXDestructor:
			func_node = func_node_ptr_t ( new CppNodeClassDestructor( parent ) );
			break;
		}

		//Set the return value
		QualType ret_qtype = decl->getType()->getAs<FunctionType>()->getResultType();
		if( !ret_qtype->isVoidType() )
			func_node->setReturnValue( resolveQualType( &ret_qtype ) );

		//Parse arguments
		for(FunctionDecl::param_iterator it = decl->param_begin(), end = decl->param_end(); it != end; ++it)
		{
			ParmVarDecl* parm = *it;

			clang::QualType parm_type = parm->getType();

			func_node->addArgument(CppNodeFunctionProto::argument_ptr_t ( 
				new CppNodeFunctionProto::argument_t(resolveQualType(&parm_type), parm->hasDefaultArg())));
		}

		if( decl->isOverloadedOperator() )
			func_node->setAsOverloadedOperator(true, decl->getOverloadedOperator() );
		if( decl->getKind() != Decl::Function  )
		{
			CXXMethodDecl* mdecl = static_cast<CXXMethodDecl*>(decl);
			CppNodeClassMethod* m = static_cast<CppNodeClassMethod*>(func_node.get());

			m->setAbstract( mdecl->isPure() );
			m->setVirtual( mdecl->isVirtual() );
			m->setStatic ( mdecl->isStatic() );
			m->setMethodConstQualifier( mdecl->isStatic() ? false : (mdecl->getTypeQualifiers() & Qualifiers::Const ) );

			if( decl->getKind() == Decl::CXXConstructor )
				static_cast<CppNodeClassConstructor*>(m)->setExplicit( !mdecl->isImplicit() );
		}

		if(!static_cast<CppNodeScope*>(parent)->getChildByName(func_node->getNodeName()))
		{
			if((decl->getKind() != Decl::Function) && (parent->getNodeType() & CppNode::NODE_TYPE_CLASS) )
				static_cast<CppNodeClass*>(parent)->addMethod(CppNodeClassMethodPtr(func_node, boost::detail::static_cast_tag()));
			else
				static_cast<CppNodeScope*>(parent)->addChild(func_node);

			if(spec == AS_protected)
				func_node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);
			else if(spec == AS_private)
				func_node->setAccessType(CppNode::ACCESS_TYPE_PRIVATE);
		}
	}
	else //if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
		throw treewalk_exception("scope node is expected");
}
