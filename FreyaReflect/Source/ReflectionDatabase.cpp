/* File		: FreyaReflect: ReflectionDatabase.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/ReflectionDatabase.h"
#include "core/Log.h"

namespace reflect
{
	namespace
	{
		static ReflectionDatabase& __internal_db_starter = ReflectionDatabase::GetInstance(); //Start the DB as soon, as library is loaded. 

		class RootScope : public Scope
		{
		public:
			RootScope() : Scope(NamespaceScope,"",NULL) {}
		};
	}

	ReflectionDatabase::ReflectionDatabase()
	{
		InfoLog() << "Straiting reflection engine started"; // This will actually force that the memory arena is created first, log system - second and the reflector - third
		//Create root scope
		m_RootScope = scope_ptr_t(new RootScope);
	}

	ReflectionDatabase::~ReflectionDatabase()
	{
		InfoLog() << "Stopping reflection engine";
	}

} // namespace reflect
