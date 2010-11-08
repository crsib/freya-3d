#ifndef CppNode_h__
#define CppNode_h__

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class CppNode;

//Node specializations
class CppNodeScope;
class CppNodeVariableDecl;
class CppNodeNamespace;
class CppNodeEnum;
class CppNodeEnumValue;
class CppNodeFunction;
class CppNodeFunctionTemplateSpecialization;
class CppNodeGlobalVariable;
class CppNodeGlobalConstant;
class CppNodeTypedef;
class CppNodeClass;
class CppNodeClassTemplateSpecialization;
class CppNodeAnonymousStruct;
class CppNodeAnonymousUnion;
class CppNodeUnion;
class CppNodeClassMethod;
class CppNodeClassConstructor;
class CppNodeClassCopyConstructor;
class CppNodeClassDestructor;
class CppNodeClassOperatorEqual;
class CppNodeClassMember;
class CppNodeConversionOperator;

class CppNodeVisitor
{
public: 
	virtual ~CppNodeVisitor() {}

	virtual void	visit(CppNode* n) {}
	virtual void	visit(CppNodeScope* n) {}
	virtual void	visit(CppNodeVariableDecl* n ) {}
	virtual void	visit(CppNodeNamespace* n) {}
	virtual	void	visit(CppNodeEnum* n){ }
	virtual void    visit(CppNodeEnumValue* n) {}
	virtual void	visit(CppNodeFunction* n) {}
	virtual void	visit(CppNodeFunctionTemplateSpecialization* n) {}
	virtual void	visit(CppNodeGlobalVariable* n) {}
	virtual void	visit(CppNodeGlobalConstant* n) {}
	virtual	void	visit(CppNodeTypedef* n) {}
	virtual	void	visit(CppNodeClass* n) {}
	virtual	void	visit(CppNodeClassTemplateSpecialization* n) {}
	virtual	void	visit(CppNodeAnonymousStruct* n) {}
	virtual	void	visit(CppNodeAnonymousUnion* n) {}
	virtual	void	visit(CppNodeUnion* n) {}
	virtual	void	visit(CppNodeClassMethod* n) {}
	virtual	void	visit(CppNodeClassConstructor* n) {}
	virtual	void	visit(CppNodeClassCopyConstructor* n) {}
	virtual	void	visit(CppNodeClassDestructor* n) {}
	virtual	void	visit(CppNodeClassOperatorEqual* n) {}
	virtual	void	visit(CppNodeClassMember* n) {}
	virtual void	visit(CppNodeConversionOperator* n) {}
};

class CppNode
{
	CppNode(const CppNode&);
	CppNode& operator = (const CppNode&);
public:
	enum	NODE_TYPE
	{
		NODE_TYPE_UNKNOWN,
		NODE_TYPE_SCOPE,
		NODE_TYPE_VARIABLE_DECL,
		NODE_TYPE_NAMESPACE,
		NODE_TYPE_ENUM,
		NODE_TYPE_ENUM_VALUE,
		NODE_TYPE_FUNCTION,
		NODE_TYPE_FUNCTION_TEMPLATE_SPECIALIZATION,
		NODE_TYPE_GLOBAL_VARIABLE,
		NODE_TYPE_GLOBAL_CONSTANT,
		NODE_TYPE_TYPEDEF,
		NODE_TYPE_CLASS,
		NODE_TYPE_CLASS_TEMPLATE_SPECIALIZATION,
		NODE_TYPE_ANONYMOUS_STRUCT,
		NODE_TYPE_ANONYMOUS_UNION,
		NODE_TYPE_UNION,
		NODE_TYPE_CLASS_METHOD,
		NODE_TYPE_CLASS_CONSTRUCTOR,
		NODE_TYPE_CLASS_COPY_CONSTRUCTOR,
		NODE_TYPE_CLASS_DESTRUCTOR,
		NODE_TYPE_CLASS_OPERATOR_EQUAL,
		NODE_TYPE_CLASS_CONVERSION_OPERATOR,
		NODE_TYPE_CLASS_MEMBER
	};

	CppNode(CppNode* parent = NULL, NODE_TYPE type = NODE_TYPE_UNKNOWN, const std::string& name = "") 
		: m_NodeType(type), m_ParentNode(parent), m_NodeName(name) {}
	virtual ~CppNode() {}
	virtual void		acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	std::string			getNodeName() const { return m_NodeName; }
	void				setNodeName(const std::string& name) { m_NodeName = name; }

	NODE_TYPE			getNodeType() const { return m_NodeType; }
	CppNode*			getParent() const { return m_ParentNode; }

	std::string			getScopedName() const;
protected:
	std::string			m_NodeName;
	NODE_TYPE			m_NodeType;
	CppNode*			m_ParentNode;
};

typedef boost::shared_ptr<CppNode> CppNodePtr;

