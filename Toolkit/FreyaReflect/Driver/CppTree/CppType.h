#ifndef CppType_h__
#define CppType_h__

#include <clang/ast/Type.h>
#include <string>

class CppTree;
class CppNode;

class CppType
{
public: 
	typedef union          cpp_type_header
	{
		struct
		{
			bool            is_constant                                     : 1;  // Bit 0

			bool            is_reference                                    : 1;  // Bit 1
			bool            is_pointer                                      : 1;  // Bit 2
			bool            is_constant_pointer                             : 1;  // Bit 3
			bool            is_constant_reference                           : 1;  // Bit 4

			bool            is_builtin	                                    : 1;  // Bit 5
			bool            is_template_specialization                      : 1;  // Bit 6
			bool            is_user_type                                    : 1;  // Bit 7
			bool            is_stl_type                                     : 1;  // Bit 8

			bool			is_volatile										: 1; // Bit 9
			bool			is_volatile_pointer								: 1; // Bit 10
			unsigned        __reserved__                                    : (32 - 11);
		};
		unsigned		mask;
	} cpp_type_header_t;
private:
	CppType() : m_ASTNode(NULL) { m_TypeHeader.mask = 0u; }
	virtual ~CppType() {}

	//Make it not copyable
	CppType(const CppType&);
	CppType& operator = (const CppType&);

	CppNode*						m_ASTNode;
	clang::BuiltinType::Kind		m_Kind;

	std::string						m_QualifiedName;

	cpp_type_header_t				m_TypeHeader;

public:

	bool isConstant() const { return m_TypeHeader.is_constant; }
	bool isVolatile() const { return m_TypeHeader.is_volatile; }
	bool isReference() const { return m_TypeHeader.is_reference; }
	bool isConstantReference() const { return m_TypeHeader.is_constant_reference; }
	bool isPointer() const { return m_TypeHeader.is_pointer; }
	bool isConstantPointer() const { return m_TypeHeader.is_constant_pointer; }
	bool isVolatilePointer() const { return m_TypeHeader.is_volatile_pointer; }
	bool isBuiltin() const { return m_TypeHeader.is_builtin; }

	cpp_type_header_t   getTypeHeader() const { return m_TypeHeader; }

	const CppNode*		getUserType() const { return m_ASTNode; }

	std::string			getQualifiedName() const { return m_QualifiedName; }
};

#endif // CppType_h__