#include "core/drivermodel/DriverID.h"
#include "LzmaFilesystemDriverID.h"

unsigned		LzmaFilesystemDriver_num_entries()
{
	return 1;	
}

core::drivermodel::DriverID*	LzmaFilesystemDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new core::filesystem::drivers::ids::LzmaFilesystemDriverID;
		break;
	}
	return NULL;
}
