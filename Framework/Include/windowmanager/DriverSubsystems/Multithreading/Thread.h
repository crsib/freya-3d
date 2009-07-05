/*
 * Thread.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef THREAD__H_
#define THREAD__H_

#include "core/EngineSubsystem.h"

namespace windowmanager
{
namespace multithreading
{
class Thread : virtual public ::EngineSubsystem
{
	friend class WindowManagerDriver;
protected:
	Thread(int (*fn)(void* v),void* p)
	{
	}

	virtual ~Thread()
	{

	}
public:
	virtual unsigned 	getThreadID() = 0;
	virtual unsigned 	waitThread()  = 0;
	virtual void		killThread()  = 0;
};

}
}
#endif /* THREAD_H_ */
