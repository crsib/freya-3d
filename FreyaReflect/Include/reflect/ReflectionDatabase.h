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
#include "containers/vector.h"
#include "reflect/Scope.h"

#include "reflect/ReflectionConsumer.h"
#include "reflect/ReflectionModule.h"

namespace reflect
{
	class Class;

	class FREYA_REFLECT_EXPORT ReflectionDatabase : public ReflectionConsumer
	{
		ReflectionDatabase();
		~ReflectionDatabase();
	public:
		REFLECTION_CONSUMER();

		typedef containers::vector<reflection_module_ptr_t,containers::policies::memory::FreyaAllocator, containers::policies::multithreading::AtomicLock> reflection_modules_t;
		typedef reflection_modules_t::iterator reflection_module_iterator_t;

		static ReflectionDatabase&		GetInstance() { static ReflectionDatabase __db; return __db; }

		scope_ptr_t      getScope(const core::string& name) const { return m_RootScope->getChild(name); }
		Class*           getClass(const core::string& name) const;

		scope_ptr_t      getRootScope() const { return m_RootScope; }

		size_t           getModulesCount() const { return m_ReflectionModules.size(); }
		reflection_module_iterator_t modulesBegin()  { return m_ReflectionModules.begin(); }
		reflection_module_iterator_t modulesEnd()  { return m_ReflectionModules.end();}

		void			reflectAll(ReflectionConsumer* consumer);

		reflection_module_ptr_t getLastLoadedModule() const { return m_ReflectionModules.back(); }

		void            addModule(reflection_module_ptr_t module) { m_ReflectionModules.push_back(module); }
	private:
		scope_ptr_t                     m_RootScope;
		reflection_modules_t			m_ReflectionModules;

	}; // class ReflectionDatabase
} // namespace reflect

#endif // Reflect_ReflectionDatabase_h__