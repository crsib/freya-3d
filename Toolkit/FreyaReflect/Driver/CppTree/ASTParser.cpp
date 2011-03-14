#include "CppTree/ASTParser.h"
#include <llvm/Support/CommandLine.h>
#include <CppTree/ASTTreeWalker.h>
#include <llvm/Support/Path.h>
#include <clang/Basic/FileSystemOptions.h>
#include <llvm/Support/raw_ostream.h>
#include <ctime>
//Language flags
extern llvm::cl::opt<bool>			UseC99;
extern llvm::cl::opt<bool>			UseC;
extern llvm::cl::opt<bool>			UseMSVS;
extern llvm::cl::opt<bool>			UseRTTI;
extern llvm::cl::opt<bool>			UseCpp0x;

///// Dirty hack
class MyTextDiagnosticPrinter : public clang::TextDiagnosticPrinter
{
public:
	MyTextDiagnosticPrinter(llvm::raw_ostream &os, const clang::DiagnosticOptions &diags, bool _OwnsOutputStream = false) : 
	  clang::TextDiagnosticPrinter(os, diags,_OwnsOutputStream) {}

	virtual void HandleDiagnostic(clang::Diagnostic::Level Level,const clang::DiagnosticInfo &Info)
	{
		if(Level >= clang::Diagnostic::Error)
			clang::TextDiagnosticPrinter::HandleDiagnostic(Level,Info);
	}
};
///// End of dirty hack

namespace __internal
{
	unsigned user_supplied_nodes = 0;
	unsigned used_nodes = 0;

	//First pass marker
	class FirstPassTraversal : public CppNodeVisitor
	{
	public:
		FirstPassTraversal()
		{
			user_supplied_nodes = 0;
			used_nodes = 0;
		}
		virtual void	visit(CppNodeScope* n) 
		{
			for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it )
			{
				CppNodePtr node = *it;
				if(node->getAccessType() == CppNode::ACCESS_TYPE_PRIVATE)
					continue;
				CppNode::NODE_FLAG node_flag = node->getNodeFlag();
				CppNode::NODE_FLAG parent_flag = node->getParent()->getNodeFlag();
				// Check the node flag
				if ( 
					( node_flag   == CppNode::NODE_FLAG_USER_SUPPLIED ) //|| 
					//( node_flag   == CppNode::NODE_FLAG_USED ) 
					)
				{
					user_supplied_nodes++;
					node->acceptVisitor(*this); // Just pass to another visitor
				}
				else if( // Check parent node
					node->getParent()->getParent() &&
					( parent_flag == CppNode::NODE_FLAG_USER_SUPPLIED ) //||
					//( parent_flag == CppNode::NODE_FLAG_USED )
					)
				{
					used_nodes++;
					node->setNodeFlag(CppNode::NODE_FLAG_USED); // Mark as used
					node->acceptVisitor(*this); // And parse down
				}
			}
		}
		
		virtual void	visit(CppNodeNamespace* n) { if(n->getNodeFlag() != CppNode::NODE_FLAG_USER_SUPPLIED) n->setNodeFlag(CppNode::NODE_FLAG_USED); visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeEnum* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeClass* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeClassTemplateSpecialization* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeAnonymousStruct* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeAnonymousUnion* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual	void	visit(CppNodeUnion* n) { visit(static_cast<CppNodeScope*>(n)); }
		virtual void	visit(CppNodePointer* n) 
		{
			if( n->getPointeeType()->getUserType() && !n->getPointeeType()->isBuiltin() )
			{
				if( n->getPointeeType()->getUserType()->getNodeFlag() > CppNode::NODE_FLAG_USED )
				{
					used_nodes++;
					n->getPointeeType()->getUserType()->setNodeFlag(CppNode::NODE_FLAG_USED);
					n->getPointeeType()->getUserType()->acceptVisitor(*this);
				}
			}
		}
		virtual void	visit(CppNodeReference* n) 
		{
			if( n->getReferencedType()->getUserType() && !n->getReferencedType()->isBuiltin())
			{
				if( n->getReferencedType()->getUserType()->getNodeFlag() > CppNode::NODE_FLAG_USED )
				{
					used_nodes++;
					n->getReferencedType()->getUserType()->setNodeFlag(CppNode::NODE_FLAG_USED);
					n->getReferencedType()->getUserType()->acceptVisitor(*this);
				}
			}
		}

		virtual void	visit(CppNodeTypedef* n)
		{
			if( n->getAliasType()->getUserType() && !n->getAliasType()->isBuiltin() )
			{
				if( n->getAliasType()->getUserType()->getNodeFlag() > CppNode::NODE_FLAG_USED )
				{
					used_nodes++;
					n->getAliasType()->getUserType()->setNodeFlag(CppNode::NODE_FLAG_USED);
					n->getAliasType()->getUserType()->acceptVisitor(*this);
				}
			}

		}
	};

}

