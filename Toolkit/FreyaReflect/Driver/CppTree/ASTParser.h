#ifndef ASTParser_h__
#define ASTParser_h__

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "CppTree/CppTree.h"
#include "CppTree/CppNode.h"
#include "CppTree/CppType.h"

CppTreePtr	prepareASTTree
	(
		const std::vector<std::string>& header_paths, 
		const std::vector<std::string>& search_paths,
		const std::vector<std::string>& defs,
		const std::vector<std::string>& undefs
	);

#endif // ASTParser_h__