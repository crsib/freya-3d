/*
 * SDLMouse.cpp
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#include "SDLMouse.h"
#include <SDL/SDL.h>

namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
SDLMouse::SDLMouse()
{
	m_Mouse = SDL_SelectMouse(-1);
}

SDLMouse::~SDLMouse()
{
}

EString SDLMouse::id() const
{
	return EString("mouse");
}

bool SDLMouse::isAbsoluteCaptureSupported()
{
	return true;
}

void SDLMouse::absoluteState(int*x,int* y)
{
	SDL_GetMouseState(x,y);
}

bool SDLMouse::isRelativeCaptureSupported()
{
	return true;
}

void SDLMouse::relativeState(int* x,int* y)
{
	SDL_GetRelativeMouseState(0,x,y);
	//SDL_GetMouseState(0,x,y);
	//std::cout << "Mouse relative " << m_Mouse << " " << *x << " " << *y << " " << std::endl;
}


void SDLMouse::setMode(unsigned mode)
{

}

void SDLMouse::registerCallback(const Callback& callback)
{

}
}
}
}
}
