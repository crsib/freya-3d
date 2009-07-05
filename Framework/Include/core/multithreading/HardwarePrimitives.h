/*
 * HardwarePrimitives.h
 *
 *  Created on: 10.05.2009
 *      Author: vedenko
 */

#ifndef _HARDWAREPRIMITIVES_H_
#define _HARDWAREPRIMITIVES_H_

#ifdef __SSE__

#	include <xmmintrin.h>

#	undef PAUSE
#	define PAUSE _mm_pause();

#else
#	ifdef __GNUC__
#		if defined(__i386) || defined(__amd64)
#			define PAUSE	__asm__ ("PAUSE\n\t");
#		else
#			define PAUSE
#		endif
#	else
#		ifdef _MSC_VER
#define PAUSE __asm {REP NOP}
#		else
#			define PAUSE
#		endif
#	endif
#endif

//Yielding
#ifdef _WIN32 //Win 32 scheduler

#	include <windows.h>
#	include <process.h>

#	define YIELD SwitchToThread();


#elif __GNUC__ //Posix scheduler

#	include <pthread.h>
#	include <sched.h>
#	define YIELD    sched_yield();                                                              // we call sched_yield();
#else
#define YIELD
#endif

#endif /* HARDWAREPRIMITIVES_H_ */
