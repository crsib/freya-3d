/* File	  : freya/core/multithreading/details/thread-details.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 *
 * This file do some checks and provides appropriate thread class implementation.
 * WARNING : Do not use it directly from your code.
 */

#ifndef FREYA_THREAD_DETAILS_H_
#define FREYA_THREAD_DETAILS_H_

#if !defined(FREYA_THREAD_PLATFORM_AUTODETECT_DISABLE)
	#include "autodetect.h"
#endif

//Exactly one symbol must be defined.
#if !(defined(PLATFORM_WIN_THREADS) ^ defined(PLATFORM_POSIX_THREADS))
	#error 'Thread platform section mismatch'
#endif//PLATFORM_WIN_THREADS ^ PLATFORM_POSIX_THREADS

#if defined(PLATFORM_WIN_THREADS)
	#include "plat-win-thread.h"
#elif defined(PLATFOR_POSIX_THREADS)
	#include "plat-posix-thread.h"
#endif//PLATFORM_WIN_THREADS

#endif//FREYA_THREAD_DETAILS_H_
