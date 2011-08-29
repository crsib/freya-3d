/* File         : FreyaReflectBinary: CppNode.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef CppNode_h__
#define CppNode_h__

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "CppTree/CppType.h"

class CppNode;

//Node specializations
class CppNodeScope;
class CppNodeVariableDecl;
class CppNodeNamespace;
class CppNodeEnum;
class CppNodeEnumValue;
class CppNodeFunctionProto;
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
class CppNodeClassMemberPointer;

class CppNodePointer;
class CppNodeReference;

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
	virtual void	visit(CppNodeFunctionProto* n) {}
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
	virtual void	visit(CppNodeClassMemberPointer* n) {}
	virtual void	visit(CppNodePointer* n) {}
	virtual void	visit(CppNodeReference* n) {}
};

class CppNode : public boost::enable_shared_from_this<CppNode>
{
	CppNode(const CppNode&);
	CppNode& operator = (const CppNode&);
public:
	enum	NODE_TYPE
	{
		NODE_TYPE_UNKNOWN								=	0,
		NODE_TYPE_SCOPE									=	1 << 1,
		NODE_TYPE_VARIABLE_DECL							=	1 << 2,
		NODE_TYPE_NAMESPACE								=	1 << 3,
		NODE_TYPE_ENUM									=	1 << 4,
		NODE_TYPE_ENUM_VALUE							=	1 << 5,
		NODE_TYPE_FUNCTION_PROTO						=	1 << 6,
		NODE_TYPE_FUNCTION								=	1 << 7,
		NODE_TYPE_FUNCTION_TEMPLATE_SPECIALIZATION		=	1 << 8,
		NODE_TYPE_GLOBAL_VARIABLE						=	1 << 9,
		NODE_TYPE_GLOBAL_CONSTANT						=	1 << 10,
		NODE_TYPE_TYPEDEF								=	1 << 11,
		NODE_TYPE_CLASS									=	1 << 12,
		NODE_TYPE_CLASS_TEMPLATE_SPECIALIZATION			=	1 << 13,
		NODE_TYPE_ANONYMOUS_STRUCT						=	1 << 14,
		NODE_TYPE_ANONYMOUS_UNION						=	1 << 15,
		NODE_TYPE_UNION									=	1 << 16,
		NODE_TYPE_CLASS_METHOD							=	1 << 17,
		NODE_TYPE_CLASS_CONSTRUCTOR						=	1 << 18,
		NODE_TYPE_CLASS_COPY_CONSTRUCTOR				=	1 << 19,		
		NODE_TYPE_CLASS_DESTRUCTOR						=	1 << 20,
		NODE_TYPE_CLASS_OPERATOR_EQUAL					=	1 << 21,
		NODE_TYPE_CLASS_CONVERSION_OPERATOR				=	1 << 22,
		NODE_TYPE_CLASS_MEMBER							=	1 << 23,
		NODE_TYPE_CLASS_MEMBER_POINTER					=	1 << 24,
		NODE_TYPE_POINTER								=	1 << 25,
		NODE_TYPE_REFERENCE								=	1 << 26
	};

	enum ACCESS_TYPE
	{
		ACCESS_TYPE_PUBLIC,
		ACCESS_TYPE_PROTECTED,
		//Private members are ignored, yet we need to parse them due to STL impl
		ACCESS_TYPE_PRIVATE
	};

	enum NODE_FLAG
	{
		//This node is from user supplied header
		NODE_FLAG_USER_SUPPLIED,
		//This node is from external code and is used by user supplied code
		NODE_FLAG_USED,
		//This node is from deserialized AST code
		NODE_FLAG_DESERIALIZED,
		//This node is from external code and is not used by user supplied code
		NODE_FLAG_EXTERNAL,
		
	};

	CppNode(CppNode* parent = NULL, unsigned type = NODE_TYPE_UNKNOWN, const std::string& name = "") 
		: m_NodeType(type), m_ParentNode(parent), m_NodeName(name), m_AccessType(ACCESS_TYPE_PUBLIC),m_NodeFlag(NODE_FLAG_EXTERNAL) {}
	virtual ~CppNode() {}
	virtual void		acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	virtual std::string	getNodeName() const { return m_NodeName; }
	void				setNodeName(const std::string& name) { m_NodeName = name; }

	unsigned			getNodeType() const { return m_NodeType; }
	CppNode*			getParent() const { return m_ParentNode; }

	std::string			getScopedName() const;

	void				setAccessType(ACCESS_TYPE type) { m_AccessType = type; } 
	ACCESS_TYPE			getAccessType() const { return m_AccessType; }

	void				setNodeFlag(NODE_FLAG f) { if( m_NodeFlag == NODE_FLAG_EXTERNAL ) m_NodeFlag = f; }
	NODE_FLAG			getNodeFlag() const		 { return m_NodeFlag; }
	
	void                markDeserialized() { m_NodeFlag = NODE_FLAG_DESERIALIZED; }

	bool				needsReflection() { return (m_NodeFlag == NODE_FLAG_USED || m_NodeFlag == NODE_FLAG_USER_SUPPLIED); }

	template<class T>
	T*					cast_to() { return static_cast<T*>(this); }
protected:
	std::string			m_NodeName;
	unsigned			m_NodeType;
	CppNode*			m_ParentNode;
	ACCESS_TYPE			m_AccessType;
	NODE_FLAG			m_NodeFlag;

friend class ASTTreeWalker;
};

typedef boost::shared_ptr<CppNode> CppNodePtr;

class CppNodeScope : public CppNode
{
public:
	CppNodeScope(CppNode* parent = NULL, NODE_TYPE type = NODE_TYPE_SCOPE, const std::string& name = "") : CppNode(parent,type | NODE_TYPE_SCOPE,name) {}
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

	void		addChild(CppNodePtr child) { m_Children.push_back(child); }

protected:
	node_array_t		m_Children;
};

class CppNodeVariableDecl : public CppNode
{
public:
	CppNodeVariableDecl(CppNode* parent = NULL, NODE_TYPE type = NODE_TYPE_VARIABLE_DECL, const std::string& name = "") : CppNode(parent,type | NODE_TYPE_VARIABLE_DECL,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	void	setType(CppTypePtr type) { m_Type = type; }
	CppTypePtr getCppType() { return m_Type; }
	const CppTypePtr getCppType() const { return m_Type; }

	bool	hasValue() const { return m_HasValue; }
	void	setHasValue(bool h) { m_HasValue = h; }
protected:
	CppTypePtr	m_Type;
	bool		m_HasValue;
};

class CppNodeNamespace : public CppNodeScope
{
public:
	CppNodeNamespace(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_NAMESPACE, name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	bool isAnonymous() const { return m_NodeName == ""; }
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
	void				setValue(const long long int& v) { m_Value = v;}
protected:
	long long int		m_Value;
};

class CppNodeFunctionProto : public CppNode
{
public:
	CppNodeFunctionProto(CppNode* parent = NULL,const std::string& name = "") 
		: CppNode(parent,NODE_TYPE_FUNCTION_PROTO, name) 
	{ 
		m_HasReturnValue = false;
		m_IsOperator = false;
		m_OpType = clang::OO_None;
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	struct argument_t
	{
		CppTypePtr		Type;
		bool			HasDefaultVal;
		argument_t( const CppTypePtr& _type, bool _has_def ) : Type(_type), HasDefaultVal(_has_def) {};
	};

	typedef boost::shared_ptr<argument_t> argument_ptr_t;

	typedef std::vector<argument_ptr_t>	argument_list_t;
	typedef argument_list_t::iterator argument_list_iterator_t;
	typedef argument_list_t::const_iterator argument_list_const_iterator_t;

	argument_list_iterator_t		args_begin() { return m_ArgumentList.begin(); }
	argument_list_const_iterator_t	args_begin() const { return m_ArgumentList.end(); }
	
	argument_list_iterator_t		args_end() { return m_ArgumentList.end(); }
	argument_list_const_iterator_t	args_end() const { return m_ArgumentList.end(); }

	size_t							argumentsCount() const { return m_ArgumentList.size(); }

	void							addArgument(const argument_ptr_t& arg) { m_ArgumentList.push_back(arg); }

	void							setReturnValue(const CppTypePtr& type) { m_ReturnValue = type; m_HasReturnValue = (m_ReturnValue); }
	CppTypePtr						getReturnValue() { return m_ReturnValue; }
	const CppTypePtr				getReturnValue() const { return m_ReturnValue; }

	bool							hasReturnValue() const { return m_HasReturnValue; }
 
	bool							isOverloadedOperator() const { return m_IsOperator; }
	void							setAsOverloadedOperator(bool op, clang::OverloadedOperatorKind kind = clang::OO_None) { m_IsOperator = op; m_OpType = kind;}
	clang::OverloadedOperatorKind   getOverloadedOperatorKind() { return m_OpType; }

	std::string						getProtoString() const; //Return string of form (void) or (const std::string const )

	std::string						getNodeName() const;
	std::string						getFunctionName() const { return m_NodeName; }
protected:
	argument_list_t					m_ArgumentList;
	CppTypePtr						m_ReturnValue;

	bool							m_HasReturnValue;
	bool							m_IsOperator;

	clang::OverloadedOperatorKind	m_OpType;
};

class CppNodeFunction : public CppNodeFunctionProto
{
public:
	CppNodeFunction(const std::string& name, CppNode* parent = NULL) 
		: CppNodeFunctionProto(parent, name) 
	{ 
		m_NodeType |= NODE_TYPE_FUNCTION;
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeFunctionTemplateSpecialization : public CppNodeFunction
{
public:
	CppNodeFunctionTemplateSpecialization(const std::string& name, CppNode* parent = NULL) 
		: CppNodeFunction(name, parent)
	{ m_NodeType |= NODE_TYPE_FUNCTION_TEMPLATE_SPECIALIZATION | NODE_TYPE_FUNCTION; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	argument_list_iterator_t		targs_begin() { return m_TemplateArgumentList.begin(); }
	argument_list_const_iterator_t	targs_begin() const { return m_TemplateArgumentList.end(); }

	argument_list_iterator_t		targs_end() { return m_TemplateArgumentList.end(); }
	argument_list_const_iterator_t	targs_end() const { return m_TemplateArgumentList.end(); }

	size_t							templateArgumentsCount() const { return m_TemplateArgumentList.size(); }
	void							addTemplateArgument(const argument_ptr_t& decl) { m_TemplateArgumentList.push_back(decl); }


protected:
	CppNodeFunction::argument_list_t				m_TemplateArgumentList;
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
	{ m_NodeType = NODE_TYPE_GLOBAL_CONSTANT | NODE_TYPE_GLOBAL_VARIABLE; m_HasValue = true;}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeTypedef : public CppNode
{
public:
	CppNodeTypedef(const std::string& name, CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_TYPEDEF,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	void		setAliasType(CppTypePtr type) { m_AliasType = type; }

	CppTypePtr	getAliasType() { return m_AliasType; }
	const CppTypePtr getAliasType() const { return m_AliasType; }

protected:
	CppTypePtr	m_AliasType;
};

typedef boost::shared_ptr<CppNodeClassMethod> CppNodeClassMethodPtr;
typedef boost::shared_ptr<CppNodeClassMember> CppNodeClassMemberPtr;
class CppNodeClass : public CppNodeScope
{
public:
	CppNodeClass(const std::string& name, CppNode* parent = NULL) : CppNodeScope(parent,NODE_TYPE_CLASS,name), m_WasDefined(false) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	//
	typedef std::pair<CppTypePtr, ACCESS_TYPE>	base_type_t;
	typedef std::vector<base_type_t>			base_type_list_t;
	typedef base_type_list_t::iterator			base_type_list_iterator_t;
	typedef base_type_list_t::const_iterator	base_type_list_const_iterator_t;

	typedef std::vector< CppNodeClassMethodPtr >	method_list_t;
	typedef method_list_t::iterator				method_list_iterator_t;
	typedef method_list_t::const_iterator		method_list_const_iterator_t;

	typedef std::vector< CppNodeClassMemberPtr >	member_list_t;
	typedef member_list_t::iterator				member_list_iterator_t;
	typedef member_list_t::const_iterator		member_list_const_iterator_t;

	base_type_list_iterator_t					bases_begin() { return m_BaseClasses.begin(); }
	base_type_list_const_iterator_t				bases_begin() const { return m_BaseClasses.begin(); }

	base_type_list_iterator_t					bases_end() { return m_BaseClasses.end(); }
	base_type_list_const_iterator_t				bases_end() const { return m_BaseClasses.end(); }
	
	size_t										baseClassCount() const { return m_BaseClasses.size(); }

	void										addBaseClass(const base_type_t& bc) { m_BaseClasses.push_back(bc); }


	method_list_iterator_t						methods_begin() { return m_Metods.begin(); }
	method_list_const_iterator_t				methods_begin() const { return m_Metods.begin(); }

	method_list_iterator_t						methods_end() { return m_Metods.end(); }
	method_list_const_iterator_t				methods_end() const { return m_Metods.end(); }
	
	size_t										methodsCount() const { return m_Metods.size(); }

	void										addMethod(const CppNodeClassMethodPtr& m) { m_Metods.push_back(m); }


	member_list_iterator_t						members_begin() { return m_Members.begin(); }
	member_list_const_iterator_t				members_begin() const { return m_Members.begin(); }

	member_list_iterator_t						members_end() { return m_Members.end(); }
	member_list_const_iterator_t				members_end() const { return m_Members.end(); }
	
	size_t										membersCount() const { return m_Members.size(); }

	void										addMember(const CppNodeClassMemberPtr& m) { m_Members.push_back(m); }

	bool                                        isClassWasDefined() const { return m_WasDefined; }
	void                                        setClassWasDefined(bool def) { m_WasDefined = def; }
protected:
	base_type_list_t							m_BaseClasses;
	member_list_t								m_Members;
	method_list_t								m_Metods;
	bool										m_WasDefined;
};

class CppNodeClassTemplateSpecialization : public CppNodeClass
{
public:
	class TemplateArgument
	{
		TemplateArgument();
		TemplateArgument(const TemplateArgument&);
		TemplateArgument& operator = (const TemplateArgument&);
	public:
		enum TYPE
		{
			CPP_TYPE,
			INTEGER,
			TEMPLATE
		};

		TemplateArgument(CppTypePtr node) : m_Type(CPP_TYPE), m_CppType(node),m_IntValue(0) {}
		TemplateArgument(long long intv) : m_Type(INTEGER), m_IntValue(intv) {}
		TemplateArgument(const std::string& name) : m_Type(TEMPLATE), m_TemplateName(name),m_IntValue(0) {}
		std::string		getStringValue();

		TYPE			getType() const { return m_Type; }
		CppTypePtr		getCppNode() { return m_CppType; }
		long long		getIntValue() const { return m_IntValue; }
		const std::string& getTemplateName() const { return m_TemplateName; }
	private:
		TYPE	m_Type;
		
		CppTypePtr	m_CppType;
		long long	m_IntValue;
		std::string		m_TemplateName;
	};

	typedef boost::shared_ptr<TemplateArgument> TemplateArgumentPtr;
	
	CppNodeClassTemplateSpecialization(const std::string& name, CppNode* parent = NULL) 
		: CppNodeClass(name,parent) { m_NodeType = NODE_TYPE_CLASS_TEMPLATE_SPECIALIZATION | NODE_TYPE_CLASS | NODE_TYPE_SCOPE; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	typedef std::vector<TemplateArgumentPtr>	template_argument_list_t;
	typedef template_argument_list_t::iterator template_argument_list_iterator_t;
	typedef template_argument_list_t::const_iterator template_argument_list_const_iterator_t;
	
	template_argument_list_iterator_t		targs_begin() { return m_TemplateArgumentList.begin(); }
	template_argument_list_const_iterator_t	targs_begin() const { return m_TemplateArgumentList.end(); }

	template_argument_list_iterator_t		targs_end() { return m_TemplateArgumentList.end(); }
	template_argument_list_const_iterator_t	targs_end() const { return m_TemplateArgumentList.end(); }

	size_t							templateArgumentsCount() const { return m_TemplateArgumentList.size(); }
	void							addTemplateArgument(const TemplateArgumentPtr& decl) { m_TemplateArgumentList.push_back(decl); }

	virtual std::string				getNodeName() const;
protected:
	template_argument_list_t		m_TemplateArgumentList;
};

class CppNodeAnonymousStruct : public CppNodeClass
{
public:
	CppNodeAnonymousStruct(CppNode* parent = NULL) 
		: CppNodeClass("",parent) { m_NodeType |= NODE_TYPE_ANONYMOUS_STRUCT; }
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
	{ m_NodeType |= NODE_TYPE_ANONYMOUS_UNION; }
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassMethod : public CppNodeFunction
{
public:
	CppNodeClassMethod(const std::string& name, CppNode* parent = NULL) 
		: CppNodeFunction(name,parent) 
{
	m_NodeType |= NODE_TYPE_CLASS_METHOD; 
	m_IsConstant = false;
}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	void						setMethodConstQualifier(bool c) { m_IsConstant = c; }
	bool						getMethodConstQualifier() const { return m_IsConstant; }

	bool						isVirtual() const { return m_IsVirtual; }
	void						setVirtual(bool v) { m_IsVirtual = v; }

	bool						isAbstract() const { return m_IsVirtual && m_IsAbstract; }
	void						setAbstract(bool a) { m_IsAbstract = a; if(a) m_IsVirtual = true; }

	bool						isStatic() const { return m_IsStatic; }
	void						setStatic(bool s) { m_IsStatic = s; if(s) {m_IsVirtual = m_IsAbstract = m_IsConstant = false;} }

	std::string					getNodeName() const;
protected:
	bool						m_IsConstant;
	bool						m_IsVirtual;
	bool						m_IsAbstract;
	bool						m_IsStatic;
};

class CppNodeClassConstructor : public CppNodeClassMethod
{
public:
	CppNodeClassConstructor(CppNode* parent = NULL) 
		: CppNodeClassMethod("",parent) 
	{ 
		m_NodeType |= NODE_TYPE_CLASS_CONSTRUCTOR; 
		if(m_ParentNode) m_NodeName =  m_ParentNode->getNodeName();
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	bool			isExplicit() const { return m_IsExplicit; }
	void			setExplicit(bool e) { m_IsExplicit = e; }
protected:
	bool			m_IsExplicit;
};

class CppNodeClassCopyConstructor : public CppNodeClassConstructor
{
public:
	CppNodeClassCopyConstructor(CppNode* parent = NULL) : CppNodeClassConstructor(parent)
	{ 
		m_NodeType |= NODE_TYPE_CLASS_COPY_CONSTRUCTOR; 
		if(m_ParentNode) m_NodeName =  m_ParentNode->getNodeName();
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassDestructor : public CppNodeClassMethod
{
public:
	CppNodeClassDestructor(CppNode* parent = NULL) : CppNodeClassMethod("", parent)
	{ 
		m_NodeType |= NODE_TYPE_CLASS_DESTRUCTOR; 
		if(m_ParentNode) m_NodeName =  std::string("~") + m_ParentNode->getNodeName();
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassOperatorEqual : public CppNodeClassMethod
{
public:
	CppNodeClassOperatorEqual(CppNode* parent = NULL) : CppNodeClassMethod("operator =",parent) 
	{ 
		m_NodeType |= NODE_TYPE_CLASS_OPERATOR_EQUAL; 
		m_NodeName = "operator =";
		m_IsOperator = true;
		m_OpType   = clang::OO_Equal;
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
};

class CppNodeClassMember : public CppNodeVariableDecl
{
public:
	CppNodeClassMember(const std::string& name,CppNode* parent = NULL) : CppNodeVariableDecl(parent,NODE_TYPE_CLASS_MEMBER,name) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	bool	isStatic() const { return m_IsStatic; }
	void	setStatic(bool s) { m_IsStatic = s; }
protected:
	bool	m_IsStatic;
};

class CppNodeConversionOperator : public CppNode
{
public:
	CppNodeConversionOperator(CppNode* parent = NULL) : CppNode(parent,NODE_TYPE_CLASS_CONVERSION_OPERATOR,"") 
	{
		m_NodeName = "operator";
	}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	void		setConversionResultType(CppTypePtr type) { m_ConvType = type; }
	//CppTypePtr&	getConversionResultType() { return m_ConvType; }	
	const CppTypePtr& getConversionResultType() const { return m_ConvType; }

protected:
	CppTypePtr	 m_ConvType;
};

class CppNodeClassMemberPointer : public CppNode
{
public:
	CppNodeClassMemberPointer(CppNode* parent = NULL) : CppNode(parent, NODE_TYPE_CLASS_MEMBER_POINTER,"") {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }

	void			setClass(CppNode* c) { m_Class = c; }
	CppNode*		getClass() { return m_Class; }
	const CppNode*	getClass() const { return m_Class; }

	void			setPointeeType(CppTypePtr& c) { m_Type = c;}
	CppTypePtr		getPointeeType(){ return m_Type; }
	const CppTypePtr	getPointeeType() const { return m_Type; }
protected:
	CppNode*		m_Class;
	CppTypePtr		m_Type;
};

class CppNodePointer : public CppNode
{
public:
	CppNodePointer(CppNode* parent = NULL) : CppNode(parent, NODE_TYPE_POINTER,""), m_PointeeType(CppTypePtr()), m_IsArray(false) {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
	
	void				setPointeeType(CppTypePtr& pointee) { m_PointeeType = pointee; }
	//CppTypePtr&			getPointeeType() { return m_PointeeType; }
	const CppTypePtr&	getPointeeType() const { return m_PointeeType; }

	void				setDeclaredAsArray(bool a) { m_IsArray = a; }
	bool				isDeclaredAsArray() const  { return m_IsArray; }
protected:
	CppTypePtr		m_PointeeType;
	bool			m_IsArray;

friend class ASTTreeWalker;
};

class CppNodeReference : public CppNode
{
public:
	enum	REFERENCE_TYPE
	{
		REFERENCE_TYPE_LVALUE,
		REFERENCE_TYPE_RVALUE
	};

	CppNodeReference(CppNode* parent = NULL) : CppNode(parent, NODE_TYPE_REFERENCE,"") {}
	virtual void acceptVisitor(CppNodeVisitor& visitor) { visitor.visit(this); }
	

	
	void			setReferencedType(CppTypePtr& pointee) { m_ReferencedType = pointee; }
	//CppTypePtr&		getReferencedType() { return m_ReferencedType; }
	const CppTypePtr&	getReferencedType() const { return m_ReferencedType; }

	void			setReferenceType(REFERENCE_TYPE type) { m_RefernceType = type; }
	REFERENCE_TYPE	getReferenceType() const { return m_RefernceType; }

protected:
	CppTypePtr		m_ReferencedType;
	REFERENCE_TYPE  m_RefernceType;
friend class ASTTreeWalker;
};

#endif // CppNode_h__
