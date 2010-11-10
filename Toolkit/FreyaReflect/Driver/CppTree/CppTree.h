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

class CppTree
{
	CppNode*		m_RootNode;
	typedef			std::map<std::string, boost::shared_ptr<CppType> > type_map_t;
	type_map_t		m_TypeMap;

public:
	CppTree();
	~CppTree();

	CppNode*		findNode(const std::string& node) const;
};

#endif // CppTree_h__