CppTreePtr prepareASTTree( 
	const std::string& include_path,
	const std::vector<std::string>& header_paths, 
	const std::vector<std::string>& search_paths, 
	const std::vector<std::string>& defs, 
	const std::vector<std::string>& undefs )
{
	clock_t start = clock();
	//CppTree
	clang::DiagnosticOptions diagnosticOptions;
	diagnosticOptions.IgnoreWarnings = true;
	diagnosticOptions.ShowColors = true;
	diagnosticOptions.ShowFixits = false;
	//diagnosticOptions.
	clang::TextDiagnosticPrinter *pTextDiagnosticPrinter =
		new MyTextDiagnosticPrinter(
		llvm::outs(),
		diagnosticOptions);
	llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> ids(new clang::DiagnosticIDs);
	clang::Diagnostic diagnostic(ids,pTextDiagnosticPrinter);

	clang::LangOptions languageOptions;
	languageOptions.CPlusPlus = !(UseC.getValue() || UseC99.getValue());
	languageOptions.Microsoft = 0;//UseMSVS.getValue();
	languageOptions.Bool = true;
	languageOptions.CPlusPlus0x = UseCpp0x.getValue();
	languageOptions.Exceptions = languageOptions.CPlusPlus;
	languageOptions.C99 = UseC99.getValue() || languageOptions.CPlusPlus;
	languageOptions.RTTI = languageOptions.CPlusPlus && UseRTTI.getValue();
	languageOptions.GNUKeywords = 1;
	//languageOptions.
	//languageOptions.NoBuiltin = 1;
	
	clang::FileSystemOptions filesystemOpts;
	clang::FileManager fileManager(filesystemOpts);
	
	//filesystemOpts
	clang::SourceManager sourceManager(diagnostic,fileManager);
	clang::HeaderSearch headerSearch(fileManager);

	clang::HeaderSearchOptions headerSearchOptions;
	headerSearchOptions.UseBuiltinIncludes = 1;
	headerSearchOptions.UseStandardCXXIncludes = 0;
	headerSearchOptions.UseStandardIncludes = 1;
	
	headerSearchOptions.Verbose = BeVerbose;
	headerSearchOptions.ResourceDir = include_path;

	for(size_t i = 0; i < search_paths.size(); ++i)
		headerSearchOptions.AddPath(search_paths[i],clang::frontend::Angled,true,false,false);

	clang::TargetOptions targetOptions;
	targetOptions.Triple = llvm::sys::getHostTriple();
	targetOptions.Features.push_back("+sse");
	targetOptions.Features.push_back("+sse2");

	clang::TargetInfo *pTargetInfo = 
		clang::TargetInfo::CreateTargetInfo(
		diagnostic,
		targetOptions);

	//pTargetInfo->getTargetBuiltins

	clang::ApplyHeaderSearchOptions(
		headerSearch,
		headerSearchOptions,
		languageOptions,
		pTargetInfo->getTriple());

	clang::Preprocessor preprocessor(
		diagnostic,
		languageOptions,
		*pTargetInfo,
		sourceManager,
		headerSearch);
	//pTargetInfo->setFeatureEnabled(preprocessor.getFut)
	clang::PreprocessorOptions preprocessorOptions;
	//preprocessor.
	preprocessorOptions.UsePredefines = 1;

	for(size_t i = 0; i < defs.size(); ++i)
		preprocessorOptions.addMacroDef(defs[i]);

	for(size_t i = 0; i < undefs.size(); ++i)
		preprocessorOptions.addMacroUndef(undefs[i]);


	clang::FrontendOptions frontendOptions;

	frontendOptions.FixWhatYouCan = true;
	frontendOptions.ShowTimers = BeVerbose.getValue();
	frontendOptions.ShowStats = BeVerbose.getValue();

	preprocessor.getBuiltinInfo().InitializeBuiltins(preprocessor.getIdentifierTable(),languageOptions);
	clang::InitializePreprocessor(
		preprocessor,
		preprocessorOptions,
		headerSearchOptions,
		frontendOptions);
	 
	//Create temp file
	llvm::sys::Path tmp;
	tmp.createTemporaryFileOnDisk();
	
	if(BeVerbose)
		std::clog << "Creating " << tmp.c_str() << std::endl;
	std::string err;
	llvm::raw_fd_ostream os (tmp.c_str(),err);
	os << "#define FREYA_REFLECT 1\n\n";
	//if(UseMSVS && UseCpp0x)
	{
		os <<	"#ifdef FREYA_REFLECT\n"
				"#include <stdint.h>\n"
				"#define __int32 int\n"
				"#define __int64 long long int\n"
				"#define __w64 \n"
				"#ifdef _MSC_VER\n#undef _MSC_VER\n#endif\n"
			    "#endif\n";
	}

	if(!UseCpp0x)
		os <<	"#define nullptr (int(0))\n"
				"#define _LIBCPP_HAS_NO_UNICODE_CHARS\n";

	os <<	"#ifndef NULL\n"
			"#define NULL 0\n"
			"#endif\n"
			"#define _HAVE_STDC\n"
			"#ifndef CHAR_BIT\n"
			"#define CHAR_BIT 8\n"
			"#endif \n"
			"#undef __STRICT_ANSI__\n"
			"#define __NO_CTYPE_INLINES\n"
			"#define __MINGW_IMPORT\n"
			"#define _POSIX_THREADS 1\n"; // This is a newlib workarouds, so they are applied gloabally

	if(!UseC && !UseC99)
		os << "#define __STDC_VERSION__  199901L\n"; //This will make newlib to enable some C99 futures, like snprintf
	os << "\n\n//Headers\n\n";

	for(size_t i = 0; i < header_paths.size(); ++i)
		os << "#include \"" << header_paths[i] << "\"\n";
	os << "\n";
	os.flush();
	os.close();

	const clang::FileEntry *pFile = fileManager.getFile(tmp.c_str());
	sourceManager.createMainFileID(pFile);
	//preprocessor.EnterMainSourceFile();

	const clang::TargetInfo &targetInfo = *pTargetInfo;

	clang::IdentifierTable identifierTable(languageOptions);
	clang::SelectorTable selectorTable;

	clang::Builtin::Context builtinContext(targetInfo);
	clang::ASTContext astContext(
		languageOptions,
		sourceManager,
		targetInfo,
		identifierTable,
		selectorTable,
		builtinContext,
		0 /* size_reserve*/);
	// clang::ASTConsumer astConsumer;
	ASTTreeWalker astConsumer;
	astConsumer.source_manager = &sourceManager;
	astConsumer.locations_to_parse = boost::unordered_set<std::string>(header_paths.begin(), header_paths.end());

	pTextDiagnosticPrinter->BeginSourceFile(languageOptions,&preprocessor);

	clang::ParseAST(preprocessor, &astConsumer, astContext); 

	if(BeVerbose)
		std::clog << "Finished parsing. Cleaning the tree up" << std::endl;
	astConsumer.tree_ptr->getRootNode()->acceptVisitor(__internal::FirstPassTraversal());

	if(BeVerbose)
	{
		std::clog << "Parsing complete in: " << (float)(clock() - start) / (float)CLOCKS_PER_SEC << std::endl; 
		sourceManager.PrintStats();
		preprocessor.PrintStats();
		headerSearch.PrintStats();
		astContext.PrintStats();	
	}
	pTextDiagnosticPrinter->EndSourceFile();
	//delete pTextDiagnosticPrinter;
	tmp.eraseFromDisk();

	//delete pTextDiagnosticPrinter;

	return astConsumer.tree_ptr;
}
