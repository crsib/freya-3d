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

#include <stdlib.h>       // exit, getenv, abort
#include "parssppt.h"     // ParseTreeAndTokens, treeMain

// TODO remove some of these headers
#include "srcloc.h"       // SourceLocManager
#include "ckheap.h"       // malloc_stats
#include "cc_env.h"       // Env
#include "cc_ast.h"       // C++ AST (r)
#include "cc_ast_aux.h"   // class LoweredASTVisitor
#include "cc_lang.h"      // CCLang
#include "parsetables.h"  // ParseTables
#include "cc_print.h"     // PrintEnv
#include "cc.gr.gen.h"    // CCParse
#include "nonport.h"      // getMilliseconds
#include "ptreenode.h"    // PTreeNode
#include "ptreeact.h"     // ParseTreeLexer, ParseTreeActions
#include "sprint.h"       // structurePrint
#include "strtokp.h"      // StrtokParse
#include "smregexp.h"     // regexpMatch
#include "cc_elaborate.h" // ElabVisitor
#include "integrity.h"    // IntegrityVisitor
#include "xml_file_writer.h" // XmlFileWriter
#include "xml_reader.h"   // xmlDanglingPointersAllowed
#include "xml_do_read.h"  // xmlDoRead()
#include "xml_type_writer.h" // XmlTypeWriter

