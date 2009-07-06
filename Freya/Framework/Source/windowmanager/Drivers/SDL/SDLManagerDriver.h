/*
 * SDLManagerDriver.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef SDLMANAGERDRIVER_H_
#define SDLMANAGERDRIVER_H_

/*
 *
 */
#include "windowmanager/WindowManagerDriver.h"
#include "core/memory/MemoryAllocator.h"

#include "core/EString.h"
#include <list>
#include <map>
struct SDL_Surface;


namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
class InputDeviceFactory;
}
}
}

namespace drivers
{
namespace sdl
{
class SDLDriverID;
}

}
}


namespace core
{
class EngineCore;
}

namespace windowmanager
{
namespace drivers
{
namespace sdl
{
class SDLManagerDriver: public windowmanager::WindowManagerDriver
{
	friend class core::EngineCore;
	friend class windowmanager::drivers::sdl::SDLDriverID;
protected:
	SDLManagerDriver();
	~SDLManagerDriver();
public:
	//Typedefs
	typedef std::list<windowmanager::input::KeyDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::KeyDrivenDevice*> > KeyDrivenDeviceList;
	typedef std::list<windowmanager::input::KeyDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::KeyDrivenDevice*> >::iterator KeyDrivenDeviceListIterator;

	typedef std::list<windowmanager::input::MovementDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::MovementDrivenDevice*> > MovementDrivenDeviceList;
	typedef std::list<windowmanager::input::MovementDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::MovementDrivenDevice*> >::iterator MovementDrivenDeviceListIterator;


	virtual EString		id() const;
	//Window part
	virtual void		createWindow(unsigned Width,unsigned Height,const EString& Caption,bool Fullscreen = false,const RenderingAPIInitialization* API = 0);
	virtual void    	destroyWindow();

	//Time
	virtual unsigned		getTickCount();
	//Input
	virtual windowmanager::input::KeyDrivenDevice*		createKeyDrivenDevice(const EString& type);
	virtual windowmanager::input::MovementDrivenDevice*		createMovementDrivenDevice(const EString& type);

	virtual void					destroyKeyDrivenDevice(windowmanager::input::KeyDrivenDevice* dev);
	virtual void					destroyMovementDrivenDevice(windowmanager::input::MovementDrivenDevice* dev);
	//Events updating
	virtual void		updateEvents();

	virtual void		setQuitCallback(const windowmanager::Callback& callback); //Support for user and quit. All devices are processed in different way
	//Sets the mode for whole device.
	//For keydriven devices it is available to set individual callbacks for keys
	//For undestardable reason, its no efficient way to make the movement based actions to send messages only in specicified areas.
	//(Actually, resulting speed will be the same)
	virtual void		setKeydrivenDeviceMode(unsigned mode);
	virtual void		setMovementDrivenDevice(unsigned mode);
	//This function will post a user event
	virtual void		postUserEvent(unsigned uid, void* arg1, void* arg2);

	virtual void		grabInput(bool grab_state);
	virtual void		showCursor(bool show_state);
	virtual void		swapBuffers();
private:
	//resource managment system
	KeyDrivenDeviceList 		m_KeyDrivenDeviceList;
	MovementDrivenDeviceList 	m_MovementDrivenDeviceList;

	//Window
	SDL_Surface*				m_Screen;
	//Input events
	Callback*					m_QuitCallback;
	windowmanager::input::drivers::sdl::InputDeviceFactory*	m_Factory;
};

}
}
}

#endif /* SDLMANAGERDRIVER_H_ */
