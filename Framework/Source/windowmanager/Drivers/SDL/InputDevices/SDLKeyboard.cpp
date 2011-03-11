/*
 * SDLKeyboard.cpp
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#include "SDLKeyboard.h"
#include <SDL/SDL.h>
#include <algorithm>

namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
extern const unsigned		SDLKeyboardLookup[];
SDLKeyboard::SDLKeyboard()
{
	//std::fill(m_KeyboardState,m_KeyboardState+sizeof(m_KeyboardState),0);
}

SDLKeyboard::~SDLKeyboard()
{
}

EString 	SDLKeyboard::id() const
{
	return EString("keyboard");
}

void SDLKeyboard::updateState()
{
	Uint8* state = SDL_GetKeyboardState(NULL);
	std::copy(state,state+512,m_KeyboardState);
}

bool SDLKeyboard::getKeyState(unsigned Key)
{
	return m_KeyboardState[windowmanager::input::drivers::sdl::SDLKeyboardLookup[Key]];
}


void SDLKeyboard::registerCallback(unsigned Key,const Callback& callback)
{

}

void SDLKeyboard::dropCallback(unsigned Key)
{

}

void SDLKeyboard::setMode(unsigned mode)
{

}

void SDLKeyboard::registerCallback(const Callback& callback)
{

}

}
}
}
}
