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

//TODO: Debug
#include <iostream>
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
	BoostMutex() : m_Mutex (new boost::mutex()), m_Locked(0)
	{
		std::cout << "Mutex " << this << " is created from " << &core::multithreading::getCurrentThreadID() << std::endl;
	}
	virtual ~BoostMutex()
	{
		std::cout << "Mutex " << this << " is destroying from " << &core::multithreading::getCurrentThreadID() << std::endl;
		/*if(m_Locked)
			unlock();*/
		delete m_Mutex;
	}

	boost::mutex*		m_Mutex;
	ThreadID*			m_Owner;
	unsigned			m_Locked;
public:
	virtual void	lock()
	{
		m_Locked = 1;
		m_Mutex->lock();
		m_Owner = const_cast<core::multithreading::ThreadID*>(&core::multithreading::getCurrentThreadID());
	}

	virtual bool    tryLock()
	{
		m_Locked = m_Mutex->try_lock();

		if(m_Locked)
			m_Owner = const_cast<core::multithreading::ThreadID*>(&core::multithreading::getCurrentThreadID());
		return m_Locked;
	}

	virtual void    unlock()
	{
			m_Mutex->unlock();
		/*if(*m_Owner != core::multithreading::getCurrentThreadID())
			std::cout << "WTF Mutex " << m_Mutex << " is unlocked by " << &core::multithreading::getCurrentThreadID() << " owned by " << m_Owner << std::endl;*/
	}
};

}

}

}

}

#endif /* BOOSTMUTEX_H_ */
