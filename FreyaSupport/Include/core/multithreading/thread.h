/* File   : core/multithreading/thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_H_
#define FREYA_THREAD_H_

//Exactly one symbol must be defined.
#if !(defined(PLATFORM_WIN_THREADS) ^ defined(PLATFORM_POSIX_THREADS))
	#error 'Thread platform section mismatch'
#endif//PLATFORM_WIN_THREADS ^ PLATFORM_POSIX_THREADS

#include "thread-interface.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "details/plat-win-thread.h"
#else
	#include "details/plat-posix-thread.h"
#endif

#endif//FREYA_THREAD_H_
