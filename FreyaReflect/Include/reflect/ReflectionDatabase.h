/* File		: FreyaReflect: ReflectionDatabase.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_ReflectionDatabase_h__
#define Reflect_ReflectionDatabase_h__

#include "FreyaReflectInternal.h"

#include "containers/policies/Policies.h"
#include "containers/hash_map.h"

#include "Scope.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT ReflectionDatabase
	{
		ReflectionDatabase();
		~ReflectionDatabase();
	public:
		static ReflectionDatabase&		GetInstance() { static ReflectionDatabase __db; return __db; }

		scope_ptr_t      getScope(const core::string& name) const { return m_RootScope->getChild(name); }
	private:
		scope_ptr_t                     m_RootScope;
	}; // class ReflectionDatabase
} // namespace reflect

#endif // Reflect_ReflectionDatabase_h__