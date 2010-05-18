#include "FreyaReflect.h"

#include <iostream>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <boost/wave.hpp>

#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>

FreyaReflect::FreyaReflect()
{
	//Create root node - the default namespace node
	m_RootNode = new NamespaceNode("",NULL);
}

FreyaReflect::~FreyaReflect()
{
	delete m_RootNode;
}

bool FreyaReflect::parse()
{
	boost::wave::util::file_position_type current_position;
	try
	{
		//For each file needed
		for(size_t i = 0; i < m_IncludeList.size(); ++i)
		{
			std::clog << "Parsing " << m_IncludeList[i] << "..." << std::endl;
			boost::filesystem::fstream		instream(m_IncludeList[i]);
			std::string						instring;
			if (!instream.is_open()) {
				std::cerr << "Could not open input file: " << m_IncludeList[i] << std::endl;
				return false;
			}

			instream.unsetf(std::ios::skipws);
			instring = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
				std::istreambuf_iterator<char>());

			typedef boost::wave::cpplexer::lex_token<> token_type;
			typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;
			typedef boost::wave::context<std::string::iterator, lex_iterator_type> context_type;

			context_type ctx (instring.begin(), instring.end(), m_IncludeList[i].c_str());
			
			for(size_t _i = 0; _i < m_Definitions.size(); ++_i)
			{
				ctx.add_macro_definition(m_Definitions[_i]);
			}

			//  Get the preprocessor iterators and use them to generate 
			//  the token sequence.
			context_type::iterator_type first = ctx.begin();
			context_type::iterator_type last = ctx.end();

			while (first != last)
			{
				current_position = (*first).get_position();
				std::cout << (*first).get_value();
				++first;
			}
		}//(size_t i = 0; i < m_IncludeList.size(); ++i)
	}//try
	catch (boost::wave::cpp_exception const& e) 
	{
		// some preprocessing error
		std::cerr 
			<< e.file_name() << "(" << e.line_no() << "): "
			<< e.description() << std::endl;
		return false;
	}
	catch (std::exception const& e) 
	{
		// use last recognized token to retrieve the error position
		std::cerr 
			<< current_position.get_file() 
			<< "(" << current_position.get_line() << "): "
			<< "exception caught: " << e.what()
			<< std::endl;
		return false;
	}
	catch (...)
	{
		// use last recognized token to retrieve the error position
		std::cerr 
			<< current_position.get_file() 
			<< "(" << current_position.get_line() << "): "
			<< "unexpected exception caught." << std::endl;
		return false;
	}
	return true;
}

void FreyaReflect::addDefinition( const std::string& define )
{
	m_Definitions.push_back(define);
}

void FreyaReflect::addIncludeDirectory( const std::string& include_dir )
{
	m_IncludeDirectoryList.push_back(include_dir);
}

namespace
{
	void add_dir_recursive( const boost::filesystem::path& path, FreyaReflect& reflector)
	{
		using namespace boost::filesystem;
		static directory_iterator end_iter;

		static boost::regex  ext("(\\.(cpp)|(cxx)|(hpp)|(h)|(hxx)|(c))$",boost::regex_constants::icase);

		for(directory_iterator it( path ); it != end_iter; ++it)
		{
			if(is_directory(it->status()) && it->leaf() != ".svn")
				add_dir_recursive(it->path(),reflector);
			else if(is_regular_file(it->status()) && boost::regex_search(it->path().filename(),ext))
				reflector.addFile(it->path().directory_string());
		}
	}
}

void FreyaReflect::addDirectory( const std::string& dir_path, bool recursive /*= true*/ )
{
	using namespace boost::filesystem;
	path dirPath(dir_path);
	if(!exists(dirPath))
		throw (std::string("Directory does not exists: " ) + dir_path);
	if(recursive)
	{
		add_dir_recursive(dirPath, *this);
	}
	else
	{
		//Add the directory
		directory_iterator end_iter;
		static boost::regex  ext("(\\.(cpp)|(cxx)|(hpp)|(h)|(hxx)|(c))$",boost::regex_constants::icase);
		for(directory_iterator it( dir_path ); it != end_iter; ++it)
		{
			if(is_regular_file(it->status()) && boost::regex_search(it->path().filename(),ext))
			{
				//if(it->path().extension())
				addFile(it->path().directory_string());
			}
		}
	}
}

void FreyaReflect::addFile( const std::string& file_path )
{
	using namespace boost::filesystem;
	path    filePath(file_path);
	if(exists(filePath)&&is_regular_file(filePath))
	{
		m_IncludeList.push_back(filePath.file_string());
		std::clog << "Adding file: " << m_IncludeList.back() << std::endl;
	}
	else
		throw (std::string("Failed to find file: ") + file_path);
}
