/*
 * SDLCondition.h
 *
 *  Created on: 29.08.2008
 *      Author: vedenko
 */

#ifndef SDLCONDITION_H_
#define SDLCONDITION_H_

/*
 *
 */
#include "windowmanager/DriverSubsystems/Multithreading/Condition.h"

struct SDL_cond;

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
class SDLCondition: public Condition
{
	friend class windowmanager::drivers::sdl::SDLManagerDriver;
protected:
	SDLCondition();
	virtual ~SDLCondition();
public:
	virtual void signal();
	virtual void broadcast();
	virtual void wait(const Mutex* mut);
private:
	SDL_cond* 	m_Condition;
};

}
}
}
}
#endif /* SDLCONDITION_H_ */
