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

std::string CppNodeFunctionProto::getProtoString() const
{
	std::string outp = "(";
	if(m_ArgumentList.size())
	{
		for(argument_list_const_iterator_t it = m_ArgumentList.begin(), end = m_ArgumentList.end(); it != end; ++it)
		{
			outp += (*it)->getQualifiedName();
			if(*it != m_ArgumentList.back())
				outp += ", ";
		}
		outp += ")";
	}
	else 
		outp = "(void)";
	return outp;
}
