/*
 * BoostThread.cpp
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#include "BoostThread.h"


namespace core
{

namespace multithreading
{

namespace implementations
{

namespace boost_thread
{

BoostThread::~BoostThread()
{
	delete m_Thread;
}

const ThreadID&  	BoostThread::threadID() const
{
	return *m_ID;
}
void	  	BoostThread::wait()
{
	//std::cout << "BoostThread::wait()" << std::endl;
	if(m_Thread->joinable())
	{
	//	std::cout << "m_Thread->join()" << std::endl;
		if(false == m_Thread->timed_join(boost::posix_time::millisec(500)));
		{
			std::cout << "Boost thread refused to join, killing it" << std::endl;
			m_Thread->interrupt();
			m_Thread->detach();
		}
	}
	//std::cout << "Thread finished " << std::endl; 
}

bool	 	BoostThread::timedWait(size_t ms)
{
	return m_Thread->timed_join(boost::posix_time::millisec(ms));
}

}

}

}

}
