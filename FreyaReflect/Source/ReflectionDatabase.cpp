/* File		: FreyaReflect: ReflectionDatabase.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/ReflectionDatabase.h"
#include "core/Log.h"
#include "reflect/Class.h"

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

	ReflectionDatabase::ReflectionDatabase() : ReflectionConsumer("FreyaReflect")
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

} // namespace reflect
