#include "version.h"
#include <llvm/Support/CommandLine.h>
#include "llvm/Config/config.h"
#include <iostream>

//================================= cl options =========================================================
llvm::cl::opt<char*> OutputFile("o",llvm::cl::desc("Specify output filename. Output will be redirected to stdout if not specified"), llvm::cl::value_desc("filename"));


//======================================================================================================

void	print_version_string()
{
	std::cout << "FreyaReflect version: " << (VERSION_STRING) << "\n"
		<< "LLVM(Clang) version: " << PACKAGE_VERSION;
}

int main (int argc, char* argv[])
{
	//Parse cl options
	llvm::cl::SetVersionPrinter(print_version_string);
	llvm::cl::ParseCommandLineOptions(argc,argv);

	//system("pause");
	return 0;
}