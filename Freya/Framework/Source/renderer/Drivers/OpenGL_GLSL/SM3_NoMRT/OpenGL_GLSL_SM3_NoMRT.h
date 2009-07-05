/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLS3MRT_H_
#define OPENGLGLSLS3MRT_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRT/OpenGL_GLSL_Driver_SM3_NoMRT.h"
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
class OpenGL_GLSL_SM3_NOMRT : public core::drivermodel::DriverID
{
	friend class renderer::RenderingAPIFactory;
	OpenGL_GLSL_SM3_NOMRT()
	{
	}
	virtual ~OpenGL_GLSL_SM3_NOMRT()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new renderer::drivers::opengl_glsl_sm3_nomrt::OpenGL_GLSL_Driver();
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
