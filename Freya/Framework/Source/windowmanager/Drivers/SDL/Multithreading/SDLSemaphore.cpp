/*
 * SDLSemaphore.cpp
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#include "SDLSemaphore.h"
#include <SDL/SDL.h>
namespace windowmanager
{
namespace multithreading
{
namespace drivers
{
namespace sdl
{
SDLSemaphore::SDLSemaphore(unsigned initial_value) : Semaphore(initial_value)
{
	m_Semaphore = SDL_CreateSemaphore(initial_value);
}

SDLSemaphore::~SDLSemaphore()
{
	SDL_DestroySemaphore(m_Semaphore);
}

void	SDLSemaphore::wait()
{
	SDL_SemWait(m_Semaphore);
}

void	SDLSemaphore::post()
{
	SDL_SemPost(m_Semaphore);
}

unsigned SDLSemaphore::value()
{
	return SDL_SemValue(m_Semaphore);
}
}
}
}
}
