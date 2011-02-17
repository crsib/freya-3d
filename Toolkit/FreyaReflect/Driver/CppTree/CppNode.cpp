#include "CppTree/CppNode.h"
#include <boost/lexical_cast.hpp>

std::string CppNode::getScopedName() const
{
	if(m_ParentNode && m_ParentNode->getParent()) //The only one node has NULL parent - the outermost namespace (::)
	{
		if(!m_NodeName.empty())
			return m_ParentNode->getScopedName() + "::" + getNodeName();
		else
			return m_ParentNode->getScopedName();
	}
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
			outp += (*it)->Type->getQualifiedName();
			if(*it != m_ArgumentList.back())
				outp += ", ";
		}
		outp += ")";
	}
	else 
		outp = "(void)";

	return outp;
}

std::string CppNodeFunctionProto::getNodeName() const
{
	return m_NodeName + getProtoString();
}

std::string CppNodeClassTemplateSpecialization::getNodeName() const
{
	std::string name = m_NodeName + "< ";
	size_t last_i = m_TemplateArgumentList.size() - 1;

	for(size_t i = 0; i < last_i; ++i)
	{
		name += m_TemplateArgumentList[i]->getStringValue() + ", ";
	}
	name += m_TemplateArgumentList[last_i]->getStringValue() + " >";

	return name; 
}

std::string CppNodeClassTemplateSpecialization::TemplateArgument::getStringValue()
{
	switch (m_Type)
	{
	case CPP_TYPE:
		return m_CppType->getQualifiedName();
	case INTEGER:
		return boost::lexical_cast<std::string>(m_IntValue);
	case TEMPLATE:
		return m_TemplateName;
	}
	return "unknown";
}

std::string CppNodeClassMethod::getNodeName() const
{
	return m_NodeName + getProtoString() + (m_IsConstant ? " const" : "");
}
