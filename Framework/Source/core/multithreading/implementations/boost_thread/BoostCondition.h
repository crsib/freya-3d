/*
 * BoostCondition.h
 *
 *  Created on: 06.07.2009
 *      Author: vedenko
 */

#ifndef BOOSTCONDITION_H_
#define BOOSTCONDITION_H_

/*
 *
 */
#include "core/multithreading/Condition.h"
#include "core/multithreading/implementations/boost_thread/BoostMutex.h"

#include <boost/thread/condition_variable.hpp>

namespace core
{

namespace multithreading
{

namespace implementations
{

namespace boost_thread
{
class ImplementationFactory;
class BoostCondition: public core::multithreading::Condition
{
private:
	friend class ImplementationFactory;
	BoostCondition() : m_Cond(new boost::condition_variable_any())
	{

	}
	virtual ~BoostCondition()
	{
		m_Cond->notify_all();
		delete m_Cond;
	}

	boost::condition_variable_any*	m_Cond;
public:
	virtual void wait(core::multithreading::Mutex* mut)
	{
		//boost::unique_lock<boost::mutex> lock(*(static_cast<BoostMutex*>(mut)->m_Mutex),boost::adopt_lock);
		static_cast<BoostMutex*>(mut)->m_Locked = 0;
		//m_Cond->wait(lock);
		m_Cond->wait(*(static_cast<BoostMutex*>(mut)->m_Mutex));
		static_cast<BoostMutex*>(mut)->m_Locked = 1;
	}

	virtual void signal()
	{
		m_Cond->notify_one();
	}

	virtual void broadcast()
	{
		m_Cond->notify_all();
	}
};

}

}

}

}

#endif /* BOOSTCONDITION_H_ */
