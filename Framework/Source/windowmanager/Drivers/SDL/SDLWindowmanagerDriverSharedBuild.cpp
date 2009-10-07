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
#include "SDLDriverID.h"

extern "C" EXPORT void 		set_memory_allocator(core::memory::ALLOCATE alloc,core::memory::FREE free,core::PluginCore*	pl)
{
	core::memory::Allocate 	= alloc;
	core::memory::Free     	= free;
	core::CoreInstance		= pl;
}

extern "C" EXPORT unsigned drivers_count()
{
	return 1;
}

extern "C" EXPORT unsigned		driver_type(unsigned id)
{
	if(id == 0)
		return core::drivermodel::WINDOWMANAGER;
	return 0;
}

extern "C" EXPORT const char*	driver_name(unsigned id)
{
	switch(id)
	{
		case 0:
		{
			return "SDL";
		}
	}
	return NULL;
}

extern "C" EXPORT core::drivermodel::Driver* create_driver(const char * driverName)
{
	EString name(driverName);
	windowmanager::drivers::sdl::SDLDriverID 	id1;
	if(id1.id() == name)
	{
		return id1.create();
	}
	return NULL;
}