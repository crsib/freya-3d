#include "CppTree/ASTTreeWalker.h"

#include "CppTree/CppNode.h"
#include "CppTree/CppType.h"
#include "CppTree/CppTree.h"

#include "clang/ast/DeclTemplate.h"

using namespace clang;

ASTTreeWalker::ASTTreeWalker() : clang::ASTConsumer(), tree_ptr(new CppTree) 
{ 
	m_RootNode  = tree_ptr->getRootNode();
	node_stack.push(m_RootNode);
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
		//if(static_cast<TagDecl*>(decl)->isDefinition())
			visitClass(static_cast<RecordDecl*>(decl));
		break;
	case Decl::Var:
		visitVarDecl(static_cast<VarDecl*>(decl));
		break;
	case Decl::Typedef:
		visitTypedef(static_cast<TypedefDecl*>(decl));
		break;
	case Decl::Function:
		visitFunction(static_cast<FunctionDecl*>(decl));
		break;
	case Decl::ClassTemplate:
		visitClass(static_cast<ClassTemplateDecl*>(decl)->getTemplatedDecl());
		break;
	default:
		std::cout << "Unknown decl type " << decl->getDeclKindName() << std::endl;
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

		//Iterate through children
		visitDeclContext(static_cast<DeclContext*>(decl));

		node_stack.pop();
	}
	else
		throw std::exception("namespace node is expected");
}

void ASTTreeWalker::visitDeclContext( clang::DeclContext* decl )
{
	for(DeclContext::decl_iterator it = decl->decls_begin(), end = decl->decls_end(); it != end; ++it)
		chooseVisitor(*it);
}

void ASTTreeWalker::visitEnum( clang::EnumDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();
	if(spec == AS_private)//We do ignore private access.
		return;

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

		if(decl->getAccess() == AS_protected)
			node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);

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
	if(spec == AS_private)//We do ignore private access.
		return;

	if(node_stack.top()->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		//Ok, this is much more complicated, than the previous cases
		CppNodeScope*	parent = static_cast<CppNodeScope*>(node_stack.top());
		CppNodeScope*	node = NULL; //We do not know, what real type is it.
		CppNodePtr		found = parent->getChildByName( decl->getName() );
		if( !found )
		{
			//Ok, we could not find a specific node
			//First of all, we do not separate class and struct.
			//Yet we do separate union, anonymous struct and class template specializtion
			//Also, union is not derived from class, as it lacks support of methods
			//Lets chose the correct base for the node
			CppNodePtr	__managed_node;
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
		node_stack.push(node);

		//Remove class from the stack
		node_stack.pop();
	}
	else
		throw std::exception("scope node is expected");
}

CppTypePtr ASTTreeWalker::resolveQualType( clang::QualType* type )
{
	//Ok, we would just hope, that we will catch up,
	//how the asString method works

	std::cout << "\nresolveQualType entry: " << type->getAsString() << std::endl;

	//Ok, check the map
	CppTypePtr type_ptr = tree_ptr->getTypeBySignature(type->getAsString());

	if( !type_ptr )
	{
		type_ptr = CppTypePtr( new CppType() );

		Type* type_s =  type->getTypePtr();

		if( type_s->isBuiltinType() || type_s->isVoidPointerType()) //void* is not really builtin. Yet no need to resove it further recursively
		{
			type_ptr->m_TypeHeader.is_builtin = true;
			type_ptr->m_ASTNode = NULL;
			std::cout << "Atomic type" << std::endl;
		}
		else 
		{
			//Search the AST
			if(type_s->hasPointerRepresentation())
			{
				CppTypePtr base_type = resolveQualType(&type_s->getPointeeType());

				//Try to get the Pointer/Reference from tree

				std::cout << "Resolving unqualified type node " << type->getLocalUnqualifiedType().getAsString() << std::endl;

				CppNode* ptr = tree_ptr->findNodeBySignature(type->getLocalUnqualifiedType().getAsString());

				if(ptr)
					std::cout << "Node already declared! " << std::endl;
				
				if(ptr)
				{
					type_ptr->m_ASTNode = ptr;
				}
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
						
						std::cout << "Created wrap node " << node->getScopedName() << std::endl;

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
					std::cout << "class type" << std::endl;
					//Get underlying type
					CppNode* underl = m_DirectSearchMap[type_s->getAs<TagType>()->getDecl()];
					if(underl)
					{
						type_ptr->m_ASTNode = underl;
						std::cout << "Resolved to " << underl->getScopedName() << std::endl; 
					}
					else 
					{	
						std::cout << "Trying to resolve the type! " << std::endl;
						chooseVisitor(type_s->getAs<TagType>()->getDecl());

						underl = m_DirectSearchMap[type_s->getAs<TagType>()->getDecl()];
						if(underl)
						{
							type_ptr->m_ASTNode = underl;
							std::cout << "Resolved to " << underl->getScopedName() << std::endl; 
						}
						else 
							throw std::exception("Underlying type failed to resolve");
					}

					type_ptr->m_TypeHeader.is_constant = type->isLocalConstQualified();
					type_ptr->m_TypeHeader.is_volatile = type->isLocalVolatileQualified();
				}
			} // General case
		} // Non built in type
		//Generate name
		std::cout << "Finalizing type " << std::endl;
		type_ptr->m_QualifiedName = type->getAsString();
		type_ptr->m_TypeHeader.is_stl_type = (type_ptr->m_QualifiedName.find("std::") != std::string::npos);
		type_ptr->m_TypeHeader.is_user_type = !(type_ptr->m_TypeHeader.is_builtin && type_ptr->m_TypeHeader.is_stl_type);

		tree_ptr->addType(type_ptr);
	} // Type not found
	std::cout << "End of type resolving\n" << std::endl; 
	return type_ptr;
}

void ASTTreeWalker::visitVarDecl( clang::VarDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();
	if(spec == AS_private)//We do ignore private access.
		return;
}

void ASTTreeWalker::visitTypedef( clang::TypedefDecl* decl )
{
	AccessSpecifier spec = decl->getAccess();
	if(spec == AS_private)//We do ignore private access.
		return;

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
			if(decl->getAccess() == AS_protected)
				node->setAccessType(CppNode::ACCESS_TYPE_PROTECTED);

			node->setAliasType(resolveQualType(&decl->getUnderlyingType()).get());

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
	if(spec == AS_private)//We do ignore private access.
		return;
}
