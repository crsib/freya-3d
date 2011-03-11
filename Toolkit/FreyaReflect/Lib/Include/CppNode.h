#ifndef _CPP_NODE_H_
#define _CPP_NODE_H_

#include "internal.h"

#include <string>
#include <vector>

class CppNode;

typedef std::vector<CppNode*>				NodeList;
typedef NodeList::iterator					NodeListIterator;
typedef NodeList::reverse_iterator			NodeListReverseIterator;
typedef NodeList::const_iterator			NodeListConstIterator;
typedef NodeList::const_reverse_iterator	NodeListConstReverseIterator;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	CppNode
///
/// \brief	Base class for all cpp nodes 
///
/// \author	Crsib
/// \date	5/16/2010
////////////////////////////////////////////////////////////////////////////////////////////////////

class EXPORT CppNode
{
public:
	enum NODE_TYPE
	{
		NODE_TYPE_UNKNOWN,
		NODE_TYPE_NAMESPACE,
		NODE_TYPE_FUNCTION,
		NODE_TYPE_TEMPLATE_FUNCTION,
		NODE_TYPE_CLASS,
		NODE_TYPE_ANONYMOUS_STRUCT,
		NODE_TYPE_CLASS_TEMPLATE,
		NODE_TYPE_CLASS_CONSTRUCTOR,
		NODE_TYPE_CLASS_COPY_CONSTRUCTOR,
		NODE_TYPE_CLASS_DESTRUCTOR,
		NODE_TYPE_CLASS_METHOD,
		NODE_TYPE_CLASS_PROPERTY,
		NODE_TYPE_CLASS_FIELD,
		NODE_TYPE_ENUM,
		NODE_TYPE_ENUM_VALUE,
		NODE_TYPE_CONSTANT,
		NODE_TYPE_GLOBAL_VARIABLE,
		NODE_TYPE_TYPEDEF,
		NODE_TYPE_TEMPLATE_SPECIALIZATION,
		NODE_TYPE_STL_SPECIALIZATION
	};
private:
	CppNode();
	CppNode(const CppNode&);
	CppNode& operator = (const CppNode& node);
public:
	CppNode(NODE_TYPE tp, CppNode* parent, const std::string& short_name) : m_NodeType(tp), m_Parent(parent),m_ShortName(short_name) {}
	virtual ~CppNode()
	{
		for(size_t i = 0; i < m_NodeList.size(); ++i)
			delete m_NodeList[i];
	}

	

	NODE_TYPE		getNodeType() const
	{
		return m_NodeType;
	}
	std::string		getNodeTypeName() const
	{
		extern const char* NODE_NAMES [];
		return NODE_NAMES[m_NodeType];
	}
	std::string		getShortName() const
	{
		return m_ShortName;
	}

	virtual
		std::string		getQualifiedName() const
	{
		if(m_Parent)
			return m_Parent->getQualifiedName() + "::" + m_ShortName;
		else
			return m_ShortName;
	}
	template<typename T>
	T&					convertToType()
	{
		return dynamic_cast<T&>(*this);
	}

	size_t				nodeCount()
	{
		return m_NodeList.size();
	}

	CppNode*			nodeAt(size_t i)
	{
		return m_NodeList.at(i);
	}

	CppNode*			operator [] (size_t i)
	{
		return m_NodeList[i];
	}

	const CppNode*
						nodeAt(size_t i) const
	{
		return m_NodeList.at(i);
	}

	const CppNode*		operator [] (size_t i) const
	{
		return m_NodeList[i];
	}

	NodeListIterator	begin()
	{
		return m_NodeList.begin();
	}

	NodeListConstIterator begin() const
	{
		return m_NodeList.begin();
	}

	NodeListIterator	end() 
	{
		return m_NodeList.end();
	}

	NodeListConstIterator	end() const
	{
		return m_NodeList.end();
	}

	NodeListReverseIterator	rbegin()
	{
		return m_NodeList.rbegin();
	}

	NodeListConstReverseIterator rbegin() const
	{
		return m_NodeList.rbegin();
	}

	NodeListReverseIterator	rend() 
	{
		return m_NodeList.rend();
	}

	NodeListConstReverseIterator	rend() const
	{
		return m_NodeList.rend();
	}

	CppNode*			getNodeNamed(const std::string& name);
	const CppNode*		getNodeNamed(const std::string& name) const;

	void				addNode(CppNode* node)
	{
		m_NodeList.push_back(node);
	}

protected:
	NODE_TYPE			m_NodeType;
	NodeList			m_NodeList;
	CppNode*			m_Parent;
	std::string			m_ShortName;
};

#endif