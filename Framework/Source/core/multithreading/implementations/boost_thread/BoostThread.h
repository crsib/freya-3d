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

inline
BoostThread::~BoostThread()
{
	delete m_Thread;
}
inline
const ThreadID&  	BoostThread::threadID() const
{
	return *m_ID;
}
inline
void	  	BoostThread::wait()
{
	//std::cout << "BoostThread::wait()" << std::endl;
	if(m_Thread->joinable())
	{
	//	std::cout << "m_Thread->join()" << std::endl;
		if(false == m_Thread->timed_join(boost::posix_time::millisec(500)))
		{
			std::cout << "Boost thread refused to join, killing it" << std::endl;
			m_Thread->interrupt();
			m_Thread->detach();
		}
	}
	//std::cout << "Thread finished " << std::endl;
}
inline
bool	 	BoostThread::timedWait(size_t ms)
{
	return m_Thread->timed_join(boost::posix_time::millisec(ms));
}
}

}

}

}

#endif /* BOOSTTHREAD_H_ */
