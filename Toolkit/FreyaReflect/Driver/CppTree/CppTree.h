/* File         : FreyaReflectBinary: CppTree.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef CppTree_h__
#define CppTree_h__

#include <string>
#include <map>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "CppTree/CppType.h"

class CppNode;
typedef boost::shared_ptr<CppNode> CppNodePtr;
class CppTree;

namespace clang
{
	class QualType;
}

class CppTree
{
protected:
	CppNode*		m_RootNode;
	typedef			boost::unordered_map<std::string,  CppTypePtr> type_map_t;	
	type_map_t		m_TypeMap;

public:
	CppTree();
	~CppTree();

	CppNodePtr		findNodeBySignature(const std::string& node) const;
	CppTypePtr		getTypeBySignature(const std::string& type)  { return m_TypeMap[type]; }
	void			addType(CppTypePtr type) 
	{
		type_map_t::iterator it = m_TypeMap.find(type->getQualifiedName());
		if(it == m_TypeMap.end() || !it->second)
			m_TypeMap[type->getQualifiedName()] = type; 
	}

	CppNode*		getRootNode() { return m_RootNode; }
};

typedef boost::shared_ptr<CppTree> CppTreePtr;

#endif // CppTree_h__