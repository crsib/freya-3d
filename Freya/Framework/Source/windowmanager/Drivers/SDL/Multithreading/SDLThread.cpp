/*
 * SDLThread.cpp
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#include "SDLThread.h"

#include <SDL/SDL.h>

namespace windowmanager
{
namespace multithreading
{
namespace drivers
{
namespace sdl
{
SDLThread::SDLThread(int (*fn)(void* v),void* p) : Thread(fn,p)
{
	m_Thread = SDL_CreateThread(fn,p);
}

SDLThread::~SDLThread()
{
}

unsigned 	SDLThread::getThreadID()
{
	return SDL_GetThreadID(m_Thread);
}

unsigned 	SDLThread::waitThread()
{
	int st;
	SDL_WaitThread(m_Thread,&st);
	return (unsigned) st;
}

void		SDLThread::killThread()
{
	SDL_KillThread(m_Thread);
}

}
}
}
}

