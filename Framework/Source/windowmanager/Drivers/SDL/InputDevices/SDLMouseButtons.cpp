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

void SDLMouseButtons::updateState(){}

bool SDLMouseButtons::getKeyState(unsigned key)
{
	return SDL_GetMouseState(m_Mouse,NULL,NULL) & SDL_BUTTON(key);
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