namespace 
{
	static void handle_xBase(Env &env, xBase &x)
	{
		using std::cout;
		using std::clog;
		using std::endl;

		env.errors.print(cout);
		cout << x << endl;
		cout << "Failure probably related to code near " << env.locStr() << endl;
		cout << "current location stack:\n";
		cout << env.locationStackString();

		throw std::exception("Critical failure");
	}

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
	addDefinition("__FREYA_REFLECT");
	addDefinition("_STLP_CLASS_PARTIAL_SPECIALIZATION=1");
#ifdef _MSC_VER
	addDefinition("_MSC_VER=1600");
	addDefinition("_WIN32");
	addDefinition("__WIN32");
	addDefinition("WIN32");
	addDefinition("_WCHAR_T_DEFINED");
	//addDefinition("__cplusplus=199711L");
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
	boost::filesystem::path		 temp_name("./TempOutput.ipp");
	try
	{
		clock_t    full_parse_start = clock();
		//For each file needed
		std::string						instring = "#define _STLP_NATIVE_CPP_C_HEADER(header) <header>\n\n";
#ifdef _MSC_VER
		//Elsa does not support MSVC types. define them as typedef
		instring += 
			"#define __int32 int\n"
			"#define __int8  char\n"
			"#define __int16 short\n"
			"#define __int64 long long\n"
			"#define throw(X) \n\n";

		//No __declspec specifier
		instring += "#define __declspec(x)\n";
		instring += "#define __cdecl\n";
		instring += "#define __fastacall\n";
		instring += "#define __stdcall\n";
		instring += "#define __thiscall\n";
		instring += "#define __pragma(X)\n";
		instring += "#define __forceinline\n";

#endif	
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
		ctx.set_language( (boost::wave::language_support)(boost::wave::support_option_emit_line_directives | boost::wave::support_option_variadics | boost::wave::support_option_long_long ) );

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
		
		boost::filesystem::ofstream  output_stream(temp_name, std::ios::out);
		if(output_stream.bad())
			throw std::exception("Failed to create temp file");
		std::clog << "Preprocessing..." << std::endl;
		//Get the distance between first and last
		size_t dist = std::distance(first,last);
		size_t pc = 1;
		size_t processed = 0; 
		for( ; first != last; ++first, processed++)
		{
			//Fix 1. separate < and :: with ws
			if(first->get_value() == "<")
			{
				output_stream << "< ";
				//This cannot be the last token of a stream
				first++;
				processed++;
			}//Fix 1.
			
			//Fix 2. clean i64 token
			{
				boost::wave::token_id tid = (*first);
				if(tid == boost::wave::T_HEXAINT || tid == boost::wave::T_OCTALINT || tid == boost::wave::T_DECIMALINT || tid == boost::wave::T_LONGINTLIT || tid == boost::wave::T_INTLIT || tid == boost::wave::T_UNKNOWN)
				{
					lexer_context_type::token_type::string_type val = first->get_value();
					size_t pos = val.find("i64");
					if(pos != std::string::npos)
						output_stream << val.substr(0, pos);
					else
						output_stream << val;
					//This cannot be the last token of a stream
					first++;
					processed++;
					if(first->get_value() == "i64")
					{
						first++;
						processed++;
					}
				}
				
			}//Fix2
			//extern "C++" from MS std headers
			{
				boost::wave::token_id tid = (*first);
				if(tid == boost::wave::T_EXTERN)
				{
					lexer_context_type::iterator_type it = first;
					it++;
					processed ++;
					bool clean_up = false;
					if(it->get_value() == "\"C++\"")
						clean_up = true;
					else
					{
						it++;
						processed ++;
						if(it->get_value() == "\"C++\"")
							clean_up = true;
					}

					if(clean_up)
					{
						//scan line until 2 new lines or {
						int num_newlines = 0;
						int brace_count = 0;
						while(num_newlines != 2)
						{
							if((*it) == boost::wave::T_NEWLINE)
								num_newlines++;
							else if((*it) == boost::wave::T_LEFTBRACE)
							{
								brace_count++;
								it++;
								processed++;
								break;
							}
							it++;
							processed++;
						}
						while(brace_count > 0)
						{
							if((*it) == boost::wave::T_LEFTBRACE)
								brace_count++;
							else if((*it) == boost::wave::T_RIGHTBRACE)
								brace_count--;
							it++;
							processed++;
						}
						first = it;
					}
				}//extern token
			}//Fix3

			output_stream << first->get_value();

			//size_t processed = dist - std::distance(first,last);
			if((100.0 * (float) (processed - 1) / dist) >= (float)pc)
			{
				std::clog << pc << "%..." ;
				std::clog.flush();
				pc++;
			}
		}//Write stream
		std::clog <<  std::endl;
		output_stream.close();
		std::clog << "Parsing..." << std::endl;
		TranslationUnit *unit = NULL;
		try
		{
			CCLang lang;
			lang.GNU_Cplusplus();
			lang.MSVC_bug_compatibility();
			lang.allowModifiersWithTypedefNames = B3_TRUE;
			lang.allowExplicitSpecWithoutParams = B3_TRUE;
			lang.allowQualifiedMemberDeclarations = B3_TRUE;
			lang.allowOverloading = true;
			lang.compoundSelfName = true;
			lang.tagsAreTypes = true;
			
		//	Env
			SourceLocManager mgr;
			StringTable strTable;
			BasicTypeFactory tfac;

			SemanticValue treeTop;
			ParseTreeAndTokens tree(lang, treeTop, strTable, temp_name.string().c_str());

			traceAddSys("permissive");
			//traceAddSys("parse");
			// grab the lexer so we can check it for errors (damn this
			// 'tree' thing is stupid..)
			Lexer *lexer = dynamic_cast<Lexer*>(tree.lexer);
			xassert(lexer);

			CCParse *parseContext = new CCParse(strTable, lang);
			tree.userAct = parseContext;

			std::clog << "Building parse tables from internal data..." << std::endl;
			ParseTables *tables = parseContext->makeTables();
			tree.tables = tables;

			maybeUseTrivialActions(tree);

			if (!toplevelParse(tree, temp_name.string().c_str())) 
			{
				throw std::exception("Parsing error occured");
			}

			// check for parse errors detected by the context class
			if (parseContext->errors || lexer->errors)
			{
				throw std::exception("Parsing error occured");
			}
			int parseWarnings = lexer->warnings + parseContext->warnings;

			// treeTop is a TranslationUnit pointer
			unit = (TranslationUnit*) treeTop;

			delete parseContext;
			delete tables;

			ArrayStack<Variable*> madeUpVariables;
			ArrayStack<Variable*> builtinVars;
			
			std::clog << "Starting type check process..." << std::endl;
			Env env(strTable, lang, tfac, madeUpVariables, builtinVars, unit);
			//env.secondPassTcheck = true;
			env.doFunctionTemplateBodyInstantiation = false;
			env.delayFunctionInstantiation = true;
			env.doCompareArgsToParams = true;
			env.doReportTemplateErrors = false;
			try 
			{
				env.tcheckTranslationUnit(unit);
			}
			catch (XUnimp &x) 
			{
				HANDLER();
				(void) x;
				std::clog << "in code near " << env.locStr() << ":\n";
				throw;
			}
			catch (x_assert &x)
			{
				HANDLER();

				if (env.errors.hasFromNonDisambErrors()) {
					if (tracingSys("expect_confused_bail")) {
						std::clog << "got the expected confused/bail\n";
						exit(0);
					}
					// see comment about 'confused' in elsa main.cc
					env.error("confused by earlier errors, bailing out");
					env.errors.print(std::clog);
					throw std::exception("Type checking failed"); 
				}
				// if we don't have a basis for reducing severity, pass this on
				// to the normal handler
				handle_xBase(env, x);
			}
			catch (xBase &x) 
			{
				HANDLER();
				handle_xBase(env, x);
			}

			int numErrors = env.errors.numErrors();
			int numWarnings = env.errors.numWarnings() + parseWarnings;

			//if (numErrors != 0 || numWarnings != 0) 
			{
				// print errors and warnings
				env.errors.print(std::cout);

				std::cout << "Type checking results:\n"
					<< "  errors:   " << numErrors << "\n"
					<< "  warnings: " << numWarnings << "\n";
			}

			if (numErrors != 0) 
			{
				//throw std::exception("Type check failed");
			}
			//Elaborate
			std::clog << "Elaborating..." << std::endl;
			ElabVisitor vis(strTable, tfac, unit);
			unit->traverse(vis.loweredVisitor);
			
			//Start AST porcessing
			//unit->gdb();
			std::clog << "Regenerating AST..." << std::endl;

		}
		catch (XUnimp &x) {
			HANDLER();
			std::cout << x << std::endl;
			return false;
		}
		catch (XFatal &x) {
			HANDLER();
			std::cout << x << std::endl;
			return false;
		}
		catch (xBase &x) {
			HANDLER();
			std::cout << x << std::endl;
			return false;
		}
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
	//Delete temp file
	boost::filesystem::remove(temp_name);
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
