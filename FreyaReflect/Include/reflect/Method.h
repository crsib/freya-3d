/* File		: FreyaReflect: Method.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Method_h__
#define Reflect_Method_h__

#include "FreyaReflectInternal.h"

#include "core/RefCountedBase.h"
#include "core/Object.h"

#include "core/smart_ptr.h"

#include "core/string.h"

#include "reflect/Value.h"

namespace reflect
{
	typedef void*	method_this_ptr_t;
	//! This class represents a meta method
	/*!
	 * This class is a representation of meta method, used by reflection system.
	 * It provides ability to invoke the described method along with retrieving the methods signature.
	 * Method signature obeys the following rules:
	 *  - return value is omitted as C++ does not support overloading of functions by the return value
	 *  - if method accespts no parameters, than () is used as methods parameter list
	 *  - there is no space character between the opening brace and the first parameter
	 *  - there is no space character between the closing brace and the last method parameter
	 *  - there is no space character between the comma and former method parameter
	 *  - there is a single space character between the comma and the latter method parameter
	 *  - if object has a const qualifier, it is specified after the closing brace preceded by a single space character
	 *  - there are no leading or trailing spaces
	 *  - all the parameters are unnamed
	 *  - const qualifiers are separated by a single space character
	 *  - pointer and reference declarations are not separated from the type by a space character
	 *  - const qualifiers do precede the parameter type
	 *
	 * For example, "foo(const int&, float) const" is a valid method signature.
	 * Such restrictions are required to improve method lookup performance.
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT Method : public core::Object, public core::RefCountedBase
	{
	public:
		//! Creates a method
		Method(const core::string& signature, bool static_member, bool virtual_member) 
			: m_Signature(signature), m_IsStatic(static_member), m_IsVirtual(virtual_member) 
		{ FREYA_REFLECT_ASSERT(!(static_member && virtual_member), "Method could not be both static and virtual"); }
		//! Destructor
		virtual ~Method() {}
		//! Retrieves the method's signature
		const core::string& getMethodSignature() const { return m_Signature; }
		//! Checks, if the method is static
		bool  isStatic() const { return m_IsStatic; }
		//! Checks, if the method is virtual
		bool  isVirtual() const { return m_IsVirtual; }
		//! Calls the method.
		/*!
		 * Invokes the method using \a ptr as this pointer. If the method is static,
		 * \a ptr value is ignored. No runtime checks are done on the input parameter list,
		 * so there is no type safety guaranteed by this method.
		 * \return actual methods return value incapsulated in reflect::Value
		 */
		virtual Value call(method_this_ptr_t ptr = NULL, ...) const = 0;

	private:
		core::string m_Signature;

		bool	m_IsStatic;
		bool	m_IsVirtual;
		//Leave Method as non-copyable
		Method(const Method&);
		Method& operator = (const Method&);
	};

	typedef core::smart_ptr<Method, core::policies::ownership::Intrusive> method_ptr_t;
} // namespace reflect

#endif // Reflect_Method_h__