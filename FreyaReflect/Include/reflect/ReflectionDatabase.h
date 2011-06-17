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
#include "containers/hash_map.h"
#include "reflect/Scope.h"

#include "reflect/ReflectionConsumer.h"
#include "reflect/ReflectionModule.h"

#include "core/multithreading/spinlock.h"

#include "integer.h"

//! \defgroup grpFreyaReflect Freya 3D Engines reflection capabilities

//! \brief This namespace contains all the functionality related to Freya 3D Engines reflection capabilities
//! \ingroup gerFreyaReflect
namespace reflect
{
	class Class;
	//! Central class of the reflection system
	/*!
	 * ReflectionDatabase is a central class of the Freya3D reflection system. 
	 * It manages all reflection data along with providing a safe way to reflect the code
	 * to other relfect::ReflectionConsumer objects. 
     *
	 * ReflectionDatabase is a Meyers singleton, which in turn starts the memory manager and the logger, which guarantees,
	 * that both subsystems will be destroyed strictly after the ReflectionDatabase upon the application's termination stage.
	 * ReflectionDatabase is a reflect::ReflectionConsumer itself, and every reflect::ReflectionModule is auto-relflected into it
	 * when loaded. ReflectionDatabase manages the lifetime of reflect::Class objects.
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT ReflectionDatabase : public ReflectionConsumer
	{
		ReflectionDatabase();
		~ReflectionDatabase();

		typedef containers::vector<reflection_module_ptr_t,
			containers::policies::memory::FreyaAllocator,
			containers::policies::multithreading::AtomicLock> reflection_modules_t;
	public:
		REFLECTION_CONSUMER();
		//! Iterator to the reflection module
		typedef reflection_modules_t::iterator reflection_module_iterator_t;
		//! Retrieves the instance of the database
		static ReflectionDatabase&		GetInstance() { static ReflectionDatabase __db; return __db; }
		//! Retrieves a scope of name \a name
		scope_ptr_t      getScope(const core::string& name) const { return m_RootScope->getChild(name); }
		//! Retrieves a class named \a name
		Class*           getClass(const core::string& name) const;
		//! Retrieves the root scope
		scope_ptr_t      getRootScope() const { return m_RootScope; }
		//! Retrieves the number of loaded modules
		size_t           getModulesCount() const { return m_ReflectionModules.size(); }
		//! Retrieves the iterator to the first loaded module
		reflection_module_iterator_t modulesBegin()  { return m_ReflectionModules.begin(); }
		//! Retrieves the iterator to the "one-past-last" loaded module
		reflection_module_iterator_t modulesEnd()  { return m_ReflectionModules.end();}
		//! Reflects all loaded modules to the consumer
		void			reflectAll(ReflectionConsumer* consumer);
		//! Retrieves the last loaded module
		reflection_module_ptr_t getLastLoadedModule() const { return m_ReflectionModules.back(); }
		//! Add a new module to the reflection system, reflect it to the database and take ownership over it. This operation is thread safe
		void            addModule(reflection_module_ptr_t module);
	private:
		scope_ptr_t                     m_RootScope;
		reflection_modules_t			m_ReflectionModules;

		// Deferred name lookup
		typedef containers::hash_multimap
		<
			core::string, Class*,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator,
			containers::policies::multithreading::AtomicLock
		>  deferred_lookup_table_t;

		deferred_lookup_table_t	       m_DeferredLookupTable;

		core::multithreading::spinlock m_ModulesLock;

		friend class Class;
	}; // class ReflectionDatabase
} // namespace reflect

#endif // Reflect_ReflectionDatabase_h__