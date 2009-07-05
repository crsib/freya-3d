/*
 * SDLMutex.cpp
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#include "SDLMutex.h"
#include <SDL/SDL.h>
namespace windowmanager
{
namespace multithreading
{
namespace drivers
{
namespace sdl
{
SDLMutex::SDLMutex()
{
	m_Mutex = SDL_CreateMutex();
}

SDLMutex::~SDLMutex()
{
	SDL_DestroyMutex(m_Mutex);
}

void SDLMutex::lock()
{
	SDL_LockMutex(m_Mutex);
}

void SDLMutex::unlock()
{
	SDL_UnlockMutex(m_Mutex);
}

}
}
}
}
