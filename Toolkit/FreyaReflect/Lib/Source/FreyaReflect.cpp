#include "FreyaReflect.h"

#include <iostream>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <boost/wave/cpplexer/cpplexer_exceptions.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>

#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_tree_to_xml.hpp>

#include "translation_unit_parser.h"
#include "translation_unit_skipper.h"

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
		clock_t    full_parse_start = clock();
		//For each file needed
		for(size_t i = 0; i < m_IncludeList.size(); ++i)
		{
			std::clog << "Parsing " << m_IncludeList[i] << "..." << std::endl;
			clock_t file_parse_start = clock();
			boost::filesystem::fstream		instream(m_IncludeList[i]);
			std::string						instring;
			if (!instream.is_open()) {
				std::cerr << "Could not open input file: " << m_IncludeList[i] << std::endl;
				return false;
			}

			instream.unsetf(std::ios::skipws);
			instring = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
				std::istreambuf_iterator<char>());

			lexer_context_type ctx (instring.begin(), instring.end(), m_IncludeList[i].c_str());
			
			for(size_t _i = 0; _i < m_Definitions.size(); ++_i)
			{
				ctx.add_macro_definition(m_Definitions[_i]);
			}

			//  Get the preprocessor iterators and use them to generate 
			//  the token sequence.
			lexer_context_type::iterator_type first = ctx.begin();
			lexer_context_type::iterator_type last = ctx.end();
			
			translation_unit_grammar::rule_map_type rule_map;
			translation_unit_grammar g(&rule_map);
			translation_unit_skipper s; 

			ast_result_type pi = boost::spirit::classic::ast_parse(first, last, g, s);
			if(pi.full)
			{
				//Send parsed tree down the hierarchy
				void	parse_ast(NamespaceNode* __default_namespace, const ast_result_type& __ast,  translation_unit_grammar::rule_map_type& rule_map);
				parse_ast(m_RootNode,pi,rule_map);
				std::clog << "Successfully parsed in " << format_time(clock() - file_parse_start)<<std::endl; 
			}
			else 
			{
				std::cerr 
					<< "Hannibal: parsing failed: " << m_IncludeList[i] << std::endl;
				std::cerr 
					<< "Hannibal: last recognized token was: " 
					<< get_token_id(*pi.stop) << std::endl;

				using boost::wave::util::file_position_type;
				file_position_type const& pos(pi.stop->get_position());
				std::cerr 
					<< "Hannibal: at: " << pos.get_file() << "(" << pos.get_line() 
					<< "," << pos.get_column() << ")" << std::endl;
				return false;
			}

		}//(size_t i = 0; i < m_IncludeList.size(); ++i)
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
		std::clog << "Adding file: " << m_IncludeList.back() << std::endl;
	}
	else
		throw (std::string("Failed to find file: ") + file_path);
}
