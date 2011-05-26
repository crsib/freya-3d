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
		static ReflectionDatabase& __internal_db_starter = ReflectionDatabase::getInstance(); //Start the DB as soon, as library is loaded. 
	}

	ReflectionDatabase::ReflectionDatabase()
	{
		InfoLog() << "Straiting reflection engine started"; // This will actually force that the memory arena is created first, log system - second and the reflector - third
	}

	ReflectionDatabase::~ReflectionDatabase()
	{
		InfoLog() << "Stopping reflection engine";
	}

} // namespace reflect
