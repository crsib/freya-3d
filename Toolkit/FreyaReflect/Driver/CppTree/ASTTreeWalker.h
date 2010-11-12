#ifndef ASTTreeWalker_h__
#define ASTTreeWalker_h__

#include <iostream>

#include <llvm/Support/CommandLine.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/System/Host.h>

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

extern llvm::cl::opt<bool>			BeVerbose;

class ASTTreeWalker : public clang::ASTConsumer
{
public:
	ASTTreeWalker() : clang::ASTConsumer() { }
	virtual ~ASTTreeWalker() { }
	virtual void HandleTopLevelDecl( clang::DeclGroupRef decl);
};

#endif // ASTTreeWalker_h__