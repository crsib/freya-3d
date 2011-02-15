#ifndef ASTTreeWalker_h__
#define ASTTreeWalker_h__

#include <iostream>
#include <vector>
#include <vector>
#include <boost/unordered/unordered_set.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <string>

#include <llvm/Support/CommandLine.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Host.h>

#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>

#include <clang/Basic/LangOptions.h>

#include <clang/Basic/SourceManager.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Basic/FileManager.h>

#include <clang/Frontend/HeaderSearchOptions.h>
#include <clang/Frontend/Utils.h>

#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/TargetInfo.h>

#include <clang/Lex/Preprocessor.h>
#include <clang/Frontend/PreprocessorOptions.h>
#include <clang/Frontend/FrontendOptions.h>

#include <clang/Basic/IdentifierTable.h>
#include <clang/Basic/Builtins.h>

#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Sema/Sema.h>
#include <clang/AST/DeclBase.h>
#include <clang/AST/Type.h>
#include <clang/AST/Decl.h>
#include <clang/Sema/Lookup.h>
#include <clang/Sema/Ownership.h>
#include <clang/AST/DeclGroup.h>

#include <clang/Parse/Parser.h>

#include <clang/Parse/ParseAST.h>

#include "CppTree/CppTree.h"

#include <boost/shared_ptr.hpp>

class CppNode;
typedef boost::shared_ptr<CppNode> CppNodePtr;

class CppType;


extern llvm::cl::opt<bool>			BeVerbose;
//This class is private by it nature. So I dont' see any reason for nice and encapsulated OO code here
class ASTTreeWalker : public clang::ASTConsumer
{
public:
	ASTTreeWalker();
	virtual ~ASTTreeWalker() { }
	//************************************
	// Method:    HandleTopLevelDecl
	// FullName:  ASTTreeWalker::HandleTopLevelDecl
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: clang::DeclGroupRef decl
	//************************************
	virtual void HandleTopLevelDecl( clang::DeclGroupRef decl);

	//Public properties
	clang::SourceManager*					source_manager;
	boost::unordered_set<std::string>		locations_to_parse;

	std::stack<CppNode*>					node_stack;

	CppTreePtr								tree_ptr;

protected:
	CppNode*										m_RootNode;
	boost::unordered_map<clang::Decl*,CppNode*>		m_DirectSearchMap;
	boost::unordered_map<CppNode*,clang::Decl*>		m_ReverseSearchMap;
	boost::unordered_map<std::string, CppNodePtr>		m_TemplateSpecializationLookup;

	bool			isDeclFromUserFile(clang::SourceLocation loc);

	void			visitNamespaceDecl(clang::NamespaceDecl* decl);
	void			visitDeclContext(clang::DeclContext* decl);
	void			visitEnum(clang::EnumDecl* decl);
	void			visitClass(clang::RecordDecl* decl);

	CppTypePtr		resolveQualType(clang::QualType* type);
	void			visitVarDecl(clang::DeclaratorDecl* decl);
	void			visitTypedef(clang::TypedefDecl* decl);
	void			visitFunction(clang::FunctionDecl* decl);

	void			chooseVisitor( clang::Decl* decl );

};

#endif // ASTTreeWalker_h__