/* File		: FreyaReflect: ReflectionDatabase.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/ReflectionDatabase.h"
#include "core/Log.h"
#include "reflect/Class.h"
#include "core/multithreading/synchronize.h"

namespace reflect
{
	namespace
	{
		class ReflectorStarter
		{
			ReflectionDatabase* m_Db;
		public:
			ReflectorStarter() : m_Db(&ReflectionDatabase::GetInstance()) { m_Db->getRootScope(); }
		};
		
		static ReflectorStarter __reflection_starter;

		class RootScope : public Scope
		{
		public:
			RootScope() : Scope(NamespaceScope,"",NULL) {}
		};
	}

	ReflectionDatabase::ReflectionDatabase() : ReflectionConsumer("FreyaReflect"), m_DeferredLookupTable(2.0f)
	{
		InfoLog() << "Starting reflection engine"; // This will actually force that the memory arena is created first, log system - second and the reflector - third
		//Create root scope
		m_RootScope = scope_ptr_t(new RootScope);
	}

	ReflectionDatabase::~ReflectionDatabase()
	{
		InfoLog() << "Stopping reflection engine";
	}

	void ReflectionDatabase::reflectAll( ReflectionConsumer* consumer )
	{
		for(reflection_module_iterator_t it = m_ReflectionModules.begin(), end = m_ReflectionModules.end(); it != end; ++it)
			(*it)->reflectTo(consumer);
	}

	Class* ReflectionDatabase::getClass( const core::string& name ) const
	{
		scope_ptr_t scope = getScope(name);
		if(scope && (scope->getScopeType() == Scope::ClassScope))
			return static_cast<Class*>(scope.get());
		return NULL;
	}

	void ReflectionDatabase::addModule( reflection_module_ptr_t module )
	{
		synchronize(&m_ModulesLock)
		{
			m_ReflectionModules.push_back(module);
			module->reflectTo(this);
			if(m_DeferredLookupTable.size())
			{
				DebugLog("New module loaded. Attempting to resolve unresolved dependencied.");

				for(deferred_lookup_table_t::iterator it = m_DeferredLookupTable.begin(), end = m_DeferredLookupTable.end(); it != end; ++it)
				{
					Class* base = getClass(it->first);
					InfoLog() << "Checking " << it->first;
					if(base)
					{
						InfoLog() << it->first << " resolved.";
						//Do a lookup for a complete set of classes
						deferred_lookup_table_t::iterator_range range = m_DeferredLookupTable.find(it->first);
						it = range.second;

						for(deferred_lookup_table_t::iterator classes = range.first; classes != range.second; ++classes)
							classes->second->addBase(base);
						// Erase whole range from lookup table
						m_DeferredLookupTable.erase(range);
					} // class resolved
				} // Loop through the table

				if(m_DeferredLookupTable.empty())
				{
					DebugLog("No unresolved dependencies left.");
					m_DeferredLookupTable.reset();
				}
			} // m_DeferredLookup.size()
		} // synchronize
	}// addModule

} // namespace reflect
