#include "CppType.h"
#include <cassert>

#include <boost/cstdint.hpp>

CppTypeFactory* CppTypeFactory::m_Instance = NULL;

cpp_type::cpp_type()
{

}

cpp_type::~cpp_type()
{

}

CppTypeFactory* CppTypeFactory::getInstance()
{
	assert(m_Instance);
	return m_Instance;
}
 
cpp_type_t* CppTypeFactory::getType( cpp_type_header_t header, const std::string& qualified_name )
{
	type_map_iterator_t	it = m_TypeMap.find(qualified_name);
	if(it != m_TypeMap.end()) //Type with the same name exists
	{
		//Search for exact match
		full_type_iterator_t	fm_it = it->second.find(header);
		if(fm_it != it->second.end())
			return fm_it->second;
	}
	//So, we are here, thus, we need to create a type
	cpp_type_t*		new_type = new cpp_type;
	new_type->header = header;
	new_type->type_name = qualified_name;
	new_type->parent_node = NULL;
	//Add type
	m_TypeMap[qualified_name][header] = new_type;
	return new_type;
}

CppTypeFactory::~CppTypeFactory()
{
	type_map_iterator_t it = m_TypeMap.begin(), end = m_TypeMap.end();
}

void CppTypeFactory::regenerateTypes( CppNode* root )
{

}


bool operator<( const cpp_type_header_t& _1,const cpp_type_header_t& _2 )
{
	using namespace boost;
	return reinterpret_cast<const int32_t&>(_1) < reinterpret_cast<const int32_t&>(_2);
}

bool operator==( const cpp_type_header_t& _1,const cpp_type_header_t& _2 )
{
	using namespace boost;
	return reinterpret_cast<const int32_t&>(_1) == reinterpret_cast<const int32_t&>(_2);
}
