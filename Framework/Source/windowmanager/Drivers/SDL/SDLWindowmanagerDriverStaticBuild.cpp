#include "core/drivermodel/DriverID.h"
#include "SDLDriverID.h"

unsigned		SDLDriver_num_entries()
{
	return 1;	
}

core::drivermodel::DriverID*	SDLDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new windowmanager::drivers::sdl::SDLDriverID;
		break;
	}
	return NULL;
}
