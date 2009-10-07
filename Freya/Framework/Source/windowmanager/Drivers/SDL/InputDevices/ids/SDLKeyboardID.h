/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef SDLKEYBOARDID_H_
#define SDLKEYBOARDID_H_
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
#include "windowmanager/Drivers/SDL/InputDevices/SDLKeyboard.h"
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

class SDLKeyboardID : public core::drivermodel::DriverID
{
	friend class windowmanager::input::drivers::sdl::InputDeviceFactory;
protected:
	SDLKeyboardID()
	{
	}
	virtual ~SDLKeyboardID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new windowmanager::input::drivers::sdl::SDLKeyboard();
	}

	virtual EString							id()
	{
		return "keyboard";
	}
};

}

}

}

}
}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
