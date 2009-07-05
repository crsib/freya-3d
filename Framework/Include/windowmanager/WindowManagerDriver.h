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

namespace multithreading
{
class Thread;
class Mutex;
class Semaphore;
class Condition;
}

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

class WindowManagerDriver : public core::drivermodel::Driver
{
	//Driver(WindowManagerDriver)
	friend class core::EngineCore;
protected:
	WindowManagerDriver(){}
	~WindowManagerDriver(){}
public:
	virtual EString		id() const = 0;
	//Window part
	virtual void		createWindow(unsigned Width,unsigned Height,const EString& Caption,bool Fullscreen,const RenderingAPIInitialization* API = 0) = 0;
	virtual void    	destroyWindow() = 0;

	//Multithreading part
	//Threads
	virtual windowmanager::multithreading::Thread*	   	createThread(int (*fn)(void*),void* param) = 0; //Creates thread of execution
	virtual void	 	destroyThread(windowmanager::multithreading::Thread* thrd) = 0; //Will wait until thread finishes and destroy object
	//Mutexes/conditions
	virtual windowmanager::multithreading::Mutex*	  	createMutex() = 0;
	virtual void	  	destroyMutex(windowmanager::multithreading::Mutex* mut) = 0;

	virtual windowmanager::multithreading::Condition*	createCondidtion() = 0;
	virtual void		destroyCondition(windowmanager::multithreading::Condition* cond) = 0;
	//Semaphores
	virtual windowmanager::multithreading::Semaphore*	createSemaphore(unsigned initial) = 0;
	virtual void		destroySemaphore(windowmanager::multithreading::Semaphore* sem) = 0;
protected:
	virtual unsigned    getThreadID() = 0;
public:
	//Time
	virtual unsigned	getTickCount() = 0;
	//Input
	virtual windowmanager::input::KeyDrivenDevice*		createKeyDrivenDevice(const EString& type) = 0;
	virtual windowmanager::input::MovementDrivenDevice*	createMovementDrivenDevice(const EString& type) = 0;

	virtual void					destroyKeyDrivenDevice(windowmanager::input::KeyDrivenDevice* dev) = 0;
	virtual void					destroyMovementDrivenDevice(windowmanager::input::MovementDrivenDevice* dev) = 0;
	//Events updating and processing
	virtual void		updateEvents() = 0;
	virtual void		setQuitCallback(const Callback& callback) = 0;
	//Sets the mode for whole device.
	//For keydriven devices it is available to set individual callbacks for keys
	//For undestardable reason, its no efficient way to make the movement based actions to send messages only in specicified areas.
	//(Actually, resulting speed will be the same)
	virtual void		setKeydrivenDeviceMode(unsigned mode) = 0;
	virtual void		setMovementDrivenDevice(unsigned mode) = 0;
	//This function will post a user event
	virtual void		postUserEvent(unsigned uid, void* arg1, void* arg2) = 0;
	//WM
	virtual void		grabInput(bool grab_state) = 0;
	virtual void		showCursor(bool show_state) = 0;
	virtual void		swapBuffers() = 0;
};

}


#endif /* WINDOWMANAGERDRIVER_H_ */
