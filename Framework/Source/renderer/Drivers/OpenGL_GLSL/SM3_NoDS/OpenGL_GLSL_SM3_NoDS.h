/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM3DS_H_
#define OPENGLGLSLSM3DS_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoDS/OpenGL_GLSL_Driver_SM3_NoDS.h"
/*
 *
 */
namespace renderer
{

class RenderingAPIFactory;
namespace drivers
{

namespace ids
{
class OpenGL_GLSL_SM3_NODS : public core::drivermodel::DriverID
{
	friend class renderer::RenderingAPIFactory;
	OpenGL_GLSL_SM3_NODS()
	{
	}
	virtual ~OpenGL_GLSL_SM3_NODS()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new renderer::drivers::opengl_glsl_sm3_nods::OpenGL_GLSL_Driver();
	}

	virtual EString							id()
	{
		return "OpenGL GLSL SM3 MRT";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
