#include "CppTree/ASTTreeWalker.h"

#include "CppTree/CppNode.h"
#include "CppTree/CppType.h"
#include "CppTree/CppTree.h"

#include "clang/ast/DeclTemplate.h"

#include <boost/algorithm/string.hpp>

using namespace clang;

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
	return (locations_to_parse.find(filename) != locations_to_parse.end());
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
		std::clog << "Unknown decl type " << decl->getDeclKindName() << std::endl;
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
		}
		else if(found->getNodeType() & CppNode::NODE_TYPE_NAMESPACE)
			node = static_cast<CppNodeNamespace*>(found.get());
		else
			throw std::exception("node with the same name of different type found");

		node_stack.push(node);
		decl_stack.push(decl);
		//Iterate through children
		visitDeclContext(static_cast<DeclContext*>(decl));
		decl_stack.pop();
		node_stack.pop();
	}
	else
		throw std::exception("namespace node is expected");
}

void ASTTreeWalker::visitDeclContext( clang::DeclContext* decl )
{
	for(DeclContext::decl_iterator it = decl->decls_begin(), end = decl->decls_end(); it != end; ++it)
		if(*it != decl_stack.top() && !it->isImplicit())
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
		throw std::exception("scope node is expected");
}

void ASTTreeWalker::visitClass( clang::RecordDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(clang::ClassTemplateDecl::classof(decl))
		return;

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		//Ok, this is much more complicated, than the previous cases
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeScope*	node = NULL; //We do not know, what real type is it.
		CppNodePtr		found = parent->getChildByName( decl->getName() );
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
				boost::shared_ptr<CppNodeClassTemplateSpecialization> m_TemplateSpecialization(new CppNodeClassTemplateSpecialization(decl->getName(),parent));
				for(size_t ta_i = 0; ta_i < t_args.size(); ++ta_i)
				{
					const TemplateArgument& arg = t_args[ta_i];
					//Get the argument type
					TemplateArgument::ArgKind arg_kind = arg.getKind();
					
					switch(arg_kind)
					{
					case TemplateArgument::ArgKind::Type:
					{
						CppTypePtr	qual_type = resolveQualType(&arg.getAsType());
						assert(qual_type);
						
						CppNodeClassTemplateSpecialization::TemplateArgumentPtr a_ptr(new CppNodeClassTemplateSpecialization::TemplateArgument(qual_type));

						m_TemplateSpecialization->addTemplateArgument(a_ptr);
					}
						break;
					case TemplateArgument::ArgKind::Integral:
						m_TemplateSpecialization->addTemplateArgument(CppNodeClassTemplateSpecialization::TemplateArgumentPtr(
							new CppNodeClassTemplateSpecialization::TemplateArgument(*arg.getAsIntegral()->getRawData())));
						break;
					case TemplateArgument::ArgKind::Template:
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
							throw std::exception( (std::string("Unresolved parameter type: ") + __names[arg_kind]).c_str() );
						}
					}
				} // Loop through template arguments
				//Check, if current specialization exists

				if(!m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()])
				{
					m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()] = m_TemplateSpecialization;
					__managed_node = m_TemplateSpecialization;
				}
				else
					__managed_node = m_TemplateSpecializationLookup[m_TemplateSpecialization->getScopedName()];
			} //end node deduction

			node = __managed_node->cast_to<CppNodeScope>();
			parent->addChild(__managed_node);

			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;

			if(isDeclFromUserFile(decl->getLocation()))
				node->setNodeFlag(CppNode::NODE_FLAG_USER_SUPPLIED);

			std::clog << "Class (union) " << node->getScopedName() << std::endl;
		}
		else
			node = found->cast_to<CppNodeScope>();

		//Push class on top
		if(decl->isDefinition())
		{
			node_stack.push(node);
			decl_stack.push(decl);
			visitDeclContext(static_cast<DeclContext*>(decl));
			//Remove class from the stack
			decl_stack.pop();
			node_stack.pop();
		}
	}
	else
		throw std::exception("scope node is expected");
}

