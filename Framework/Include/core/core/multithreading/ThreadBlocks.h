/*
 * ThreadBlocks.h
 *
 *  Created on: 05.07.2009
 *      Author: vedenko
 */

#ifndef THREADBLOCKS_H_
#define THREADBLOCKS_H_

#include <cstdlib>

namespace core
{
namespace multithreading
{
//! Yield the the thread manager to change the current thread of execution
/*!
 * This function yields to system specific thread manager, that thread switch should occur.
 * This function helps to reduce CPU usage and improves performance of an application
 */
void	yield();

//! Puts the current thread of execution into the sleep mode
/*!
 * Puts the current thread of execution into the sleep mode, forcing to change threads.
 * This function highly reduces the CPU usage
 * \param ms is an amount of time for thread to sleep in ms
 */
void	sleep(size_t ms);

//! Get the number of hardware-accelerated threads
/*!
 * Gets the number of hardware-accelerated threads, e.g. number of logical cores
 * @return number of logical cores or 0, if information is not provided by host OS
 */
unsigned	numHardwareThreads();

//! Returns the current thread ID
/*!
 * Retrieve the current thread ID
 * @return the ID of a current thread
 */
ThreadID&	getCurrentThreadID();

//! Get the main thread ID
/*!
 * Retrieves the ID of the main thread of the application
 * @return the ID of the main thread. Data might be unavailable without core::EngineCore created
 */
ThreadID&	getMainThreadID();
//! Pause the spin-wait loop
/*!
 *  Pauses the spin-wait loop for a short amount of time, reducing the cpu usage by a thread to improve the performance of other threads
 */
void		pause();
}
}
#endif /* THREADBLOCKS_H_ */
