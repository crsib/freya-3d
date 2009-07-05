/*
 * RenderingAPI.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef RENDERINGAPI_H_
#define RENDERINGAPI_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace windowmanager
{
class RenderingAPIInitialization: virtual public ::EngineSubsystem
{
	friend class WindowManagerDriver;
protected:
	RenderingAPIInitialization()
	{
	}
	~RenderingAPIInitialization()
	{
	}
public:
	virtual unsigned getAPI_ID() = 0;
	virtual void setupAPI()  = 0;
};

}
#endif /* RENDERINGAPI_H_ */
