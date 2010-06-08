#ifndef __FREYA_REFLECT_H_
#define __FREYA_REFLECT_H_

#include "internal.h"

#include <string>
#include <vector>

#include "CppNode.h"
#include "NamespaceNode.h"
#include <CppType.h>

#include <boost/wave.hpp>

#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class
#include "ContextPolicy.hpp"

typedef boost::wave::cpplexer::lex_token<> lexed_token_type;
typedef boost::wave::cpplexer::lex_iterator<lexed_token_type> lex_iterator_type;
typedef boost::wave::context<std::string::iterator, lex_iterator_type,
	boost::wave::iteration_context_policies::load_file_to_string,custom_directives_hooks> lexer_context_type;
typedef boost::spirit::classic::tree_parse_info<lexer_context_type::iterator_type> 
	ast_result_type;
typedef boost::spirit::classic::tree_match<lexer_context_type::iterator_type> ast_tree_match;
typedef ast_tree_match::const_tree_iterator			ast_const_tree_iterator;
typedef ast_tree_match::tree_iterator				ast_tree_iterator;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	FreyaReflect
///
/// \brief	Entry point class of reflection library. All other interfaces should be acquired from this class 
///	This class provides functionality to parse given C++ headers and extract reflection data from them.
/// \author	Crsib
/// \date	5/14/2010
////////////////////////////////////////////////////////////////////////////////////////////////////

class EXPORT FreyaReflect
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	FreyaReflect()
	///
	/// \brief	Default constructor. 
	///	This constructor creates an empty reflection data collector class.
	/// \author	Crsib
	/// \date	5/14/2010
	////////////////////////////////////////////////////////////////////////////////////////////////////

	FreyaReflect();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	~FreyaReflect()
	///
	/// \brief	Finaliser. 
	///
	/// \author	Crsib
	/// \date	5/15/2010
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~FreyaReflect();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addFile(const std::string& file_path)
	///
	/// \brief	Adds a file. 
	///
	/// \author	Crsib
	/// \date	5/15/2010
	///
	/// \param	file_path	Full pathname of the file. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void		addFile(const std::string& file_path);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addDirectory(const std::string& dir_path, bool recursive = true)
	///
	/// \brief	Adds a directory to 'recursive'. 
	///
	/// \author	Crsib
	/// \date	5/15/2010
	///
	/// \param	dir_path	Pathname of the directory. 
	/// \param	recursive	true to process recursively, false to process locally only. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void		addDirectory(const std::string& dir_path, bool recursive = true);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addIncludeDirectory(const std::string& include_dir)
	///
	/// \brief	Adds an include directory. 
	///
	/// \author	Crsib
	/// \date	5/15/2010
	///
	/// \param	include_dir	The include dir. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void		addIncludeDirectory(const std::string& include_dir);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addDefinition(const std::string& define)
	///
	/// \brief	Adds a definition. 
	/// Syntax of definition is similar to one used by wave library.
	/// \author	Crsib
	/// \date	5/15/2010
	///
	/// \param	define	The define. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void		addDefinition(const std::string& define);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool parse()
	///
	/// \brief	Parses all added files object. Generates kind of AST, which can be latter used to collect reflection data 
	///
	/// \return	true if it succeeds, false if it fails. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool		parse();

	CppNode*	root()
	{
		return m_RootNode;
	}
	const CppNode* 
				root() const
	{
		return m_RootNode;
	}
private:
	NamespaceNode*		m_RootNode;

	typedef		std::vector<std::string> IncludePaths;
	typedef		std::vector<std::string> Definitions;
	IncludePaths	m_IncludeList;
	IncludePaths	m_IncludeDirectoryList;
	Definitions		m_Definitions;
};

#endif