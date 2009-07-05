/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM3SIMPLE_H_
#define OPENGLGLSLSM3SIMPLE_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/OpenGL_GLSL_Driver_SM3_Simple.h"
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
class OpenGL_GLSL_SM3_SIMPLE : public core::drivermodel::DriverID
{
	friend class renderer::RenderingAPIFactory;
	OpenGL_GLSL_SM3_SIMPLE()
	{
	}
	virtual ~OpenGL_GLSL_SM3_SIMPLE()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new renderer::drivers::opengl_glsl_sm3_simple::OpenGL_GLSL_Driver();
	}

	virtual EString							id()
	{
		return "OpenGL GLSL";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
