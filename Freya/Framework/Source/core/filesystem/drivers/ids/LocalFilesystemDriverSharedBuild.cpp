#include <cstdlib>
#include <cstring>

#include "core/PluginCore.h"

namespace core
{
namespace memory
{
	typedef void* (*ALLOCATE)(size_t,unsigned);
	typedef void  (*FREE)(void*,unsigned);
	extern ALLOCATE Allocate;
	extern FREE Free;
	ALLOCATE	 Allocate = NULL;
	FREE		 Free     = NULL;
	
}
	extern core::PluginCore* CoreInstance;
	core::PluginCore*	  CoreInstance;
}
//Needfull inculdes
#include "internal.h"
#include "core/drivermodel/Driver.h"
//Ids
#include "AppHomeFilesystemDriverID.h"
#include "CurrentFilesystemDriverID.h"
#include "LocalFilesystemDriverID.h"

extern "C" EXPORT unsigned drivers_count()
{
	return 3;
}

extern "C" EXPORT void 		set_memory_allocator(core::memory::ALLOCATE alloc,core::memory::FREE free,core::PluginCore*	pl)
{
	core::memory::Allocate = alloc;
	core::memory::Free     = free;
	core::CoreInstance	   = pl;
}

extern "C" EXPORT unsigned		driver_type(unsigned id)
{
	if(id < 3)
		return core::drivermodel::FILESYSTEM;
	return 0;
}

extern "C" EXPORT const char*	driver_name(unsigned id)
{
	switch(id)
	{
		case 0:
		{
			return "app-home";
		}
		break;
		case 1:
		{
			return "pwd";
		}
		break;
		case 2:
		{
			return "local";
		}
		break;
	}
	return NULL;
}

extern "C" EXPORT core::drivermodel::Driver* create_driver(const char * driverName)
{
	EString name(driverName);
	core::filesystem::drivers::ids::AppHomeFilesystemDriverID 	id1;
	core::filesystem::drivers::ids::CurrentFilesystemDriverID 	id2;
	core::filesystem::drivers::ids::LocalFilesystemDriverID 	id3;
	if(id1.id() == name)
	{
		return id1.create();
	}
	else if(id2.id() == name)
	{
		return id2.create();	
	}
	else if(id3.id() == name)
	{
		return id3.create();	
	}
	return NULL;
}