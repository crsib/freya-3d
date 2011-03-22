#ifndef TreeMarker_h__
#define TreeMarker_h__

#include "CppTree/CppNode.h"

class CppType;

class TreeMarker : public CppNodeVisitor
{
public:
	int				UserSuppliedNodes;
	int				UsedNodes;

	TreeMarker() : UserSuppliedNodes(0), UsedNodes(0) {}
	virtual ~TreeMarker(){}
	virtual void	visit(CppNode* n){}
	virtual void	visit(CppNodeScope* n){}
	virtual void	visit(CppNodeVariableDecl* n );
	virtual void	visit(CppNodeNamespace* n);
	virtual	void	visit(CppNodeEnum* n){}
	virtual void    visit(CppNodeEnumValue* n){}
	virtual void	visit(CppNodeFunctionProto* n);
	virtual void	visit(CppNodeFunction* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual void	visit(CppNodeFunctionTemplateSpecialization* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual void	visit(CppNodeGlobalVariable* n) { visit(static_cast<CppNodeVariableDecl*>(n)); }
	virtual void	visit(CppNodeGlobalConstant* n) { visit(static_cast<CppNodeVariableDecl*>(n)); }
	virtual	void	visit(CppNodeTypedef* n);
	virtual	void	visit(CppNodeClass* n);
	virtual	void	visit(CppNodeClassTemplateSpecialization* n);
	virtual	void	visit(CppNodeAnonymousStruct* n) { visit(static_cast<CppNodeClass*>(n)); }
	virtual	void	visit(CppNodeAnonymousUnion* n) { visit(static_cast<CppNodeUnion*>(n)); }
	virtual	void	visit(CppNodeUnion* n);
	virtual	void	visit(CppNodeClassMethod* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual	void	visit(CppNodeClassConstructor* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual	void	visit(CppNodeClassCopyConstructor* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual	void	visit(CppNodeClassDestructor* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual	void	visit(CppNodeClassOperatorEqual* n) { visit(static_cast<CppNodeFunctionProto*>(n)); }
	virtual	void	visit(CppNodeClassMember* n) { visit(static_cast<CppNodeVariableDecl*>(n)); }
	virtual void	visit(CppNodeConversionOperator* n);
	virtual void	visit(CppNodeClassMemberPointer* n);
	virtual void	visit(CppNodePointer* n);
	virtual void	visit(CppNodeReference* n);
private:
	void			markNode( CppNode* n );

};

#endif // TreeMarker_h__