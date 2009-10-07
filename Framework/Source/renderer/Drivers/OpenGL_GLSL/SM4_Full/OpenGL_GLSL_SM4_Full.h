/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM4_H_
#define OPENGLGLSLSM4_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_Full/OpenGL_GLSL_Driver_SM4_Full.h"
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
class OpenGL_GLSL_SM4_FULL : public core::drivermodel::DriverID
{
public:
	OpenGL_GLSL_SM4_FULL()
	{
	}
	virtual ~OpenGL_GLSL_SM4_FULL()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new renderer::drivers::opengl_glsl_sm4_full::OpenGL_GLSL_Driver();
	}

	virtual EString							id()
	{
		return "OpenGL GLSL SM40 MRT DS";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
