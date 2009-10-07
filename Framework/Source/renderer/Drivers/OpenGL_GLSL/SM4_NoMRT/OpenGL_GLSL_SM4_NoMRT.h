/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLS4MRT_H_
#define OPENGLGLSLS4MRT_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_NoMRT/OpenGL_GLSL_Driver_SM4_NoMRT.h"
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
class OpenGL_GLSL_SM4_NOMRT : public core::drivermodel::DriverID
{
public:
	OpenGL_GLSL_SM4_NOMRT()
	{
	}
	virtual ~OpenGL_GLSL_SM4_NOMRT()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new renderer::drivers::opengl_glsl_sm4_nomrt::OpenGL_GLSL_Driver();
	}

	virtual EString							id()
	{
		return "OpenGL GLSL SM3 DS";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
