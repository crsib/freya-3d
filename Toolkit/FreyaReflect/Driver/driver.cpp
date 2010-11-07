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

//================================= cl options =========================================================
llvm::cl::opt<std::string>	ReflectionOutputFile("refl-output",llvm::cl::desc("Specify output filename for reflection file. Output will be redirected to stdout, if not specified"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>	LuaOutputFile("lua-output",llvm::cl::desc("Specify output filename for Lua bindings file. Output will be suppressed, if not specified"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>  XMLOutputFile("xml-output",llvm::cl::desc("Specify output filename for XML de-serialization of AST part, used for reflection"),llvm::cl::value_desc("filename"));
llvm::cl::opt<bool>			RecursiveScan("R", llvm::cl::desc("Treat input as a directory and scan it recursively for header files. Supported extensions are (*.h;*.hpp;*.ipp;*.hxx)"));
llvm::cl::list<std::string> IncludeDirs("I",llvm::cl::desc("Global include directory"),llvm::cl::value_desc("directory"),llvm::cl::Prefix);
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

	for(size_t i = 0; i < file_list.size(); ++i)
		std::cout << file_list[i] << std::endl;

	//system("pause");
	return 0;
}