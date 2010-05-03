/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef SDLMOUSEID_H_
#define SDLMOUSEID_H_

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
	virtual core::drivermodel::Driver*		create() const
	{
		return new windowmanager::input::drivers::sdl::SDLMouse();
	}

	virtual EString							id() const
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
