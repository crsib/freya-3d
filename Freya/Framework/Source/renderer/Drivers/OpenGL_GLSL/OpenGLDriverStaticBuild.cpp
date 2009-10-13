#include "core/drivermodel/DriverID.h"


#include "OpenGL15Driver/OpenGL_GLSL_SM3_Simple.h"

unsigned		OpenGLDriver_num_entries()
{
	return 1;
}

core::drivermodel::DriverID*	OpenGLDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new renderer::drivers::ids::OpenGL15DriverID;
		break;
	}
	return NULL;
}
