#ifndef CppType_h__
#define CppType_h__

#include <string>
#include "internal.h"
#include <map>

class CppNode;

class CppTypeFactory;

class FreyaReflect;

typedef struct		cpp_type_header
{
	bool		by_constant							: 1;

	bool		by_reference						: 1;
	bool		by_pointer							: 1;
	bool		by_constant_pointer					: 1;
	bool		by_constant_reference				: 1;

	bool		is_basic_type						: 1;
	bool		is_template_instantation			: 1;
	bool		is_user_type						: 1;
	bool		is_stl_type							: 1;

	unsigned	__reserved__						: (32 - 9);
} cpp_type_header_t;

bool	operator < (const cpp_type_header_t& _1,const cpp_type_header_t& _2);
bool	operator == (const cpp_type_header_t& _1,const cpp_type_header_t& _2);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct	cpp_type
///
/// \brief	This structure is holder for any type, .
///
/// \author	Crsib
/// \date	6/3/2010
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct  cpp_type
{
	cpp_type_header_t	header;
	//The following pointer is used, when is_user_type == true and contains pointer to node, holding the user declaration
	CppNode*	parent_node;

	//This string contains a fully qualified name of a type (this name will be used to resolve the type later if possible)
	std::string	type_name;

private:
	cpp_type();
	~cpp_type();
	cpp_type(const cpp_type&);
	cpp_type& operator = (const cpp_type&);
	friend class CppTypeFactory;
} cpp_type_t;

class EXPORT CppTypeFactory
{
private:
	static	CppTypeFactory*		m_Instance;
	CppTypeFactory(){m_Instance = this;}
	~CppTypeFactory();
	CppTypeFactory(const CppTypeFactory&);
	CppTypeFactory& operator = (const CppTypeFactory&);
public:
	static CppTypeFactory*				getInstance();

	cpp_type_t*					getType(cpp_type_header_t header, const std::string& qualified_name);

private:
	typedef		std::map<cpp_type_header_t,cpp_type_t*> full_type_t;
	typedef		full_type_t::iterator					full_type_iterator_t;
	typedef		full_type_t::const_iterator				full_type_const_iterator_t;
	
	typedef		std::map<std::string, full_type_t>		type_map_t;
	typedef		type_map_t::iterator					type_map_iterator_t;
	typedef		type_map_t::const_iterator				type_map_const_iterator_t;

	type_map_t	m_TypeMap;

	void		regenerateTypes(CppNode* root);

	friend      class FreyaReflect;
};

#endif // CppType_h__