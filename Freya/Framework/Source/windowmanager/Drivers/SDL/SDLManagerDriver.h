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

#include "windowmanager/WindowManagerDriver.h"
#include "core/memory/MemoryAllocator.h"

#include "core/EString.h"
#include <list>
#include <map>
#include <SDL/SDL.h>


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
class SDLWindowManagerDriver: public windowmanager::WindowManagerDriver
{
	friend class core::EngineCore;
	friend class windowmanager::drivers::sdl::SDLDriverID;
protected:
	SDLWindowManagerDriver();
	~SDLWindowManagerDriver();
public:
	//Typedefs
	typedef std::list<windowmanager::input::KeyDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::KeyDrivenDevice*> > KeyDrivenDeviceList;
	typedef std::list<windowmanager::input::KeyDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::KeyDrivenDevice*> >::iterator KeyDrivenDeviceListIterator;

	typedef std::list<windowmanager::input::MovementDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::MovementDrivenDevice*> > MovementDrivenDeviceList;
	typedef std::list<windowmanager::input::MovementDrivenDevice*,core::memory::MemoryAllocator<windowmanager::input::MovementDrivenDevice*> >::iterator MovementDrivenDeviceListIterator;


	virtual EString		id() const;
	//Window part
	virtual void		setWindowedModeWindowSize(unsigned width,unsigned height);

	virtual void 		setCaption(const EString& caption);

	virtual void		setWindowFormat(WindowFormat*	fmt);

	virtual unsigned	getSupportedModesNumber();

	virtual DisplayMode*getDisplayMode(unsigned id);

	virtual void		setFullscreenWindowMode(DisplayMode* mode);
	virtual void		setFullscreenWindowMode(unsigned id);

	virtual void		toggleFullscreen(bool fs);

	virtual void		initWindow(renderer::RenderingAPIVersion*	API);

	virtual void		setMouseWheelCallback(const Callback& callback);

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

	virtual unsigned	getWindowWidth() const;
	virtual unsigned	getWindowHeight() const;
private:
	//resource managment system
	KeyDrivenDeviceList 		m_KeyDrivenDeviceList;
	MovementDrivenDeviceList 	m_MovementDrivenDeviceList;

	//Window
	SDL_WindowID				m_WindowID;
	SDL_GLContext				m_GLContext;
	unsigned					m_Width;
	unsigned					m_Height;
	unsigned					m_Fullscreen;
	WindowFormat*				m_Fmt;
	EString						m_Caption;
	SDL_DisplayMode**			m_SDLDisplayModes;
	DisplayMode**				m_FreyaModes;
	unsigned					m_NumModes;
	unsigned					m_FullScreenMode;
	//Input events
	Callback*					m_QuitCallback;
	Callback*					m_MouseWheelCallback;

	unsigned					m_Grabbed;
	unsigned					m_CursorShown;
	windowmanager::input::drivers::sdl::InputDeviceFactory*	m_Factory;
};

}
}
}

#endif /* SDLMANAGERDRIVER_H_ */
