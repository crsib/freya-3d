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
#include "SM4_Full/OpenGL_GLSL_SM4_Full.h"
#include "SM4_NoDS/OpenGL_GLSL_SM4_NoDS.h"
#include "SM4_NoMRT/OpenGL_GLSL_SM4_NoMRT.h"
#include "SM4_NoMRTDS/OpenGL_GLSL_SM4_NoMRTDS.h"


extern "C" EXPORT void 		set_memory_allocator(core::memory::ALLOCATE alloc,core::memory::FREE free,core::PluginCore*	pl)
{
	core::memory::Allocate 	= alloc;
	core::memory::Free     	= free;
	core::CoreInstance		= pl;
}

extern "C" EXPORT unsigned drivers_count()
{
	return 4;
}

extern "C" EXPORT unsigned		driver_type(unsigned id)
{
	if(id < 4)
		return core::drivermodel::RENDERER;
	return 0;
}

extern "C" EXPORT const char*	driver_name(unsigned id)
{
	switch(id)
	{
		case 0:
		{
			return "OpenGL GLSL SM40 MRT DS";
		}
		break;
		case 1:
		{
			return "OpenGL GLSL SM40 MRT";
		}
		break;
		case 2:
		{
			return "OpenGL GLSL SM40 DS";
		}
		break;
		case 3:
		{
			return "OpenGL GLSL SM40";
		}
		break;
	}
	return NULL;
}

extern "C" EXPORT core::drivermodel::Driver* create_driver(const char * driverName)
{
	EString name(driverName);
	renderer::drivers::ids::OpenGL_GLSL_SM4_FULL 	id1;
	renderer::drivers::ids::OpenGL_GLSL_SM4_NODS	id2;
	renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRT	id3;
	renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRTDS	id4;
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
	else if(id4.id() == name)
	{
		return id4.create();
	}
	return NULL;
}