/*
 * Thread.h
 *
 *  Created on: 04.06.2009
 *      Author: vedenko
 */

#ifndef THREAD_H_
#define THREAD_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"
namespace core
{

namespace multithreading
{
class ThreadID;
//! Platform independent abstraction of thread of execution
/*!
 * Platform independent abstraction of thread of execution.
 * Released more or less above engine driver model
 */
class Thread: public drivermodel::Driver
{
public:
	//! Always returns "thread"
	virtual EString id() const {return "thread";}

	//! Return the engine specific id of a thread
	/*!
	 * Return the engine specific id of a thread.
	 * \return thread ID
	 */
	virtual ThreadID&  threadID() const = 0;
	//! Waits a thread of execution to be finished
	virtual void	  wait() = 0;
	//! Waits a thread of execution to be finished for a period of time
	/*!
	 * Waits a thread of execution to be finished for a period of time and continues execution
	 * of the caller thread
	 * \return true if the tread has finished, false otherwise
	 */
	virtual bool	  timedWait(size_t ms) = 0;
};

}

}

#endif /* THREAD_H_ */
