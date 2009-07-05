/*
 * Semaphore.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef SEMAPHORE__H_
#define SEMAPHORE__H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace windowmanager
{
namespace multithreading
{
class Semaphore: virtual public ::EngineSubsystem
{
	friend class WindowManagerDriver;
protected:
	Semaphore(unsigned initialValue)
	{
	}
	virtual ~Semaphore()
	{

	}
public:
	virtual void 		wait() = 0;
	virtual void 		post() = 0;
	virtual unsigned	value()= 0;
};

}
}

#endif /* SEMAPHORE_H_ */
