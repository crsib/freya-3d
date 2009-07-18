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

#define SYNCHRONIZE(mutex) {\
							core::multithreading::Lock __lock__(mutex)

#define ENDSYNC					}

namespace core
{

namespace multithreading
{
//! This class provides save synchronization concept.
/*!
 * This class provides save synchronization concept. It is recomended to use it indirectly using SYNCHRONIZE/ENDSYNC macros pair
 * Please note, that this pair creates a view scope,so be careful with defining local variables inside it
 */
class Lock: public virtual EngineSubsystem
{
	Mutex* 	m_Mutex;
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
};

}

}

#endif /* LOCK_H_ */
