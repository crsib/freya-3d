#include <CppTree/CppTree.h>
#include <CppTree/CppNode.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>

CppTree::CppTree()
{
	m_RootNode = new CppNodeNamespace("", NULL); //Create root namespace
}

CppTree::~CppTree()
{
	delete m_RootNode;
}



CppNode* CppTree::findNode( const std::string& node ) const
{
	std::vector< std::string > tok_list;
	boost::split(tok_list, node, boost::is_any_of("::"), boost::token_compress_on);
	CppNode*  cur_node = m_RootNode;
	for(size_t i = 0; i < tok_list.size() - 1; ++i) //All internal nodes should have NODE_SCOPE as one of the types
	{
		boost::trim(tok_list[i]);
		if(tok_list[i].length())
		{
			if(cur_node->getNodeType() & CppNode::NODE_TYPE_SCOPE)
			{
				cur_node = static_cast<CppNodeScope*>(cur_node)->getChildByName(tok_list[i]).get();
				if(!cur_node)
					return NULL;
			}
			else
				return NULL;
		}//if(tok_list[i].length())
	}//for(size_t i = 0; i < tok_list.size() - 1; ++i)
	//Ok, now the behavior will be different for different scopes.
	//The most easy case - curr_node is still a scope and a name cam be retrieved from a scope
	unsigned node_type = cur_node->getNodeType();

	if(cur_node->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		CppNode* tmp = static_cast<CppNodeScope*>(cur_node)->getChildByName(tok_list.back()).get();
		if(tmp)
			return tmp;
	}
	//The easiest of cases left
	//This is a class member
	if(cur_node->getNodeType() & CppNode::NODE_TYPE_CLASS)
	{
		for(CppNodeClass::member_list_const_iterator_t 
			it = static_cast<CppNodeClass*>(cur_node)->members_begin(),
			end = static_cast<CppNodeClass*>(cur_node)->members_end();
			it != end; ++it)
				if ((*it)->getNodeName() == tok_list.back())
					return *it;
	}
	//This one is a function pointer.
	

	return NULL;
}