class CppNodeScope : public CppNode
{
public:
	CppNodeScope(CppNode* parent = NULL, NODE_TYPE type = NODE_TYPE_SCOPE, const std::string& name = "") : CppNode(parent,type,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
	typedef std::vector< CppNodePtr > node_array_t;
	typedef node_array_t::iterator node_array_iterator_t;
	typedef node_array_t::const_iterator node_array_const_iterator_t;

	size_t	numChildren() const { return m_Children.size(); }
	CppNodePtr at(size_t i) { return m_Children.at(i); }
	CppNodePtr operator [] (size_t i) { return m_Children[i]; }

	node_array_iterator_t  begin()	{ return m_Children.begin(); }
	node_array_iterator_t  end()	{ return m_Children.end();	 }

	node_array_const_iterator_t  begin() const { return m_Children.begin(); }
	node_array_const_iterator_t  end() const { return m_Children.end(); }

	CppNodePtr  getChildByName(const std::string& name);

protected:
	node_array_t		m_Children;
};

class CppNodeVariableDecl : public CppNode
{
public:
	CppNodeVariableDecl(CppNode* parent = NULL, NODE_TYPE type = NODE_TYPE_VARIABLE_DECL, const std::string& name = "") : CppNode(parent,type,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeNamespace : public CppNodeScope
{
public:
	CppNodeNamespace(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_NAMESPACE, name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeEnum : public CppNodeScope
{
public:
	CppNodeEnum(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_ENUM,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeEnumValue : public CppNode
{
public:
	CppNodeEnumValue(const std::string& name, long long int value, CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_ENUM_VALUE, name), m_Value(value) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	long long int		getValue() const { return m_Value; }
private:
	long long int		m_Value;
};

class CppNodeFunction : public CppNode
{
public:
	CppNodeFunction(const std::string& name, CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_FUNCTION, name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeFunctionTemplateSpecialization : public CppNodeFunction
{
public:
	CppNodeFunctionTemplateSpecialization(const std::string& name, CppNode* parent = NULL) 
		: CppNodeFunction(name, parent)
	{m_NodeType = NODE_TYPE_FUNCTION_TEMPLATE_SPECIALIZATION; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeGlobalVariable : public CppNodeVariableDecl
{
public:
	CppNodeGlobalVariable(const std::string& name, CppNode* parent = NULL) : CppNodeVariableDecl(parent,NODE_TYPE_GLOBAL_VARIABLE, name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeGlobalConstant : public CppNodeGlobalVariable
{
public:
	CppNodeGlobalConstant(const std::string& name, CppNode* parent = NULL) : CppNodeGlobalVariable (name,parent) 
	{ m_NodeType = NODE_TYPE_GLOBAL_CONSTANT; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeTypedef : public CppNode
{
public:
	CppNodeTypedef(const std::string& name, CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_TYPEDEF,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClass : public CppNodeScope
{
public:
	CppNodeClass(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_CLASS,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassTemplateSpecialization : public CppNodeClass
{
public:
	CppNodeClassTemplateSpecialization(const std::string& name, CppNode* parent = NULL) 
		: CppNodeClass(name,parent) { m_NodeType = NODE_TYPE_CLASS_TEMPLATE_SPECIALIZATION; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeAnonymousStruct : public CppNodeClass
{
public:
	CppNodeAnonymousStruct(CppNode* parent = NULL) 
		: CppNodeClass("",parent) { m_NodeType = NODE_TYPE_ANONYMOUS_STRUCT; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeUnion : public CppNodeScope
{
public:
	CppNodeUnion(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_UNION,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeAnonymousUnion : public CppNodeUnion
{
public:
	CppNodeAnonymousUnion(CppNode* parent = NULL) 
		: CppNodeUnion("", parent) 
	{ m_NodeType = NODE_TYPE_ANONYMOUS_UNION; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassMethod : public CppNodeFunction
{
public:
	CppNodeClassMethod(const std::string& name, CppNode* parent = NULL) 
		: CppNodeFunction(name,parent) { m_NodeType = NODE_TYPE_CLASS_METHOD; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassConstructor : public CppNodeClassMethod
{
public:
	CppNodeClassConstructor(CppNode* parent = NULL) 
		: CppNodeClassMethod("",parent) { m_NodeType = NODE_TYPE_CLASS_CONSTRUCTOR; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassCopyConstructor : public CppNodeClassMethod
{
public:
	CppNodeClassCopyConstructor(CppNode* parent = NULL) : CppNodeClassMethod("",parent)
	{ m_NodeType = NODE_TYPE_CLASS_COPY_CONSTRUCTOR; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassDestructor : public CppNodeClassMethod
{
public:
	CppNodeClassDestructor(CppNode* parent = NULL) : CppNodeClassMethod("", parent)
	{ m_NodeType = NODE_TYPE_CLASS_DESTRUCTOR; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassOperatorEqual : public CppNodeClassMethod
{
public:
	CppNodeClassOperatorEqual(CppNode* parent = NULL) : CppNodeClassMethod("operator =",parent) 
	{ m_NodeType = NODE_TYPE_CLASS_OPERATOR_EQUAL; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassMember : public CppNodeVariableDecl
{
public:
	CppNodeClassMember(const std::string& name,CppNode* parent = NULL) : CppNodeVariableDecl(parent,NODE_TYPE_CLASS_MEMBER,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeConversionOperator : public CppNode
{
public:
	CppNodeConversionOperator(CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_CLASS_CONVERSION_OPERATOR,"") {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

#endif // CppNode_h__
