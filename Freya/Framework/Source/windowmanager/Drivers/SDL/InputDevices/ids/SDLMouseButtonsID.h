/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef SDLMOUSEBUTTONSID_H_
#define SDLMOUSEBUTTONSID_H_

#include "core/drivermodel/DriverID.h"
#include "windowmanager/Drivers/SDL/InputDevices/SDLMouseButtons.h"
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

class SDLMouseButtonsID : public core::drivermodel::DriverID
{
	friend class windowmanager::input::drivers::sdl::InputDeviceFactory;
protected:
	SDLMouseButtonsID()
	{
	}
	virtual ~SDLMouseButtonsID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new windowmanager::input::drivers::sdl::SDLMouseButtons();
	}

	virtual EString							id()
	{
		return "mouse_buttons";
	}
};

}

}

}

}
}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
