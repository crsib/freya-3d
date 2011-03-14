#ifndef XMLWriter_h__
#define XMLWriter_h__

#include "CppTree/CppNode.h"
#include <string>
#include <fstream>
#include <set>

class CppType;

class XMLWriter : public CppNodeVisitor
{
	//Current iteration depth
	unsigned		m_CurrentDepth;
	//Insert tabs into the output stream
	std::string		insertTabs();
	//Output stream handle
	std::ofstream	m_OutputStream;
	//Tree top
	CppNode*		m_TreeTop;

	std::set<CppType*> m_TypesCache;
public:
	XMLWriter(CppNode* tree_top, const std::string& _path);
	~XMLWriter();
	virtual void	visit(CppNode* n);
	virtual void	visit(CppNodeScope* n);
	virtual void	visit(CppNodeVariableDecl* n );
	virtual void	visit(CppNodeNamespace* n);
	virtual	void	visit(CppNodeEnum* n);
	virtual void    visit(CppNodeEnumValue* n);
	virtual void	visit(CppNodeFunctionProto* n);
	virtual void	visit(CppNodeFunction* n);
	virtual void	visit(CppNodeFunctionTemplateSpecialization* n);
	virtual void	visit(CppNodeGlobalVariable* n);
	virtual void	visit(CppNodeGlobalConstant* n);
	virtual	void	visit(CppNodeTypedef* n);
	virtual	void	visit(CppNodeClass* n);
	virtual	void	visit(CppNodeClassTemplateSpecialization* n);
	virtual	void	visit(CppNodeAnonymousStruct* n);
	virtual	void	visit(CppNodeAnonymousUnion* n);
	virtual	void	visit(CppNodeUnion* n);
	virtual	void	visit(CppNodeClassMethod* n);
	virtual	void	visit(CppNodeClassConstructor* n);
	virtual	void	visit(CppNodeClassCopyConstructor* n);
	virtual	void	visit(CppNodeClassDestructor* n);
	virtual	void	visit(CppNodeClassOperatorEqual* n);
	virtual	void	visit(CppNodeClassMember* n);
	virtual void	visit(CppNodeConversionOperator* n);
	virtual void	visit(CppNodeClassMemberPointer* n);
	virtual void	visit(CppNodePointer* n);
	virtual void	visit(CppNodeReference* n);
};

#endif // XMLWriter_h__