#ifndef CppTree_h__
#define CppTree_h__

#include <string>
#include <map>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>
#include "CppTree/CppType.h"

class CppNode;
class CppTree;

namespace clang
{
	class QualType;
}

class CppTree
{
protected:
	CppNode*		m_RootNode;
	typedef			std::map<std::string,  CppTypePtr> type_map_t;	
	type_map_t		m_TypeMap;

public:
	CppTree();
	~CppTree();

	CppNode*		findNodeBySignature(const std::string& node) const;
	CppTypePtr		getTypeBySignature(const std::string& type)  { return m_TypeMap[type]; }
	void			addType(CppTypePtr type) { m_TypeMap[type->getQualifiedName()] = type; }

	CppNode*		getRootNode() { return m_RootNode; }
};

typedef boost::shared_ptr<CppTree> CppTreePtr;

#endif // CppTree_h__