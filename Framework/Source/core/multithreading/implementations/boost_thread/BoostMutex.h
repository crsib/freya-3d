/*
 * BoostMutex.h
 *
 *  Created on: 06.07.2009
 *      Author: vedenko
 */

#ifndef BOOSTMUTEX_H_
#define BOOSTMUTEX_H_

/*
 *
 */
#include "core/multithreading/Mutex.h"
#include <boost/thread/mutex.hpp>

namespace core
{

namespace multithreading
{
class Mutex;
namespace implementations
{

namespace boost_thread
{
class ImplementationFactory;
class BoostCondition;
class BoostMutex: public core::multithreading::Mutex
{
	friend class ImplementationFactory;
	friend class BoostCondition;
private:
	BoostMutex() : m_Mutex (new boost::mutex()), m_Locked(0){}
	virtual ~BoostMutex()
	{
		if(m_Locked)
			unlock();
		delete m_Mutex;
	}

	boost::mutex*		m_Mutex;
	unsigned			m_Locked;
public:
	virtual void	lock()
	{
		if(m_Locked == 0)
		{
			m_Locked = 1;
			m_Mutex->lock();
		}
	}

	virtual bool    tryLock()
	{
		if(m_Locked == 0)
		{
			m_Locked = m_Mutex->try_lock();
		}
		return m_Locked;
	}

	virtual void    unlock()
	{
		if(m_Locked)
		{
			m_Locked = 0;
			m_Mutex->unlock();
		}
	}
};

}

}

}

}

#endif /* BOOSTMUTEX_H_ */
