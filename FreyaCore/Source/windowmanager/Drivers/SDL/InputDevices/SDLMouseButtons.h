/*
 * SDLMouseButtons.h
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#ifndef SDLMOUSEBUTTONS_H_
#define SDLMOUSEBUTTONS_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/InputDevices/KeyDrivenDevice.h"


namespace windowmanager
{
class SDLManagerDriver;
namespace input
{
namespace drivers
{
namespace sdl
{
class InputDeviceFactory;

namespace ids
{
class SDLMouseButtonsID;
}

class SDLMouseButtons: public KeyDrivenDevice
{
	friend class windowmanager::input::drivers::sdl::ids::SDLMouseButtonsID;
	friend class windowmanager::SDLManagerDriver;
protected:
	SDLMouseButtons();
	virtual ~SDLMouseButtons();
public:
	virtual EString id() const;
	virtual bool getKeyState(unsigned Key);
	virtual void updateState(); //Updates state

	//For normal mode
	//First argument is KeyAction, second - Key ID
	virtual void registerCallback(unsigned Key,const Callback& callback);
	virtual void dropCallback(unsigned Key);

	virtual void setMode(unsigned mode);//Set processing mode
	virtual void registerCallback(const Callback& callback);//For event-based mode

private:
	int		m_Mouse;
	int 	m_State;
};

}
}
}
}
#endif /* SDLMOUSEBUTTONS_H_ */
