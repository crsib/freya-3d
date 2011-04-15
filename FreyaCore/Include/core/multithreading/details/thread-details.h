/* File	  : multithreading/details/thread-details.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_DETAILS_H_
#define FREYA_THREAD_DETAILS_H_

#if defined(PLATFORM_WIN_THREADS)
	#include "plat-win-thread.h"
#elif defined(PLATFOR_POSIX_THREADS)
	#include "plat-posix-thread.h"
#endif//PLATFORM_WIN_THREADS

#endif//FREYA_THREAD_DETAILS_H_
