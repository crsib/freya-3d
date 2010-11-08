#include "CppTree/CppNode.h"

std::string CppNode::getScopedName() const
{
	if(m_ParentNode && m_ParentNode->getParent()) //The only one node has NULL parent - the outermost namespace
		return m_ParentNode->m_NodeName + "::" + m_NodeName;
	else 
		return m_NodeName;
}

CppNodePtr  CppNodeScope::getChildByName(const std::string& name)
{
	for(node_array_const_iterator_t it = m_Children.begin(), end = m_Children.end();
		it != end; ++it)
	{
		if((*it)->getNodeName() == name)
			return *it;
	}
	return CppNodePtr();
}