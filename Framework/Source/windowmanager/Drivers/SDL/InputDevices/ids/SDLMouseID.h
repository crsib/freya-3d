/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef SDLMOUSEID_H_
#define SDLMOUSEID_H_
#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif
#include "core/drivermodel/DriverID.h"
#include "windowmanager/Drivers/SDL/InputDevices/SDLMouse.h"
/*
 *
 */

namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
class InputDeviceFactory;

namespace ids
{

class SDLMouseID : public core::drivermodel::DriverID
{
	friend class windowmanager::input::drivers::sdl::InputDeviceFactory;
protected:
	SDLMouseID()
	{
	}
	virtual ~SDLMouseID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new windowmanager::input::drivers::sdl::SDLMouse();
	}

	virtual EString							id()
	{
		return "mouse";
	}
};

}

}

}

}
}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
