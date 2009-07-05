/*
 * SDLMouse.h
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#ifndef SDLMOUSE_H_
#define SDLMOUSE_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/InputDevices/MovementDrivenDevice.h"

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
class SDLMouseID;
}

class SDLMouse: public MovementDrivenDevice
{
	friend class windowmanager::input::drivers::sdl::ids::SDLMouseID;
	friend class windowmanager::SDLManagerDriver;
protected:
	SDLMouse();
	virtual ~SDLMouse();
public:
	virtual EString	id() const;
	virtual bool 	isRelativeCaptureSupported();
	virtual void	relativeState(int* x,int* y);

	virtual bool	isAbsoluteCaptureSupported();
	virtual void	absoluteState(int* x,int* y);

	virtual void setMode(unsigned mode);//Set processing mode
	virtual void registerCallback(const Callback& callback);//For event-based mode
private:
	int		m_Mouse;
};

}
}
}
}
#endif /* SDLMOUSE_H_ */
