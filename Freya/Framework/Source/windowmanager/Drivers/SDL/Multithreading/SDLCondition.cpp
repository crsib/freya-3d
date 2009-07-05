/*
 * SDLCondition.cpp
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#include "SDLCondition.h"
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
SDLCondition::SDLCondition()
{
	m_Condition = SDL_CreateCond();

}

SDLCondition::~SDLCondition()
{
	SDL_CondBroadcast(m_Condition);
	SDL_DestroyCond(m_Condition);
}

void SDLCondition::signal()
{
	SDL_CondSignal(m_Condition);
}

void SDLCondition::broadcast()
{
	SDL_CondBroadcast(m_Condition);
}

void SDLCondition::wait(const Mutex* mut)
{
	SDL_CondWait(m_Condition,static_cast<SDLMutex*>(const_cast<Mutex*>(mut))->m_Mutex);
}

}
}
}
}
