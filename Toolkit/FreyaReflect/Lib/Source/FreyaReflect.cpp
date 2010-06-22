#include "FreyaReflect.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/wave.hpp>

#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class
#include "ContextPolicy.hpp"

typedef boost::wave::cpplexer::lex_token<> lexed_token_type;
typedef boost::wave::cpplexer::lex_iterator<lexed_token_type> lex_iterator_type;
typedef boost::wave::context<std::string::iterator, lex_iterator_type,
	boost::wave::iteration_context_policies::load_file_to_string,custom_directives_hooks> lexer_context_type;

#include <iostream>
#include <sstream>

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <boost/wave/cpplexer/cpplexer_exceptions.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>

#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_tree_to_xml.hpp>

#include <ctime>
#include <sstream>

namespace 
{
	std::string format_time(clock_t time)
	{
		std::ostringstream sstream;
		sstream.precision(3);
		sstream << std::fixed << static_cast<float>(time) / static_cast<float>(CLOCKS_PER_SEC) << " secs" ;
		sstream.flush();
		return sstream.str();
	}

	///////////////////////////////////////////////////////////////////////////
	//  helper routines needed to generate the parse tree XML dump
	typedef boost::wave::cpplexer::lex_token<> lexed_token_type;

	lexed_token_type::string_type  get_token_id(lexed_token_type const &t) 
	{ 
		using namespace boost::wave;
		return get_token_name(token_id(t)); // boost::wave::token_id(t); 
	}

	lexed_token_type::string_type get_token_value(lexed_token_type const &t) 
	{ 
		return t.get_value(); 
	}

}   // unnamed namespace 

FreyaReflect::FreyaReflect()
{
	//Create root node - the default namespace node
	m_RootNode = new NamespaceNode("",NULL);
	new CppTypeFactory;
	addDefinition("__i386");
#ifdef _MSC_VER
	addDefinition("_MSC_VER=1600");
	addDefinition("_WIN32");
	addDefinition("__WIN32");
	addDefinition("WIN32");
#else
	addDefinition("__GNUC__=");
#if defined (__APPLE__)
	addDefinition("__APPLE__");
#else
	addDefinition("__linux__");
#endif
#endif
#ifdef _STLP_DEBUG
	addDefinition("_STLP_DEBUG");
#endif
	addDefinition("_STLP_HAS_INCLUDE_NEXT");
}

FreyaReflect::~FreyaReflect()
{
	CppTypeFactory* node = CppTypeFactory::getInstance();
	delete node;
	delete m_RootNode;
}

bool FreyaReflect::parse()
{
	boost::wave::util::file_position_type current_position;
	try
	{
		clock_t    full_parse_start = clock();
		//For each file needed
		std::string						instring = "#define _STLP_NATIVE_CPP_C_HEADER(header) <header>\n\n";
		for(size_t i = 0; i < m_IncludeList.size(); ++i)
		{
			std::clog << "Injecting " << m_IncludeList[i] << "..." << std::endl;
#ifdef _WIN32
			//Fix path
			static boost::regex  rg("\\\\",boost::regex_constants::icase);
			instring = instring + "#include \"" + boost::regex_replace(std::string(m_IncludeList[i].c_str()),rg,std::string("/"),boost::match_default | boost::format_sed) + "\"\n";
#else
			instring = instring + "#include \"" + m_IncludeList[i].c_str() + "\"\n";
#endif
		
		}
		std::cout << instring << std::endl;
		lexer_context_type ctx (instring.begin(), instring.end(), "parse_buffer");
		ctx.set_language( (boost::wave::language_support)( boost::wave::support_option_variadics | boost::wave::support_option_long_long ) );

		for(size_t _i = 0; _i < m_Definitions.size(); ++_i)
		{
			ctx.add_macro_definition(m_Definitions[_i]);
		}

		for(size_t i = 0; i < m_IncludeDirectoryList.size(); ++i)
		{
			
			ctx.add_include_path(m_IncludeDirectoryList[i].c_str());
			ctx.add_sysinclude_path(m_IncludeDirectoryList[i].c_str());
		}
		//Ok, time for system includes ))
		{
#ifdef _MSC_VER
			char* env     = getenv("INCLUDE");
			if(env == NULL)
				env = "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/INCLUDE;C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/ATLMFC/INCLUDE;C:/Program Files (x86)/Microsoft SDKs"
				"/Windows/v7.0A/include;"
				"C:/Program Files/Microsoft Visual Studio 10.0/VC/INCLUDE;C:/Program Files/Microsoft Visual Studio 10.0/VC/ATLMFC/INCLUDE;C:/Program Files/Microsoft SDKs"
				"/Windows/v7.0A/include;";
			std::string   paths(env);
			std::string	  separator(";");
#else
			std::string	  path(getenv("CPATH"));
			path += getenv("C_INCLUDE_PATH");
			path += getenv("CPLUS_INCLUDE_PATH");
			std::string	   separator(PATH_SEPARATOR);
#endif
			std::vector< std::string > _paths;
			boost::algorithm::split(_paths, paths, boost::algorithm::is_any_of(separator));
			for(size_t i = 0; i < _paths.size(); ++i)
			{
				ctx.add_sysinclude_path(_paths[i].c_str());
				std::clog << "Adding system include path " << _paths[i] << std::endl;
			}
		}
		ctx.set_max_include_nesting_depth(256);
		//  Get the preprocessor iterators and use them to generate 
		//  the token sequence.
		lexer_context_type::iterator_type first = ctx.begin();
		lexer_context_type::iterator_type last = ctx.end();
		//Generate full source and feed it to ELSA
		std::ostringstream  output_stream;
		for( ; first != last; ++first)
			output_stream << first->get_value();

		//std::cout << output_stream.str() << std::endl;
		std::clog << "Parse completed in " << format_time(clock() - full_parse_start) << std::endl;
	}//try
	catch (boost::wave::cpp_exception const& e) 
	{
		// some preprocessing error
		std::cerr 
			<< e.file_name() << "(" << e.line_no() << "): "
			<< e.description() << std::endl;
		return false;
	}
	catch(boost::wave::cpplexer::lexing_exception const& e)
	{
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
		//std::clog << "Adding file: " << m_IncludeList.back() << std::endl;
	}
	else
		throw (std::string("Failed to find file: ") + file_path);
}
