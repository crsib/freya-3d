#include "core/drivermodel/DriverID.h"
#include "LocalFilesystemDriverID.h"
#include "AppHomeFilesystemDriverID.h"
#include "CurrentFilesystemDriverID.h"

unsigned		BoostFilesystemDriver_num_entries()
{
	return 3;	
}

core::drivermodel::DriverID*	BoostFilesystemDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new core::filesystem::drivers::ids::LocalFilesystemDriverID;
		break;
		case 1:
			return new core::filesystem::drivers::ids::AppHomeFilesystemDriverID;
		break;
		case 2: 
			return new core::filesystem::drivers::ids::CurrentFilesystemDriverID;
		break;	
	}
	return NULL;
}
