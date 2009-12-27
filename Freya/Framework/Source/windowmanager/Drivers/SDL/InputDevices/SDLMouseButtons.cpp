/*
 * SDLMouseButtons.cpp
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#include "SDLMouseButtons.h"
#include "windowmanager/DriverSubsystems/InputDevices/MouseButtons.h"
#include <SDL/SDL.h>

namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
SDLMouseButtons::SDLMouseButtons()
{
	m_Mouse = SDL_SelectMouse(-1);

}

SDLMouseButtons::~SDLMouseButtons()
{
}

EString SDLMouseButtons::id() const
{
	return EString("mouse_buttons");
}

void SDLMouseButtons::updateState()
{
	m_State = SDL_GetMouseState(NULL,NULL);
}

bool SDLMouseButtons::getKeyState(unsigned key)
{
	//std::cout << "[SDL::MOUSE]: Key state requested: " << m_State << std::endl;
	return (m_State & SDL_BUTTON(key));
	return false;
}

void SDLMouseButtons::registerCallback(unsigned Key,const Callback& callback)
{

}

void SDLMouseButtons::dropCallback(unsigned Key)
{

}

void SDLMouseButtons::setMode(unsigned mode)
{

}

void SDLMouseButtons::registerCallback(const Callback& callback)
{

}
}
}
}
}

