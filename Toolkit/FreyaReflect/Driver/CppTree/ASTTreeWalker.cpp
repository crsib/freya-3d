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
	//
	for(DeclGroupRef::iterator it = d.begin(), end = d.end(); it != end; ++it)
	{
		//if(!isDeclFromUserFile((*it)->getLocation()))
		//	continue;

	}
}

void ASTTreeWalker::handleDeclGroup( clang::DeclGroupRef decl )
{

}