CppTypePtr ASTTreeWalker::resolveQualType( clang::QualType* type )
{
	//Ok, we would just hope, that we will catch up,
	//how the asString method works

	//Ok, check the map
	CppTypePtr type_ptr = tree_ptr->getTypeBySignature(type->getAsString());

	if( !type_ptr )
	{
		type_ptr = CppTypePtr( new CppType() );

		const Type* type_s =  type->getTypePtr();

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
				CppTypePtr base_type = resolveQualType(&type_s->getPointeeType());

				//Try to get the Pointer/Reference from tree
				CppNode* ptr = tree_ptr->findNodeBySignature(type->getLocalUnqualifiedType().getAsString());

				if(ptr)
					type_ptr->m_ASTNode = ptr;
				else 
				{
					if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
					{
						//Ok, this is much more complicated, than the previous cases
						CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
						CppNodePtr		node;

						std::string node_name = type->getAsString();

						size_t pos = node_name.find_last_of(":");
						if( pos != std::string::npos )
							node_name.erase( 0, pos + 1 );

						if(type_s->isReferenceType())
						{
							node = CppNodePtr( new CppNodeReference(parent) );
							node->cast_to<CppNodeReference>()->setReferencedType(base_type.get());
							node->cast_to<CppNodeReference>()->setReferenceType(type_s->isLValueReferenceType() ? 
								CppNodeReference::REFERENCE_TYPE_LVALUE : CppNodeReference::REFERENCE_TYPE_RVALUE);

							type_ptr->m_TypeHeader.is_reference = true;
							type_ptr->m_TypeHeader.is_constant_reference = type->isLocalConstQualified();
						}
						else
						{
							node = CppNodePtr( new CppNodePointer(parent) );
							node->cast_to<CppNodePointer>()->setPointeeType(base_type.get());
							node->cast_to<CppNodePointer>()->setDeclaredAsArray(type_s->isArrayType());

							type_ptr->m_TypeHeader.is_pointer = true;
							type_ptr->m_TypeHeader.is_constant_pointer = type->isLocalConstQualified();
							type_ptr->m_TypeHeader.is_array = type_s->isArrayType();
							type_ptr->m_TypeHeader.is_volatile_pointer = type->isLocalVolatileQualified();
						}

						node->m_NodeName = node_name;
						parent->addChild(node);

						type_ptr->m_ASTNode = node.get();
					}
					else
						throw std::exception("scope node is expected");
				}
			} // Pointer type
			else
			{
				//This one is the most general case.
				if(type_s->isMemberPointerType())
				{
				//	node = CppNodePtr( new CppNodeClassMemberPointer(parent) );
					std::cout << "\nMember pointer!!!\n" <<std::endl;
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
						else 
						{
							throw std::exception((std::string("Underlying type failed to resolve: ") + type->getAsString()).c_str());
						}
					}

					type_ptr->m_TypeHeader.is_constant = type->isLocalConstQualified();
					type_ptr->m_TypeHeader.is_volatile = type->isLocalVolatileQualified();
				}
			} // General case
		} // Non built in type
		//Generate name

		if(!TypeOfType::classof(type_s) && !TypeOfExprType::classof(type_s) && !BuiltinType::classof(type_s) && !DecltypeType::classof(type_s))
			type_ptr->m_QualifiedName = type->getAsString();
		else
		{
			if(TypeOfType::classof(type_s))
				type_ptr->m_QualifiedName = static_cast<const TypeOfType*>(type_s)->desugar().getAsString();
			else if(TypeOfExprType::classof(type_s))
				type_ptr->m_QualifiedName = static_cast<const TypeOfExprType*>(type_s)->desugar().getAsString();
			else if(BuiltinType::classof(type_s))
				type_ptr->m_QualifiedName = static_cast<const BuiltinType*>(type_s)->desugar().getAsString();
			else
				type_ptr->m_QualifiedName = static_cast<const DecltypeType*>(type_s)->desugar().getAsString();
		}
		type_ptr->m_TypeHeader.is_stl_type = (type_ptr->m_QualifiedName.find("std::") != std::string::npos);
		type_ptr->m_TypeHeader.is_user_type = !(type_ptr->m_TypeHeader.is_builtin && type_ptr->m_TypeHeader.is_stl_type);

		boost::erase_range(type_ptr->m_QualifiedName, boost::find_first(type_ptr->m_QualifiedName,std::string("class ") ) );
		boost::erase_range(type_ptr->m_QualifiedName, boost::find_first(type_ptr->m_QualifiedName,std::string("struct ") ) );
		boost::erase_range(type_ptr->m_QualifiedName, boost::find_first(type_ptr->m_QualifiedName,std::string("union ") ) );
		boost::erase_range(type_ptr->m_QualifiedName, boost::find_first(type_ptr->m_QualifiedName,std::string("enum ") ) );

		tree_ptr->addType(type_ptr);
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
			parent->addChild(nodeptr);
			if(spec == AS_protected)
				node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);
			else if(spec == AS_private)
				node->setAccessType(CppNode::ACCESS_TYPE_PRIVATE);

			node->setType(resolveQualType(&decl->getType()));

			std::clog << "var " << node->getScopedName() << " -> " << node->getCppType()->getQualifiedName() << std::endl;

			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
		}
	}
	else
		throw std::exception("scope node is expected");
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

			node->setAliasType(resolveQualType(&decl->getUnderlyingType()));

			std::clog << "typedef " << node->getScopedName() << " -> " << node->getAliasType()->getQualifiedName() << std::endl;

			//Register search map for improved type resolving
			m_DirectSearchMap[decl] = node;
			m_ReverseSearchMap[node] = decl;
		}
	}
	else
		throw std::exception("scope node is expected");
}

void ASTTreeWalker::visitFunction( clang::FunctionDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();

	if(decl->getBuiltinID())
		return; //Nope, there is definetly no interst in built ins
	//Ok, this case is rather difficult. Lets start from the very basic check
	CppNode* parent = node_stack.top();
	if(parent->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		std::string func_name = decl->getNameAsString();
		//Now, we should first generate real prototype of the function
		typedef std::auto_ptr<CppNodeFunctionProto> func_node_ptr_t;
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
		QualType& ret_qtype = decl->getType()->getAs<FunctionType>()->getResultType();
		if( !ret_qtype->isVoidType() )
			func_node->setReturnValue( resolveQualType( &ret_qtype ) );

		//Parse arguments
		for(FunctionDecl::param_iterator it = decl->param_begin(), end = decl->param_end(); it != end; ++it)
		{
			ParmVarDecl* parm = *it;

			func_node->addArgument(CppNodeFunctionProto::argument_ptr_t ( 
				new CppNodeFunctionProto::argument_t(resolveQualType(&parm->getType()), parm->hasDefaultArg())));
		}

		if( decl->isOverloadedOperator() )
			func_node->setAsOverloadedOperator(true, decl->getOverloadedOperator() );
		if( decl->getKind() != Decl::Function )
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

		//Test
		std::cout 
			<< "func: " << (func_node->hasReturnValue() ? func_node->getReturnValue()->getQualifiedName() : "void") << " " 
			<< func_node->getScopedName() << std::endl;
	}
	else //if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
		throw std::exception("scope node is expected");
}
