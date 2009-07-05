/*
 * SDLSemaphore.h
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#ifndef SDLSEMAPHORE_H_
#define SDLSEMAPHORE_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/Multithreading/Semaphore.h"
struct	SDL_semaphore;

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
class SDLSemaphore: public Semaphore
{
	friend class windowmanager::drivers::sdl::SDLManagerDriver;
protected:
	SDLSemaphore(unsigned initial_value);
	virtual ~SDLSemaphore();
public:
	virtual void 		wait();
	virtual void 		post();
	virtual unsigned	value();
private:
	SDL_semaphore*            m_Semaphore;
};

}
}
}
}

#endif /* SDLSEMAPHORE_H_ */
