/*
 * SDLManagerDriver.cpp
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#include "SDLManagerDriver.h"
#include "windowmanager/Drivers/SDL/InputDeviceFactory.h"
#include "windowmanager/Drivers/SDL/Multithreading/SDLThread.h"
#include "windowmanager/Drivers/SDL/Multithreading/SDLMutex.h"
#include "windowmanager/Drivers/SDL/Multithreading/SDLSemaphore.h"
#include "windowmanager/Drivers/SDL/Multithreading/SDLCondition.h"

#include "windowmanager/Drivers/SDL/OpenGLSDLAPIInit.h"

#include "windowmanager/DriverSubsystems/InputDevices/KeyDrivenDevice.h"
#include "windowmanager/DriverSubsystems/InputDevices/MovementDrivenDevice.h"

#include "windowmanager/Callback.h"

#include "windowmanager/WMException.h"

#include <algorithm>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <iostream>
using std::clog;
using std::endl;

namespace windowmanager
{
namespace drivers
{
namespace sdl
{
using namespace windowmanager::input;
using namespace windowmanager::multithreading;
SDLManagerDriver::SDLManagerDriver()
{
	clog << "Starting SDL window manager" << endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	m_Factory = new windowmanager::input::drivers::sdl::InputDeviceFactory();
	m_QuitCallback = NULL;
}

SDLManagerDriver::~SDLManagerDriver()
{
	for(ThreadListIterator it = m_ThreadList.begin();it != m_ThreadList.end();it++)
	{
		(*it)->killThread();
		delete static_cast<windowmanager::multithreading::drivers::sdl::SDLThread*>(*it);
	}
	for(MutexListIterator it = m_MutexList.begin();it != m_MutexList.end();it++)
	{
		delete static_cast<windowmanager::multithreading::drivers::sdl::SDLMutex*>(*it);
	}
	for(SemaphoreListIterator it = m_SemaphoreList.begin();it != m_SemaphoreList.end();it++)
	{
		delete static_cast<windowmanager::multithreading::drivers::sdl::SDLSemaphore*>(*it);
	}
	for(ConditionListIterator it = m_ConditionList.begin();it != m_ConditionList.end();it++)
	{
		delete static_cast<windowmanager::multithreading::drivers::sdl::SDLCondition*>(*it);
	}

	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		delete (*it);
	}

	for(MovementDrivenDeviceListIterator it = m_MovementDrivenDeviceList.begin();it != m_MovementDrivenDeviceList.end();it++)
	{
		delete (*it);
	}
	delete m_Factory;
	delete m_QuitCallback;
	if(m_Screen)
		SDL_FreeSurface(m_Screen);
	SDL_Quit();
}

EString 		SDLManagerDriver::id() const
{
	return EString("SDL");
}
void		SDLManagerDriver::createWindow(unsigned Width,unsigned Height,const EString& Caption,bool Fullscreen,const RenderingAPIInitialization* API)
{
	RenderingAPIInitialization* Api = const_cast<RenderingAPIInitialization*>(API);
	if(Api == 0)
		Api = new OpenGLSDLAPIInit();
	Api->setupAPI();
	if(API == 0)
	{
		delete static_cast<OpenGLSDLAPIInit*>(Api);
	}
	unsigned flag = Fullscreen? SDL_OPENGL | SDL_FULLSCREEN : SDL_OPENGL;
	unsigned bpp =	SDL_VideoModeOK(Width,Height,0,flag);
	if((m_Screen =  SDL_SetVideoMode(Width,Height,bpp,flag)) == NULL)
	{
		clog << "Failed to create window: " << SDL_GetError() << endl;
		throw WMException(EString("Failed to create window: ") + SDL_GetError());
	}
	clog << "Window was successfully created with: " << Width << "x" << Height << "x" << bpp << " " << (Fullscreen ? "fullscreen" : " ") << endl;

	SDL_WM_SetCaption(Caption.c_str(),Caption.c_str());

	clog 	 << "\nVendor " << glGetString( GL_VENDOR ) << "\nRenderer " << glGetString( GL_RENDERER )
	<< "\nVersion " << glGetString( GL_VERSION ) << endl;

}

void    	SDLManagerDriver::destroyWindow()
{
	if(m_Screen)
		SDL_FreeSurface(m_Screen);
}

//Multithreading part
//Threads
Thread*	   	SDLManagerDriver::createThread(int (*fn)(void*),void* param) //Creates thread of execution
{
	Thread*	th	=  new windowmanager::multithreading::drivers::sdl::SDLThread(fn,param);
	m_ThreadList.push_back(th);
	return th;
}

void	 	SDLManagerDriver::destroyThread(Thread* thrd) //Will wait until thread finishes and destroy object
{
	ThreadListIterator it = std::find(m_ThreadList.begin(),m_ThreadList.end(),thrd);
	if(it == m_ThreadList.end()) return; //No actual thread exists
	m_ThreadList.erase(it);
	delete static_cast<windowmanager::multithreading::drivers::sdl::SDLThread*>(thrd);
}

//Mutexes/conditions
Mutex*	  	SDLManagerDriver::createMutex()
{
	Mutex*  mut = new windowmanager::multithreading::drivers::sdl::SDLMutex();
	m_MutexList.push_back(mut);
	return mut;
}

void	  	SDLManagerDriver::destroyMutex(Mutex* mut)
{
	MutexListIterator it = std::find(m_MutexList.begin(),m_MutexList.end(),mut);
	if(it == m_MutexList.end()) return; //No actual mutex exists
	m_MutexList.erase(it);
	delete static_cast<windowmanager::multithreading::drivers::sdl::SDLMutex*>(mut);
}

Condition*	SDLManagerDriver::createCondidtion()
{
	Condition* cond = new windowmanager::multithreading::drivers::sdl::SDLCondition();
	m_ConditionList.push_back(cond);
	return cond;
}

void		SDLManagerDriver::destroyCondition(Condition* cond)
{
	ConditionListIterator it = std::find(m_ConditionList.begin(),m_ConditionList.end(),cond);
	if(it == m_ConditionList.end()) return; //No actual condition exists
	m_ConditionList.erase(it);
	delete static_cast<windowmanager::multithreading::drivers::sdl::SDLCondition*>(cond);
}

//Semaphores
Semaphore*	SDLManagerDriver::createSemaphore(unsigned initial)
{
	Semaphore*	sem = new windowmanager::multithreading::drivers::sdl::SDLSemaphore(initial);
	m_SemaphoreList.push_back(sem);
	return sem;
}

void		SDLManagerDriver::destroySemaphore(Semaphore* sem)
{
	SemaphoreListIterator it = std::find(m_SemaphoreList.begin(),m_SemaphoreList.end(),sem);
	if(it == m_SemaphoreList.end()) return; //No actual semaphore exists
	m_SemaphoreList.erase(it);
	delete static_cast<windowmanager::multithreading::drivers::sdl::SDLSemaphore*>(sem);
}

//Time
unsigned		SDLManagerDriver::getTickCount()
{
	return SDL_GetTicks();
}

//Input
KeyDrivenDevice*		SDLManagerDriver::createKeyDrivenDevice(const EString& type)
{
	KeyDrivenDevice* dev = static_cast<KeyDrivenDevice*>(m_Factory->createDriver(type));
	m_KeyDrivenDeviceList.push_back(dev);
	return dev;
}

MovementDrivenDevice*	SDLManagerDriver::createMovementDrivenDevice(const EString& type)
{
	MovementDrivenDevice* dev = static_cast<MovementDrivenDevice*>(m_Factory->createDriver(type));
	m_MovementDrivenDeviceList.push_back(dev);
	return dev;
}

void					SDLManagerDriver::destroyKeyDrivenDevice(KeyDrivenDevice* dev)
{
	KeyDrivenDeviceListIterator it = std::find(m_KeyDrivenDeviceList.begin(),m_KeyDrivenDeviceList.end(),dev);
	if(it == m_KeyDrivenDeviceList.end()) return; //No actual device exists
	m_KeyDrivenDeviceList.erase(it);
	delete dev;
}

void					SDLManagerDriver::destroyMovementDrivenDevice(MovementDrivenDevice* dev)
{
	MovementDrivenDeviceListIterator it = std::find(m_MovementDrivenDeviceList.begin(),m_MovementDrivenDeviceList.end(),dev);
	if(it == m_MovementDrivenDeviceList.end()) return; //No actual device exists
	m_MovementDrivenDeviceList.erase(it);
	delete dev;
}

//Events updating
void		SDLManagerDriver::updateEvents()
{
	SDL_Event	event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			if(m_QuitCallback)
				m_QuitCallback->call();
	}
	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		(*it)->updateState();
	}
}

void		SDLManagerDriver::grabInput(bool grab_state)
{
	SDL_WM_GrabInput(grab_state ? SDL_GRAB_ON : SDL_GRAB_OFF);
}

void		SDLManagerDriver::showCursor(bool cursor_state)
{
	SDL_ShowCursor(cursor_state);
}

void		SDLManagerDriver::swapBuffers()
{
	SDL_GL_SwapBuffers();
}

void		SDLManagerDriver::setQuitCallback(const Callback& callback)
{
	if(!m_QuitCallback)
		m_QuitCallback = new Callback(callback);
	else
		*m_QuitCallback = callback;
}

void		SDLManagerDriver::setKeydrivenDeviceMode(unsigned mode)
{
	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		(*it)->setMode(mode);
	}


}

void		SDLManagerDriver::setMovementDrivenDevice(unsigned mode)
{
	for(MovementDrivenDeviceListIterator it = m_MovementDrivenDeviceList.begin();it != m_MovementDrivenDeviceList.end();it++)
	{
		(*it)->setMode(mode);
	}
}

void		SDLManagerDriver::postUserEvent(unsigned uid, void* arg1, void* arg2)
{
	SDL_Event	event;
	event.type = SDL_USEREVENT;
	event.user.code = uid;
	event.user.data1 = arg1;
	event.user.data2 = arg2;
	SDL_PushEvent(&event);
}

unsigned	SDLManagerDriver::getThreadID()
{
	return SDL_ThreadID();
}

}
}

}

