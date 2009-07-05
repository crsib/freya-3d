/*
 * Mutex.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef MUTEX__H_
#define MUTEX__H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace windowmanager
{
namespace multithreading
{

class Mutex: virtual public ::EngineSubsystem
{
	friend class WindowManagerDriver;
protected:
	Mutex()
	{
	}
	virtual ~Mutex()
	{

	}
public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

}
}

#endif /* MUTEX_H_ */
