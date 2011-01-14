#include "version.h"
//LLVM includes
#include <llvm/Support/Path.h>
#include <llvm/Support/Regex.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Config/config.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <zlib.h>
#include <cstdio>

#include "CppTree/ASTParser.h"

#include <memory>

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
	if(llvm::sys::path::filename(current_dir.str()) == ".svn")//We do not want to parse .svn directories
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
//================== Write temporary headers ===========================================================
llvm::sys::Path	write_down_temp_rutime()
{
	extern const size_t num_files;
	extern const size_t uncompressed_size;
	extern const size_t compressed_size;

	extern unsigned char	compressed_headers[];

	std::auto_ptr<unsigned char>	__managed_out_buffer (new unsigned char [uncompressed_size]);
	unsigned char* buffer = __managed_out_buffer.get();
//*
	int ret;
	z_stream strm;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = inflateInit(&strm); //Very aggressive compression
	if (ret != Z_OK)
	{
		//delete buffer;
		throw std::exception("zlib inflateInit failed");
	}

	strm.avail_in = compressed_size;
	strm.avail_out = uncompressed_size;

	strm.next_in = compressed_headers;
	strm.next_out = buffer;

	ret = inflate(&strm,Z_FINISH);

	if(ret != Z_STREAM_END)
	{
		//delete buffer;
		throw std::exception("Failed to decompress headers");
	}

	inflateEnd(&strm);
	//*/
	llvm::sys::Path	temp_path = llvm::sys::Path::GetTemporaryDirectory();
	llvm::sys::Path path (temp_path.str() + "/include");
	path.createDirectoryOnDisk(true);

	size_t offset = 0;
	for(size_t i = 0; i < num_files; ++i)
	{
		size_t filename_size = *reinterpret_cast<size_t*>(buffer + offset);
		offset += sizeof(size_t);
		size_t file_size =  *reinterpret_cast<size_t*>(buffer + offset);
		offset += sizeof(size_t);
		std::string filename (reinterpret_cast<char*>(buffer + offset), filename_size);
		offset += filename_size;

		llvm::sys::Path tmp(filename);
		tmp.eraseComponent();

		if(!tmp.empty() && (tmp.str() != filename))
		{
			llvm::sys::Path dir_path (path.str() + "/" + tmp.str());
			//std::clog << "Checking " << dir_path.str() << " for temporary runtime storage" << std::endl;
			if(!dir_path.exists())
			{
				dir_path.createDirectoryOnDisk(true);

				if(BeVerbose)
					std::clog << "Creating " << dir_path.str() << " for temporary runtime storage" << std::endl;
			}
		}

		//Now, write da file down
		
		FILE* output_file = fopen((path.str() + "/" + filename).c_str(), "wb");
		if(!output_file)
			throw std::exception("Failed to create a file");
		fwrite(buffer + offset,1,file_size,output_file);
		fclose(output_file);

		offset+= file_size;
	}
	
	return temp_path;
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
	//Write down headers
	try
	{
		llvm::sys::Path path = write_down_temp_rutime();
		//Now, start tree populating.
		CppTreePtr	ast_tree = prepareASTTree(path.str(),file_list,IncludeDirs,Definitions,UnDefinitions);

		path.eraseFromDisk(true);

		//Run generators here
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	//system("pause");
	return 0;
}