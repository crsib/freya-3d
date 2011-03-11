#ifndef EnumNodes_h__
#define EnumNodes_h__

#include "CppNode.h"

class EXPORT EnumNode : public CppNode
{
public:
	EnumNode(const std::string& enum_name, CppNode* parent) : CppNode(NODE_TYPE_ENUM,parent,enum_name){ }
	virtual ~EnumNode(){}

	virtual
		std::string		getQualifiedName() const
	{
		if(m_Parent)
		{
			std::string ending = m_ShortName.length() ? (std::string("::") + m_ShortName) : "";
			return m_Parent->getQualifiedName() + ending;
		}
		else
			return m_ShortName;
	}

private:

};

class EXPORT EnumValueNode : public CppNode
{
public:
	EnumValueNode(const std::string& enum_name, long long value, CppNode* parent) : CppNode(NODE_TYPE_ENUM_VALUE,parent,enum_name), m_Value(value){ }
	virtual ~EnumValueNode(){}
	
	long long getValue() const
	{
		return m_Value;
	}

	virtual
		std::string		getQualifiedName() const
	{
		if(m_Parent)
			return m_Parent->getQualifiedName() + "::" + m_ShortName;
		else
			return m_ShortName;
	}
private:
	long long		m_Value;
};

#endif // EnumNodes_h__