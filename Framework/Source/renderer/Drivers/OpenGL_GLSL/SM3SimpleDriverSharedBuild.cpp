#include <cstdlib>
#include <cstring>
#include "core/PluginCore.h"

//Needfull inculdes
#include "internal.h"
#include "core/drivermodel/Driver.h"
//Ids
#include "OpenGL15Driver/OpenGL_GLSL_SM3_Simple.h"

extern "C" PLUGIN_EXPORT unsigned drivers_count()
{
	return 1;
}

extern "C" PLUGIN_EXPORT unsigned		driver_type(unsigned id)
{
	if(id == 0)
		return core::drivermodel::RENDERER;
	return 0;
}

extern "C" PLUGIN_EXPORT const char*	driver_name(unsigned id)
{
	switch(id)
	{
		case 0:
		{
			return "OpenGL 1.5 GLSL";
		}
		break;
	}
	return NULL;
}

extern "C" PLUGIN_EXPORT core::drivermodel::Driver* create_driver(const char * driverName)
{
	EString name(driverName);
	renderer::drivers::ids::OpenGL15DriverID 	id1;
	if(id1.id() == name)
	{
		return id1.create();
	}
	return NULL;
}
