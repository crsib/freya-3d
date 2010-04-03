/*
 * ThreadBlocks.h
 *
 *  Created on: 05.07.2009
 *      Author: vedenko
 */

#ifndef THREADBLOCKS_H_
#define THREADBLOCKS_H_

#include <cstdlib>
#include "core/multithreading/ThreadID.h"

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
const ThreadID&	getCurrentThreadID();

//! Get the main thread ID
/*!
 * Retrieves the ID of the main thread of the application
 * @return the ID of the main thread. Data might be unavailable without core::EngineCore created
 */
const ThreadID&	getMainThreadID();
//! Pause the spin-wait loop
/*!
 *  Pauses the spin-wait loop for a short amount of time, reducing the cpu usage by a thread to improve the performance of other threads
 */
void		pause();

#ifdef _MSC_VER
#include <windows.h>
#endif

#ifdef _MSC_VER
#	define test_and_set InterlockedBitTestAndSet
#else
inline long SyncInterlockedExchange(volatile long *Dest, long Val)
{
#if defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
	return  __sync_lock_test_and_set(Dest, Val);
#else
	register int result;
	__asm__ __volatile__("lock; xchg %0,%1"
			: "=r" (result), "=m" (*Dest)
			  : "0" (Val), "m" (*Dest)
			    : "memory");
	return result;
#endif
}
#ifndef test_and_set
#	define test_and_set core::multithreading::SyncInterlockedExchange
#endif
#endif

}
}
#endif /* THREADBLOCKS_H_ */
