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

	class FREYA_REFLECT_EXPORT Method : public core::Object, public core::RefCountedBase
	{
	public:
		Method(const core::string& signature, bool static_member, bool virtual_member) 
			: m_Signature(signature), m_IsStatic(static_member), m_IsVirtual(virtual_member) 
		{ FREYA_REFLECT_ASSERT(!(static_member && virtual_member), "Method could not be both static and virtual"); }
		virtual ~Method() {}

		const core::string& getMethodSignature() const { return m_Signature; }
		bool  isStatic() const { return m_IsStatic; }
		bool  isVirtual() const { return m_IsVirtual; }

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