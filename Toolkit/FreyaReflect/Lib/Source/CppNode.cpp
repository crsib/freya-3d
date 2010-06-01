#include "CppNode.h"

#include <algorithm>

struct		_NodeFindPredicate
{
	explicit _NodeFindPredicate(const std::string& search_name) : m_SearchName (search_name) {}

	bool	operator()(const CppNode* node)
	{
		return (m_SearchName == node->getShortName()) || (m_SearchName == node->getQualifiedName());
	}

	std::string				m_SearchName;
};

CppNode*	CppNode::getNodeNamed(const std::string& name)
{
	NodeListIterator it = std::find_if(m_NodeList.begin(), m_NodeList.end(),_NodeFindPredicate(name));
	if(it != m_NodeList.end())
		return *it;
	else 
		return NULL;
}

const CppNode*	CppNode::getNodeNamed(const std::string& name) const
{
	NodeListConstIterator it = std::find_if(m_NodeList.begin(), m_NodeList.end(),_NodeFindPredicate(name));
	if(it != m_NodeList.end())
		return *it;
	else 
		return NULL;
}