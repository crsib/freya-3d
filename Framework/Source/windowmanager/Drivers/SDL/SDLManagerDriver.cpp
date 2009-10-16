/*
 * SDLManagerDriver.cpp
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#include "SDLManagerDriver.h"
#include "windowmanager/Drivers/SDL/InputDeviceFactory.h"

#include "windowmanager/Drivers/SDL/OpenGLSDLAPIInit.h"

#include "windowmanager/DriverSubsystems/InputDevices/KeyDrivenDevice.h"
#include "windowmanager/DriverSubsystems/InputDevices/MovementDrivenDevice.h"

#include "windowmanager/Callback.h"

#include "windowmanager/WMException.h"

#include <algorithm>
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
SDLWindowManagerDriver::SDLWindowManagerDriver()
{
	clog << "Starting SDL window manager" << endl;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		char* err = SDL_GetError();
		throw windowmanager::WMException("Failed to start SDL: " + EString(err));
	}
	m_Factory = new windowmanager::input::drivers::sdl::InputDeviceFactory();
	m_QuitCallback = NULL;
	m_MouseWheelCallback = NULL;
	m_WindowID = 0;
	m_GLContext = 0;
	m_Fullscreen = 0;
	m_Fmt = NULL;

	//Get avalable modes
	m_NumModes = SDL_GetNumDisplayModes();
	if(m_NumModes)
	{
		m_SDLDisplayModes = reinterpret_cast<SDL_DisplayMode**>(core::memory::Allocate(m_NumModes*sizeof(void*),core::memory::GENERIC_POOL));
		m_FreyaModes      = reinterpret_cast<DisplayMode**>(core::memory::Allocate(m_NumModes*sizeof(void*),core::memory::GENERIC_POOL));
		for(unsigned i = 0; i < m_NumModes;i++)
		{
			SDL_DisplayMode* mode = reinterpret_cast<SDL_DisplayMode*>(core::memory::Allocate(sizeof(SDL_DisplayMode),core::memory::GENERIC_POOL));
			SDL_GetDisplayMode(i,mode);
			DisplayMode*     fmode = new DisplayMode;
			fmode->width = mode->w;
			fmode->height = mode->h;
			fmode->refreshRate = mode->refresh_rate;
			fmode->id  = i;
			m_SDLDisplayModes[i] = mode;
			m_FreyaModes[i] = fmode;
		}
	}
	m_FullScreenMode = 0;
	m_Grabbed = false;
	m_CursorShown = false;
}

SDLWindowManagerDriver::~SDLWindowManagerDriver()
{
	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		delete (*it);
	}

	for(MovementDrivenDeviceListIterator it = m_MovementDrivenDeviceList.begin();it != m_MovementDrivenDeviceList.end();it++)
	{
		delete (*it);
	}
	if(m_NumModes)
	{
		for(unsigned i = 0; i < m_NumModes;i++)
		{
			core::memory::Free(m_SDLDisplayModes[i],core::memory::GENERIC_POOL);
			delete m_FreyaModes[i];
		}
		core::memory::Free(m_SDLDisplayModes,core::memory::GENERIC_POOL);
		core::memory::Free(m_FreyaModes,core::memory::GENERIC_POOL);
	}
	delete m_Factory;
	delete m_QuitCallback;

	if(m_GLContext)
		SDL_GL_DeleteContext(m_GLContext);

	if(m_WindowID)
		SDL_DestroyWindow(m_WindowID);
	SDL_Quit();
}

EString 		SDLWindowManagerDriver::id() const
		{
	return EString("SDL");
		}

void			SDLWindowManagerDriver::setWindowedModeWindowSize(unsigned width,unsigned height)
{
	if(m_WindowID)
	{
		SDL_SetWindowSize(m_WindowID,width,height);
	}
	m_Width = width;
	m_Height = height;
}

void 			SDLWindowManagerDriver::setCaption(const EString& caption)
{
	if(m_WindowID)
	{
		SDL_SetWindowTitle(m_WindowID,caption.c_str());
	}
	m_Caption = caption;
}

void			SDLWindowManagerDriver::setWindowFormat(WindowFormat*	fmt)
{
	if(m_Fmt)
		delete m_Fmt;
	m_Fmt = new WindowFormat();
	::memcpy(m_Fmt,fmt,sizeof(WindowFormat));
}

unsigned		SDLWindowManagerDriver::getSupportedModesNumber()
{
	return m_NumModes;
}

DisplayMode* 	SDLWindowManagerDriver::getDisplayMode(unsigned id)
{
	if(id < m_NumModes)
		return m_FreyaModes[id];
	else
		throw windowmanager::WMException(EString("Mode is not supported"));
}

void			SDLWindowManagerDriver::setFullscreenWindowMode(DisplayMode* mode)
{
	this->setFullscreenWindowMode(mode->id);
}

void			SDLWindowManagerDriver::setFullscreenWindowMode(unsigned id)
{
	if(id < m_NumModes)
	{

		SDL_SetFullscreenDisplayMode(m_SDLDisplayModes[id]);
		m_FullScreenMode = id;
	}
	else
		throw windowmanager::WMException(EString("Mode is not supported"));
}

void			SDLWindowManagerDriver::toggleFullscreen(bool fs)
{
	if(m_WindowID)
	{
		SDL_SetWindowFullscreen(m_WindowID,fs);
	}
	m_Fullscreen = fs;
}

void			SDLWindowManagerDriver::initWindow(renderer::RenderingAPIVersion*	API)
{
	std::clog << "Initializing window..." << std::endl;
	if(m_WindowID)
		this->destroyWindow();
	bool usesDefaultWF = false;
	if(m_Fmt == NULL)
	{
		m_Fmt = new WindowFormat;
	}

	if(API->type() != renderer::RenderingAPIVersion::OPENGL)
		throw windowmanager::WMException("Support for APIs other the OpenGL is not implemented yet");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,API->major() - '0');
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,API->minor() - '0');

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,m_Fmt->RedSize);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,m_Fmt->GreenSize);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,m_Fmt->BlueSize);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,m_Fmt->AlphaSize);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,m_Fmt->BufferSize);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,m_Fmt->DepthSize);

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,m_Fmt->StencilSize);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,m_Fmt->Doublebuffered);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,m_Fmt->Accelerated);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,m_Fmt->Multisampled);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,m_Fmt->MultisampleSamples);

	SDL_GL_SetSwapInterval(m_Fmt->VSync);

	//Now we are ready to create window

	m_WindowID = SDL_CreateWindow(m_Caption.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_Width,m_Height,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(m_WindowID == 0)
		throw windowmanager::WMException("Failed to create window");
	SDL_SetWindowGrab(m_WindowID,m_Grabbed);
	SDL_SetWindowFullscreen(m_WindowID,m_Fullscreen);

	m_GLContext = SDL_GL_CreateContext(m_WindowID);
	if(m_GLContext == 0)
	{
		SDL_DestroyWindow(m_WindowID);
		m_WindowID = 0;
		throw windowmanager::WMException("Failed to create window");
	}
	if(m_Fmt->Multisampled)
		glEnable(GL_MULTISAMPLE);
	if(usesDefaultWF)
	{
		delete m_Fmt;
	}
	std::clog << "Window successfully created" << std::endl;
	clog 	 << "Started renderer:\n\tVendor: " << glGetString( GL_VENDOR )
					<< "\n\tRenderer: " << glGetString( GL_RENDERER )
					<< "\n\tOpenGL version: " << glGetString( GL_VERSION )
					<< "\n\tGLSL version: "<<  glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}


void    	SDLWindowManagerDriver::destroyWindow()
{
	if(m_GLContext)
		SDL_GL_DeleteContext(m_GLContext);
	if(m_WindowID)
		SDL_DestroyWindow(m_WindowID);
	m_GLContext = 	0;
	m_WindowID = 	0;
}

//Time
unsigned		SDLWindowManagerDriver::getTickCount()
{
	return SDL_GetTicks();
}

//Input
KeyDrivenDevice*		SDLWindowManagerDriver::createKeyDrivenDevice(const EString& type)
{
	KeyDrivenDevice* dev = static_cast<KeyDrivenDevice*>(m_Factory->createDriver(type));
	m_KeyDrivenDeviceList.push_back(dev);
	return dev;
}

MovementDrivenDevice*	SDLWindowManagerDriver::createMovementDrivenDevice(const EString& type)
{
	MovementDrivenDevice* dev = static_cast<MovementDrivenDevice*>(m_Factory->createDriver(type));
	m_MovementDrivenDeviceList.push_back(dev);
	return dev;
}

void					SDLWindowManagerDriver::destroyKeyDrivenDevice(KeyDrivenDevice* dev)
{
	KeyDrivenDeviceListIterator it = std::find(m_KeyDrivenDeviceList.begin(),m_KeyDrivenDeviceList.end(),dev);
	if(it == m_KeyDrivenDeviceList.end()) return; //No actual device exists
	m_KeyDrivenDeviceList.erase(it);
	delete dev;
}

void					SDLWindowManagerDriver::destroyMovementDrivenDevice(MovementDrivenDevice* dev)
{
	MovementDrivenDeviceListIterator it = std::find(m_MovementDrivenDeviceList.begin(),m_MovementDrivenDeviceList.end(),dev);
	if(it == m_MovementDrivenDeviceList.end()) return; //No actual device exists
	m_MovementDrivenDeviceList.erase(it);
	delete dev;
}

//Events updating
void		SDLWindowManagerDriver::updateEvents()
{
	SDL_Event	event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			if(m_QuitCallback)
				m_QuitCallback->call();
			break;
		case SDL_MOUSEWHEEL:
			if(m_MouseWheelCallback)
				m_MouseWheelCallback->call(event.wheel.which,event.wheel.y);
			break;
		}

	}
	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		(*it)->updateState();
	}
}

void		SDLWindowManagerDriver::grabInput(bool grab_state)
{
	if(m_WindowID)
		SDL_SetWindowGrab(m_WindowID,grab_state);
	m_Grabbed = grab_state;
}

void		SDLWindowManagerDriver::showCursor(bool cursor_state)
{
	SDL_ShowCursor(cursor_state);
	m_CursorShown = cursor_state;
}

void		SDLWindowManagerDriver::swapBuffers()
{
	if(m_WindowID)
		SDL_GL_SwapWindow(m_WindowID);
}

void		SDLWindowManagerDriver::setQuitCallback(const Callback& callback)
{
	if(!m_QuitCallback)
		m_QuitCallback = new Callback(callback);
	else
		*m_QuitCallback = callback;
}

void			SDLWindowManagerDriver::setMouseWheelCallback(const Callback& callback)
{
	if(!m_MouseWheelCallback)
		m_MouseWheelCallback = new Callback(callback);
	else
		*m_MouseWheelCallback = callback;
}

void		SDLWindowManagerDriver::setKeydrivenDeviceMode(unsigned mode)
{
	for(KeyDrivenDeviceListIterator it = m_KeyDrivenDeviceList.begin();it != m_KeyDrivenDeviceList.end();it++)
	{
		(*it)->setMode(mode);
	}


}

void		SDLWindowManagerDriver::setMovementDrivenDevice(unsigned mode)
{
	for(MovementDrivenDeviceListIterator it = m_MovementDrivenDeviceList.begin();it != m_MovementDrivenDeviceList.end();it++)
	{
		(*it)->setMode(mode);
	}
}

void		SDLWindowManagerDriver::postUserEvent(unsigned uid, void* arg1, void* arg2)
{
	SDL_Event	event;
	event.type = SDL_USEREVENT;
	event.user.code = uid;
	event.user.data1 = arg1;
	event.user.data2 = arg2;
	SDL_PushEvent(&event);
}

}
}

}

