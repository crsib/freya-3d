/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef OPENGLGLSLSM3SIMPLE_H_
#define OPENGLGLSLSM3SIMPLE_H_

#include "renderer/RenderingAPIDriverID.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/OpenGL_GLSL_Driver_SM3_Simple.h"
#include "windowmanager/WindowManagerDriver.h"
#include "core/PluginCore.h"
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
class OpenGL15DriverID : public renderer::RenderingAPIDriverID
{
public:
	OpenGL15DriverID()
	{
	}
	virtual ~OpenGL15DriverID()
	{
	}

public:
	class OpenGL15Version : public renderer::RenderingAPIVersion
		{
			virtual
			APITYPE type() const
			{
				return renderer::RenderingAPIVersion::OPENGL;
			}
			//! Returns ASCII enconded major version
			virtual
			char	major() const
			{
				return '1';
			}
			//! Returns ASCII enconded minor version
			virtual
			char	minor() const
			{
				return '1';
			}
			//! Returns ASCII enconded patch level
			virtual
			char	patch() const
			{
				return 0;
			}
		};


	virtual
	core::drivermodel::Driver*		create() const
	{
		core::CoreInstance->getWindowManager()->initWindow(new OpenGL15Version);
		return new renderer::drivers::opengl_glsl_15::OpenGL_GLSL_Driver();
	}

	virtual
	EString							id() const
	{
		return "OpenGL 1.5 GLSL";
	}


	virtual
	renderer::RenderingAPIVersion*	version() 	const
	{
		return new OpenGL15Version;
	}
};

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
