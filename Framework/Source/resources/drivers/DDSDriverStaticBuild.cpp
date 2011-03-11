#include "core/drivermodel/DriverID.h"
#include "DDSDriver.h"

unsigned		DDSDriver_num_entries()
{
	return 1;	
}

core::drivermodel::DriverID*	DDSDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new resources::drivers::DDSDriverID;
		break;
	}
	return NULL;
}
