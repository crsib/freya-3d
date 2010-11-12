#include "version.h"
//LLVM includes
#include <llvm/System/Path.h>
#include <llvm/Support/Regex.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Config/config.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CppTree/ASTParser.h"

//================================= cl options =========================================================
//Output flags
llvm::cl::opt<std::string>	ReflectionOutputFile("refl-output",llvm::cl::desc("Specify output filename for reflection file. Use stdout to redirect output to standard output"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>	LuaOutputFile("lua-output",llvm::cl::desc("Specify output filename for Lua bindings file.  Use stdout to redirect output to standard output"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>  XMLOutputFile("xml-output",llvm::cl::desc("Specify output filename for XML deserialization of AST.  Use stdout to redirect output to standard output"),llvm::cl::value_desc("filename"));
//Input flags
llvm::cl::opt<bool>			RecursiveScan("R", llvm::cl::desc("Treat input as a directory and scan it recursively for header files. Supported extensions are (*.h;*.hpp;*.ipp;*.hxx)"));
//Generators flag
llvm::cl::opt<bool>			EmitInterfaceImplemetationsToLua("lua-emit-impl-classes",
	llvm::cl::desc("Generate Lua bindings for classes, that just implement the interface. Will produce larger output."));
llvm::cl::opt<std::string>	UseCustomAllocModel("use-custom-alloc",
	llvm::cl::desc("Make the output classes to be ancestors of class, which overrides memory management operators. This base class must be reflected."),
	llvm::cl::value_desc("qualified class name"));
llvm::cl::opt<bool>			UseLuaJit("use-luajit",
	llvm::cl::desc("Generate JIT controlling code. Requires LuaJIT 2.0 backend to work"));
//Preprocessor flags
llvm::cl::list<std::string> IncludeDirs("I",llvm::cl::desc("Global include directory"),llvm::cl::value_desc("directory"),llvm::cl::Prefix);
llvm::cl::list<std::string> Definitions("D",llvm::cl::desc("Defines a preprocessor definition. Uses default GCC syntax"),llvm::cl::value_desc("directory"),llvm::cl::Prefix);
llvm::cl::list<std::string> UnDefinitions("U",llvm::cl::desc("Undefines a preprocessor definition."),llvm::cl::value_desc("directory"),llvm::cl::Prefix);

//Language flags
extern llvm::cl::opt<bool>			UseC99;
extern llvm::cl::opt<bool>			UseC;
extern llvm::cl::opt<bool>			UseCpp0x;
extern llvm::cl::opt<bool>			UseMSVS;
extern llvm::cl::opt<bool>			UseRTTI;

llvm::cl::opt<bool>					UseC99("c99",llvm::cl::desc("Treat input language as C99"));
llvm::cl::opt<bool>					UseC("c",llvm::cl::desc("Treat input language as C"));
llvm::cl::opt<bool>					UseCpp0x("c++0x",llvm::cl::desc("Enable some C++0x features. Use Clang documentation for the full list of supported features"));
llvm::cl::opt<bool>					UseMSVS("msvc",llvm::cl::desc("Enable Microsoft's extensions"));
llvm::cl::opt<bool>					UseRTTI("rtti",llvm::cl::desc("Enable RTTI support while parsing C++ input. Results in slow parsing"));


extern llvm::cl::opt<bool>			BeVerbose;
llvm::cl::opt<bool>					BeVerbose("v",llvm::cl::desc("Verbose mode"));

llvm::cl::list<std::string> InputFilenames(llvm::cl::Positional, llvm::cl::desc("<Input files>"), llvm::cl::OneOrMore);


//======================================================================================================

void	print_version_string()
{
	std::cout << "FreyaReflect version: " << (VERSION_STRING) << "\n"
		<< "LLVM(Clang) version: " << PACKAGE_VERSION;
}

//====================== Iterates through the directory and recursively collect every header file ======

void	header_files_collector(std::vector<std::string>& path_list, const llvm::sys::Path& current_dir)
{
	if(current_dir.getLast() == ".svn")//We do not want to parse .svn directories
		return;
	std::set<llvm::sys::Path> paths;
	std::string err;
	if(!current_dir.getDirectoryContents(paths,&err))
	{
		for(auto it = paths.begin(), end = paths.end(); it != end; ++it)
		{
			if(it->isDirectory())
				header_files_collector(path_list, *it);
			else
			{
				static llvm::Regex regex("(\\.(hpp|h|hxx|ipp))$",llvm::Regex::IgnoreCase);
				if(regex.match(it->str()))
				{
					path_list.push_back(it->str());
				}
			}
		}//for(auto it = paths.begin(), end = paths.end(); it != end; ++it)
	} //if(current_dir.getDirectoryContents(paths,NULL))
}

//======================================================================================================

int main (int argc, char* argv[])
{
	//Parse cl options
	llvm::cl::SetVersionPrinter(print_version_string);
	llvm::cl::ParseCommandLineOptions(argc,argv);
	//Gather input files.
	std::vector<std::string> file_list;
	//Check, if need to iterate recursively
	if(RecursiveScan.getValue())
	{
		if(InputFilenames.size() == 1)
		{
			llvm::sys::Path path(InputFilenames.front());
			if(path.isDirectory())
				header_files_collector(file_list, path);
			else
			{
				std::cerr << "-R implies, that the input is a directory" << std::endl;
				return 1;
			}
		}
		else
		{	
			std::cerr << "-R implies, that there is only one directory" << std::endl;
			return 1;
		}
	}//if(RecursiveScan.getValue())
	else
	{
		for(auto it = InputFilenames.begin(), end = InputFilenames.end(); it != end; ++it)
			file_list.push_back(*it);
	} //Just populate the list

	//Now, start tree populating.
	CppTreePtr	ast_tree = prepareASTTree(file_list,IncludeDirs,Definitions,UnDefinitions);
	//system("pause");
	return 0;
}