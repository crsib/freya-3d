#include <cstdlib>
#include <cstring>
#include "core/PluginCore.h"

//Needfull inculdes
#include "internal.h"
#include "core/drivermodel/Driver.h"
//Ids
#include "SDLDriverID.h"

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
