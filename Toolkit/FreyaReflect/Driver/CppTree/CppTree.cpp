#include <CppTree/CppTree.h>
#include <CppTree/CppNode.h>

CppTree::CppTree()
{
	m_RootNode = new CppNodeNamespace("", NULL); //Create root namespace
}

CppTree::~CppTree()
{
	delete m_RootNode;
}