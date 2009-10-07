#include "core/drivermodel/DriverID.h"
#include "TGADriver.h"

unsigned		TGADriver_num_entries()
{
	return 1;	
}

core::drivermodel::DriverID*	TGADriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new resources::drivers::TGADriverID;
		break;
	}
	return NULL;
}
