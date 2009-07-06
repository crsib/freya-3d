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
	m_Thread->join();
}

bool	 	BoostThread::timedWait(size_t ms)
{
	return m_Thread->timed_join(boost::posix_time::millisec(ms));
}

}

}

}

}
