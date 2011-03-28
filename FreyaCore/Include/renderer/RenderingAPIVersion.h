/*
 * RenderingAPIVersion.h
 *
 *  Created on: Oct 12, 2009
 *      Author: crsib
 */

#ifndef RENDERINGAPIVERSION_H_
#define RENDERINGAPIVERSION_H_

#include "core/EngineSubsystem.h"

namespace renderer
{

//!Defines the version and type of an API
/*!
 * Defines the version and type of an API.<BR>
 * For DirectXGraphics compatibility, version is returned in ASCII encoded format. <BR>
 * For example - DirectX 9.0c will have '9' as major,'0' as minor,'c' as patch.<BR>
 * If patch is insufficient - patch should return 0
 */
class RenderingAPIVersion: public virtual EngineSubsystem
{
public:
	virtual ~RenderingAPIVersion(){}

	//!Defines the type of API
	enum APITYPE
	{
		//! API is OpenGL
		OPENGL,
		//! API is OpenGL ES
		OPENGLES,
		//! API is DirectXGraphics
		DIRECTX,
		//! API is managed DirectX
		MANAGED_DIRECTX
	};
	//! Returns a type of API
	virtual APITYPE type() const 	= 0;
	//! Returns ASCII enconded major version
	virtual char	major() const 	= 0;
	//! Returns ASCII enconded minor version
	virtual char	minor() const 	= 0;
	//! Returns ASCII enconded patch level
	virtual char	patch() const	= 0;
};

}

#endif /* RENDERINGAPIVERSION_H_ */
