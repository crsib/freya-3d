/*
 * BoostThreadBlocks.cpp
 *
 *  Created on: 06.07.2009
 *      Author: vedenko
 */

#ifdef	_MSC_VER
#include <intrin.h>
extern "C"
{
	long _InterlockedCompareExchange (long volatile *, long, long);
	long __cdecl _InterlockedIncrement(long volatile *);
	long __cdecl _InterlockedDecrement(long volatile *);
}
#endif

#include "core/multithreading/ThreadBlocks.h"
#include "config.h"


#ifdef USE_BOOST_THREADS
#include <boost/thread/thread.hpp>
#include "BoostThreadID.h"
#include <map>


#ifdef __SSE__

#	include <xmmintrin.h>

#endif

namespace core
{
namespace multithreading
{

namespace implementations
{

namespace boost_thread
{
extern ThreadID*	MainThreadID;
ThreadID*	MainThreadID = NULL;
extern std::map<boost::thread::id,BoostThreadID*> ThreadMap;
std::map<boost::thread::id,BoostThreadID*> ThreadMap;
}
}

void	yield()
{
	boost::this_thread::yield();
}

unsigned	numHardwareThreads()
{
	return boost::thread::hardware_concurrency();
}

const ThreadID&	getCurrentThreadID()
{
	boost::thread::id tid = boost::this_thread::get_id();
	if(implementations::boost_thread::ThreadMap[tid] == NULL)
		implementations::boost_thread::ThreadMap[tid] = new core::multithreading::implementations::boost_thread::BoostThreadID(tid);
	return *(implementations::boost_thread::ThreadMap[tid]);
}

const ThreadID&	getMainThreadID()
{
	return *core::multithreading::implementations::boost_thread::MainThreadID;
}

void		pause()
{
#ifdef __SSE__
	_mm_pause();
#else
#	ifdef __GNUC__
#		if defined(__i386) || defined(__amd64)
			__asm__ ("PAUSE\n\t");
#		else

#		endif
#	else
#		ifdef _MSC_VER
			__asm {REP NOP}
#		else

#		endif
#	endif
#endif
}

}
}
#endif
