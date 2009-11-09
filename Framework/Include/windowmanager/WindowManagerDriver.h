/*
 * WindowManagerDriver.h
 *
 *  Created on: 27-Aug-08
 *      Author: vedenko
 */

#ifndef WINDOWMANAGERDRIVER_H_
#define WINDOWMANAGERDRIVER_H_

#include "core/EString.h"
#include "core/drivermodel/Driver.h"
#include "windowmanager/DisplayMode.h"
#include "windowmanager/WindowFormat.h"
#include "renderer/RenderingAPIVersion.h"
/*
 * This class is a abstratction of what WindowManager must be
 * Window Manager must provide access to creating/destroying window, parsing system messages, input handling, start of a main loop, creating and destroyng threads
 */

namespace core
{
class EngineCore;
}
//!Namespace related to window managment and other window system specific futures of Freya 3D engine
namespace windowmanager
{

class RenderingAPIInitialization;

namespace input
{
class KeyDrivenDevice;
class MovementDrivenDevice;
}
//Internal message subsystem

//

namespace EventType
{
enum
{
	QUIT,
	USER_EVENT
};
}

namespace ProcessingMode
{
enum
{
	NORMAL,
	EVENT_BASED
};
}

class Callback;
//! This class provides interface to all WindowManager drivers
/*!
 * This class provides interface to all WindowManager drivers. The window, itself is created when creating renderer class.
 * The inherited classes must provide correct initialization and management for all rendering APIs it supports
 */
class WindowManagerDriver : public core::drivermodel::Driver
{
	//Driver(WindowManagerDriver)
	friend class core::EngineCore;
protected:
	WindowManagerDriver(){}
	virtual ~WindowManagerDriver(){}
public:
	virtual EString		id() const = 0;
	//Window part
	//! Sets the window size for windowed mode
	virtual void		setWindowedModeWindowSize(unsigned width,unsigned height) = 0;
	//! Sets the window caption
	virtual void 		setCaption(const EString& caption) = 0;
	//! Sets the desired window format. This will affect only for windows created after format is set
	virtual void		setWindowFormat(WindowFormat*	fmt) = 0;
	//! Returns the number of display modes for full screen
	virtual unsigned	getSupportedModesNumber()			=  0;
	//! Returns the mode for id (0 < id < getSupportedModesNumber() )
	virtual DisplayMode*getDisplayMode(unsigned id)			=  0;
	//! Set the fullscreen window mode
	virtual void		setFullscreenWindowMode(DisplayMode* mode) = 0;
	virtual void		setFullscreenWindowMode(unsigned id)	= 0;
	//! Toggles fullscreen
	virtual void		toggleFullscreen(bool fs) = 0;
	//! Creates window and initializes specified RAPI. Destroys API
	virtual void		initWindow(renderer::RenderingAPIVersion*	API) = 0;
	//! Destroys window (does not destroys RAPIDriver)
	virtual void		destroyWindow() = 0;

	virtual unsigned	getWindowWidth() const = 0;
	virtual unsigned	getWindowHeight() const = 0;
	//Time
	virtual unsigned	getTickCount() = 0;
	//Input
	virtual windowmanager::input::KeyDrivenDevice*		createKeyDrivenDevice(const EString& type) = 0;
	virtual windowmanager::input::MovementDrivenDevice*	createMovementDrivenDevice(const EString& type) = 0;

	virtual void					destroyKeyDrivenDevice(windowmanager::input::KeyDrivenDevice* dev) = 0;
	virtual void					destroyMovementDrivenDevice(windowmanager::input::MovementDrivenDevice* dev) = 0;
	//!Events updating and processing
	virtual void		updateEvents() = 0;
	//! Set call back for quit event. No parameters passed
	virtual void		setQuitCallback(const Callback& callback) = 0;
	//! Set the mouse wheel callback. p1 is int and represents a mouse. p2 is int and represents an event value
	virtual void		setMouseWheelCallback(const Callback& callback) = 0;

	//This function will post a user event
	virtual void		postUserEvent(unsigned uid, void* arg1, void* arg2) = 0;
	//WM
	virtual void		grabInput(bool grab_state) = 0;
	virtual void		showCursor(bool show_state) = 0;
	virtual void		swapBuffers() = 0;
};

}


#endif /* WINDOWMANAGERDRIVER_H_ */
