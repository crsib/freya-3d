/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM3MRTDS_H_
#define OPENGLGLSLSM3MRTDS_H_

#include "core/drivermodel/DriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRTDS/OpenGL_GLSL_Driver_SM3_NoMRTDS.h"
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
class OpenGL_GLSL_SM3_NOMRTDS : public core::drivermodel::DriverID
{
public:
	OpenGL_GLSL_SM3_NOMRTDS()
	{
	}
	virtual ~OpenGL_GLSL_SM3_NOMRTDS()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new renderer::drivers::opengl_glsl_sm3_nomrtds::OpenGL_GLSL_Driver();
	}

	virtual EString							id() const
	{
		return "OpenGL GLSL SM3";
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
