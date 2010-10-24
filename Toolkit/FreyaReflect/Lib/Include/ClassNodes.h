#ifndef ClassNodes_h__
#define ClassNodes_h__

#include "CppNode.h"
#include "CppType.h"

#include <vector>
#include <cstdlib>
//Class node itself
class	ClassMethodException : public std::exception
{
public:
	ClassMethodException(const std::string& msg) : m_What(std::string("[ASTParser]: class method: ") + msg) {}
	virtual  ~ClassMethodException(){}
	virtual const char *  what() const
	{
		return m_What.c_str();
	}
private:
	std::string		m_What;
};

class EXPORT ClassNode : public CppNode
{
public:
	enum BASE_TYPE
	{
		PRIVATE = 0,
		PROTECTED = 1,
		PUBLIC = 2,
		VIRTUAL = 3
	};

	ClassNode(const std::string& class_name, CppNode* parent) : CppNode(NODE_TYPE_CLASS,parent,class_name)
	{}
	virtual ~ClassNode(){}

	typedef std::vector<cpp_type*> base_class_list_t;

	size_t				baseCount() const {return m_BaseClassList.size();}
	cpp_type*			getBase(size_t idx){return m_BaseClassList.at(idx);}
	void				addBase(cpp_type* node){m_BaseClassList.push_back(node);}

private:
	base_class_list_t				m_BaseClassList;
};

class EXPORT AnonymousStructNode : public CppNode
{
public:
	AnonymousStructNode(CppNode* parent) : CppNode(NODE_TYPE_ANONYMOUS_STRUCT,parent,"")
	{}
	virtual ~AnonymousStructNode(){}


};

class EXPORT ClassMethod : public CppNode
{
public:
	ClassMethod(const std::string& method_name, 
		bool const_method, bool virtual_method, bool static_method, CppNode* parent) : CppNode(NODE_TYPE_CLASS_METHOD,parent,method_name)
	{
		//if((const_method) && static_method)
		//	throw ClassMethodException(std::string("static method could not be either virtual, nor const: ") + method_name);
		m_ConstantMethod = const_method;
		m_VirtualMethod  = virtual_method;
		m_StaticMethod   = static_method;
	}


	void						setReturnValue(const cpp_type * type) {m_ReturnValue = type;}
	const cpp_type*				returnValue() const {return m_ReturnValue;}

	typedef std::pair<const cpp_type*, const std::string>		argument_t;
	typedef std::vector<argument_t>						argument_list_t;	
	typedef argument_list_t::iterator					argument_list_iterator_t;
	typedef argument_list_t::const_iterator				argument_list_const_iterator_t;

	void						addArgument(const cpp_type* type, const std::string& param_name = "")
	{
		std::string name(param_name);
		char	buf[16];
		if(name == "")
			name = std::string("__") + itoa(m_ArgumentList.size(),buf,10);
		m_ArgumentList.push_back(std::make_pair(type,name));
	}

	argument_list_iterator_t	argumentsListBegin()
	{
		return m_ArgumentList.begin();
	}

	argument_list_iterator_t	argumentsListEnd()
	{
		return m_ArgumentList.end();
	}

	argument_list_const_iterator_t	argumentsListBegin() const
	{
		return m_ArgumentList.begin();
	}

	argument_list_const_iterator_t	argumentsListEnd() const
	{
		return m_ArgumentList.end();
	}

	size_t						argumentsCount() const
	{
		return m_ArgumentList.size();
	}

private:
	bool			m_ConstantMethod;
	bool			m_VirtualMethod;
	bool			m_StaticMethod;

	const cpp_type* m_ReturnValue;

	argument_list_t	m_ArgumentList;

	
};

#endif // ClassNodes_h__