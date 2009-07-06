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
	BoostMutex() : m_Mutex (new boost::mutex()){}
	virtual ~BoostMutex()
	{
		unlock();
		delete m_Mutex;
	}

	boost::mutex*		m_Mutex;
public:
	virtual void	lock()
	{
		m_Mutex->lock();
	}

	virtual bool    tryLock()
	{
		return m_Mutex->try_lock();
	}

	virtual void    unlock()
	{
		m_Mutex->unlock();
	}
};

}

}

}

}

#endif /* BOOSTMUTEX_H_ */
