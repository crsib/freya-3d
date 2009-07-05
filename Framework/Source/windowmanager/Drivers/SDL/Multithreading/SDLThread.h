/*
 * SDLThread.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef SDLTHREAD_H_
#define SDLTHREAD_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/Multithreading/Thread.h"
struct SDL_Thread;

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
class SDLThread: public Thread
{
	friend class windowmanager::drivers::sdl::SDLManagerDriver;
protected:
	SDLThread(int (*fn)(void* v),void* p);
	virtual ~SDLThread();
public:
	virtual unsigned 	getThreadID();
	virtual unsigned 	waitThread();
	virtual void		killThread();
private:
	SDL_Thread*			m_Thread;
};

}
}
}
}
#endif /* SDLTHREAD_H_ */
