#include "CppTree/ASTTreeWalker.h"

#include "CppTree/CppNode.h"
#include "CppTree/CppType.h"
#include "CppTree/CppTree.h"

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
		//if(!isDeclFromUserFile((*it)->getLocation()))
		//	continue;
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
		visitEnum(static_cast<EnumDecl*>(decl));
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
			std::clog << "namespace " << node->getScopedName() << std::endl;
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
			std::clog << "enum " << node->getScopedName() << std::endl;
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

			std::clog << "enum value " << eval->getScopedName() << " = " << eval->getValue() << std::endl;
		}
	}
	else
		throw std::exception("scope node is expected");
}
