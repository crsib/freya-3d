/* File         : FreyaReflectBinary: driver.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */


#ifdef _MSC_VER
#pragma warning( disable : 4005 )
#endif

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

#include "Output/XMLWriter.h"
#include "Input/XMLReader.h"

#include <memory>


class driver_exception : public std::exception
{
	const char * m_ExceptionMsg; 
public:
	driver_exception(const char* exception) throw() : m_ExceptionMsg ( m_ExceptionMsg ) {}
  	virtual const char* what() const throw() { return m_ExceptionMsg; }

};

//================================= cl options =========================================================
//Output flags
llvm::cl::opt<std::string>	ReflectionOutputFile("refl-output",llvm::cl::desc("Specify output filename for reflection file. Use stdout to redirect output to standard output"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>	LuaOutputFile("lua-output",llvm::cl::desc("Specify output filename for Lua bindings file.  Use stdout to redirect output to standard output"), llvm::cl::value_desc("filename"));
llvm::cl::opt<std::string>  XMLOutputFile("xml-output",llvm::cl::desc("Specify output filename for XML deserialization of AST.  Use stdout to redirect output to standard output"),llvm::cl::value_desc("filename"));
//Input flags
llvm::cl::list<std::string>	RecursiveScan("R", llvm::cl::desc("Scan the directory recursively for header files. Supported extensions are (*.h;*.hpp;*.ipp;*.hxx)"),llvm::cl::value_desc("directory"),llvm::cl::Prefix);
llvm::cl::list<std::string> XMLInput("X",llvm::cl::desc("XML files containing data about already reflected nodes"),llvm::cl::value_desc("XML File"), llvm::cl::Prefix);        

llvm::cl::list<std::string> IncludeDirs("I",llvm::cl::desc("Global include directory"),llvm::cl::value_desc("directory"),llvm::cl::Prefix);
llvm::cl::list<std::string> Definitions("D",llvm::cl::desc("Defines a preprocessor definition. Uses default GCC syntax"),llvm::cl::value_desc("definition"),llvm::cl::Prefix);
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

llvm::cl::list<std::string> InputFilenames(llvm::cl::Positional, llvm::cl::desc("<Input files>"), llvm::cl::ZeroOrMore);


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
		for(std::set<llvm::sys::Path>::iterator it = paths.begin(), end = paths.end(); it != end; ++it)
		{
			if( it->isDirectory() )
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
llvm::sys::Path	write_down_temp_runtime()
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
		throw driver_exception("zlib inflateInit failed");
	}

	strm.avail_in = compressed_size;
	strm.avail_out = uncompressed_size;

	strm.next_in = compressed_headers;
	strm.next_out = buffer;

	ret = inflate(&strm,Z_FINISH);

	if(ret != Z_STREAM_END)
	{
		//delete buffer;
		throw driver_exception("Failed to decompress headers");
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
			throw driver_exception("Failed to create a file");
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
	if(RecursiveScan.size())
	{
		for(std::vector<std::string>::iterator it = RecursiveScan.begin(), end = RecursiveScan.end(); it != end; ++it)
		{
			llvm::sys::Path path(*it);
			if(path.isDirectory())
				header_files_collector(file_list, path);
			else
			{
				std::cerr << "-R implies, that the input is a directory" << std::endl;
				return 1;
			}
		}
	}//if(RecursiveScan.getValue())
	
	for(std::vector<std::string>::iterator it = InputFilenames.begin(), end = InputFilenames.end(); it != end; ++it)
		file_list.push_back(*it);

	if(file_list.empty())
	{
		std::cerr << "No input specified. Please, use `freyareflect -help` to get help on using freyareflect" << std::endl;
		return -1;
	}
	//Write down headers
	try
	{
		llvm::sys::Path path = write_down_temp_runtime();
		//Now, start tree populating.
		CppTreePtr	ast_tree = prepareASTTree(path.str(),file_list,IncludeDirs,Definitions,UnDefinitions);

		path.eraseFromDisk(true);

		// Load input
		for(std::vector<std::string>::iterator it = XMLInput.begin(), end = XMLInput.end(); it != end; ++it)
			XMLReader(*it, ast_tree.get());

		//Run generators here
		if(XMLOutputFile.getValue() != "")
		{
			XMLWriter xml_writer(ast_tree->getRootNode(), XMLOutputFile.getValue());
			ast_tree->getRootNode()->acceptVisitor(xml_writer);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		abort();
		return 1;
	}
	
	//system("pause");
	return 0;
}
