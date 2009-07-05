/*
 * SDLMutex.h
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#ifndef SDLMUTEX_H_
#define SDLMUTEX_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/Multithreading/Mutex.h"
struct SDL_mutex;

namespace windowmanager
{
namespace drivers
{
namespace sdl
{
class SDLManagerDriver;
}
}
namespace multithreading
{
namespace drivers
{
namespace sdl
{
class SDLMutex: public Mutex
{
	friend class windowmanager::drivers::sdl::SDLManagerDriver;
	friend class SDLCondition;
protected:
	SDLMutex();
	virtual ~SDLMutex();
public:
	virtual void lock();
	virtual void unlock();
private:
	SDL_mutex*		m_Mutex;
};

}
}
}
}

#endif /* SDLMUTEX_H_ */
