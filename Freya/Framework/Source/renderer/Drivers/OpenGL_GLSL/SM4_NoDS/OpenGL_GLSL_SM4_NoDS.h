/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM4DS_H_
#define OPENGLGLSLSM4DS_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_NoDS/OpenGL_GLSL_Driver_SM4_NoDS.h"
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
class OpenGL_GLSL_SM4_NODS : public core::drivermodel::DriverID
{
public:
	OpenGL_GLSL_SM4_NODS()
	{
	}
	virtual ~OpenGL_GLSL_SM4_NODS()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new renderer::drivers::opengl_glsl_sm4_nods::OpenGL_GLSL_Driver;
	}

	virtual EString							id() const
	{
		return "OpenGL GLSL SM40 MRT";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
