/*
 * Lock.h
 *
 *  Created on: Jul 18, 2009
 *      Author: crsib
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "core/EngineSubsystem.h"
#include "Mutex.h"

#define synchronize(mutex) 			for(core::multithreading::Lock _FREYA_TEMP__lock__(mutex);_FREYA_TEMP__lock__.check();)


namespace core
{

namespace multithreading
{
//! This class provides save synchronization concept.
/*!
 * This class provides save synchronization concept. It is recomended to use it indirectly using synchronize macros
 */
class Lock: public virtual EngineSubsystem
{
	Mutex* 		m_Mutex;
	unsigned	m_Locked;
public:
	Lock(Mutex* mutex)
	{
		m_Mutex = mutex;
		m_Mutex->lock();
	}
	virtual ~Lock()
	{
		m_Mutex->unlock();
	}

	//Fake routines.
	//! DO NOT USE IT DIRECTLY
	bool check ()
	{
		m_Locked = !m_Locked;
		return !m_Locked;
	}
};

}

}

#endif /* LOCK_H_ */
