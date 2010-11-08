#ifndef CppTree_h__
#define CppTree_h__

#include <string>
#include <map>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>

class CppNode;
class CppTree;
class CppType;

namespace __internal
{
	void create_builtins(CppTree* for_tree);
}

class CppTree
{
	friend void create_builtins(CppTree* for_tree);

	CppNode*		m_RootNode;

	typedef			std::map<std::string, boost::shared_ptr<CppType> > type_map_t;
	type_map_t		m_TypeMap;

public:
	CppTree();
	~CppTree();
};

#endif // CppTree_h__