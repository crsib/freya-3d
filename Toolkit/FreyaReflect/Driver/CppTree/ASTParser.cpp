#include "CppTree/ASTParser.h"
#include <llvm/Support/CommandLine.h>
#include <CppTree/ASTTreeWalker.h>
#include <llvm/System/Path.h>
#include <llvm/Support/raw_ostream.h>
#include <ctime>
//Language flags
extern llvm::cl::opt<bool>			UseC99;
extern llvm::cl::opt<bool>			UseC;
extern llvm::cl::opt<bool>			UseMSVS;
extern llvm::cl::opt<bool>			UseRTTI;
extern llvm::cl::opt<bool>			UseCpp0x;

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
	diagnosticOptions.ShowFixits = false;
	//diagnosticOptions.
	clang::TextDiagnosticPrinter *pTextDiagnosticPrinter =
		new clang::TextDiagnosticPrinter(
		llvm::outs(),
		diagnosticOptions);
	clang::Diagnostic diagnostic(pTextDiagnosticPrinter);

	clang::LangOptions languageOptions;
	languageOptions.CPlusPlus = !(UseC.getValue() || UseC99.getValue());
	languageOptions.Microsoft = 0;//UseMSVS.getValue();
	languageOptions.Bool = true;
	languageOptions.CPlusPlus0x = 1;//UseCpp0x.getValue();
	languageOptions.Exceptions = languageOptions.CPlusPlus;
	languageOptions.C99 = UseC99.getValue();
	languageOptions.RTTI = languageOptions.CPlusPlus && UseRTTI.getValue();
	languageOptions.GNUKeywords = 1;
	//languageOptions.
	//languageOptions.NoBuiltin = 1;

	clang::SourceManager sourceManager(diagnostic);
	clang::FileManager fileManager;
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

	preprocessor.getBuiltinInfo().InitializeBuiltins(preprocessor.getIdentifierTable(),preprocessor.getLangOptions().NoBuiltin);
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
	{
		std::clog << "Parsing complete in: " << (float)(clock() - start) / (float)CLOCKS_PER_SEC << std::endl; 
		sourceManager.PrintStats();
		preprocessor.PrintStats();
		headerSearch.PrintStats();
		astContext.PrintStats();	
	}
	tmp.eraseFromDisk();
	return astConsumer.tree_ptr;
}
