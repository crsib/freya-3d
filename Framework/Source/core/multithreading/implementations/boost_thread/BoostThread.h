/*
 * BoostThread.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef BOOSTTHREAD_H_
#define BOOSTTHREAD_H_

/*
 *
 */
#include "core/multithreading/Thread.h"
#include <boost/thread/thread.hpp>
#include "BoostThreadID.h"

namespace core
{

namespace multithreading
{

namespace implementations
{

namespace boost_thread
{
class ImplementationFactory;
class BoostThread: public core::multithreading::Thread
{
	friend class ImplementationFactory;
	template<typename Callable>
	BoostThread(Callable func) :
		m_Thread(new boost::thread(func)),
		m_ID(new BoostThreadID(m_Thread->get_id()))
	{}

	virtual ~BoostThread();
public:
	virtual const ThreadID&  	threadID() const;
	virtual void	  	wait();

	virtual bool	 	timedWait(size_t ms);

private:
	boost::thread*	m_Thread;
	BoostThreadID*  m_ID;
};

}

}

}

}

#endif /* BOOSTTHREAD_H_ */
