#include "core/drivermodel/DriverID.h"

#include "SM3_Full/OpenGL_GLSL_SM3_Full.h"
#include "SM4_Full/OpenGL_GLSL_SM4_Full.h"

#include "SM3_NoDS/OpenGL_GLSL_SM3_NoDS.h"
#include "SM4_NoDS/OpenGL_GLSL_SM4_NoDS.h"

#include "SM3_NoMRT/OpenGL_GLSL_SM3_NoMRT.h"
#include "SM4_NoMRT/OpenGL_GLSL_SM4_NoMRT.h"

#include "SM3_NoMRTDS/OpenGL_GLSL_SM3_NoMRTDS.h"
#include "SM4_NoMRTDS/OpenGL_GLSL_SM4_NoMRTDS.h"

#include "SM3_Simple/OpenGL_GLSL_SM3_Simple.h"

unsigned		OpenGLDriver_num_entries()
{
	return 9;	
}

core::drivermodel::DriverID*	OpenGLDriver_driver_id(unsigned n)
{
	switch(n)
	{
		case 0:
			return new renderer::drivers::ids::OpenGL_GLSL_SM3_FULL;
		break;
		case 1:
			return new renderer::drivers::ids::OpenGL_GLSL_SM4_FULL;
		break;
		case 2:
			return new renderer::drivers::ids::OpenGL_GLSL_SM3_NODS;
		break;
		case 3:
			return new renderer::drivers::ids::OpenGL_GLSL_SM4_NODS;
		break;
		case 4:
			return new renderer::drivers::ids::OpenGL_GLSL_SM3_NOMRT;
		break;
		case 5:
			return new renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRT;
		break;
		case 6:
			return new renderer::drivers::ids::OpenGL_GLSL_SM3_NOMRTDS;
		break;
		case 7:
			return new renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRTDS;
		break;
		case 8:
			return new renderer::drivers::ids::OpenGL_GLSL_SM3_SIMPLE;
		break;
	}
	return NULL;
}
