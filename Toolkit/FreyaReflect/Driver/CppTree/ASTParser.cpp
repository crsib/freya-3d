#include "CppTree/ASTParser.h"
#include <llvm/Support/CommandLine.h>
#include <CppTree/ASTTreeWalker.h>
#include <llvm/System/Path.h>
#include <llvm/Support/raw_ostream.h>

//Language flags
extern llvm::cl::opt<bool>			UseC99;
extern llvm::cl::opt<bool>			UseC;
extern llvm::cl::opt<bool>			UseMSVS;
extern llvm::cl::opt<bool>			UseRTTI;
extern llvm::cl::opt<bool>			UseCpp0x;

CppTreePtr prepareASTTree( 
	const std::vector<std::string>& header_paths, 
	const std::vector<std::string>& search_paths, 
	const std::vector<std::string>& defs, 
	const std::vector<std::string>& undefs )
{
	//CppTree
	clang::DiagnosticOptions diagnosticOptions;
	diagnosticOptions.IgnoreWarnings = true;
	//diagnosticOptions.
	clang::TextDiagnosticPrinter *pTextDiagnosticPrinter =
		new clang::TextDiagnosticPrinter(
		llvm::outs(),
		diagnosticOptions);
	clang::Diagnostic diagnostic(pTextDiagnosticPrinter);

	clang::LangOptions languageOptions;
	languageOptions.CPlusPlus = !(UseC.getValue() || UseC99.getValue());
	languageOptions.Microsoft = UseMSVS.getValue();
	languageOptions.Bool = true;
	languageOptions.CPlusPlus0x = UseCpp0x.getValue();
	languageOptions.Exceptions = languageOptions.CPlusPlus;
	languageOptions.C99 = UseC99.getValue();
	languageOptions.RTTI = languageOptions.CPlusPlus && UseRTTI.getValue();

	clang::SourceManager sourceManager(diagnostic);
	clang::FileManager fileManager;
	clang::HeaderSearch headerSearch(fileManager);

	clang::HeaderSearchOptions headerSearchOptions;
	for(size_t i = 0; i < search_paths.size(); ++i)
		headerSearchOptions.AddPath(search_paths[i],clang::frontend::Angled,true,false,true);

	clang::TargetOptions targetOptions;
	targetOptions.Triple = llvm::sys::getHostTriple();

	clang::TargetInfo *pTargetInfo = 
		clang::TargetInfo::CreateTargetInfo(
		diagnostic,
		targetOptions);

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

	clang::PreprocessorOptions preprocessorOptions;
	for(size_t i = 0; i < defs.size(); ++i)
		preprocessorOptions.addMacroDef(defs[i]);

	for(size_t i = 0; i < undefs.size(); ++i)
		preprocessorOptions.addMacroUndef(undefs[i]);

	clang::FrontendOptions frontendOptions;

	frontendOptions.FixWhatYouCan = true;
	frontendOptions.ShowTimers = BeVerbose.getValue();

	clang::InitializePreprocessor(
		preprocessor,
		preprocessorOptions,
		headerSearchOptions,
		frontendOptions);

	//Create temp file
	llvm::sys::Path tmp;
	tmp.createTemporaryFileOnDisk();
	
	std::cout << "Creating " << tmp.c_str() << std::endl;
	std::string err;
	llvm::raw_fd_ostream os (tmp.c_str(),err);
	os << "#define FREYA_REFLECT 1\n\n";
	if(UseMSVS && UseCpp0x)
		os << "#define __nullptr nullptr\n\n";
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

	pTextDiagnosticPrinter->BeginSourceFile(languageOptions,NULL);

	clang::ParseAST(preprocessor, &astConsumer, astContext); 

	tmp.eraseFromDisk();
	return CppTreePtr();
}
