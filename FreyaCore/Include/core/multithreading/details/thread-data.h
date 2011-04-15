/* File	  : multithreading/details/thread-data.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_DATA_H_
#define FREYA_THREAD_DATA_H_

#if defined(PLATFORM_WIN_THREADS)
	#include "plat-win-thread-data.h"
#elif defined(PLATFORM_POSIX_THREADS)
	#include "plat-posix-thread-data.h"
#endif//PLATFORM_WIN_THREADS

#endif//FREYA_THREAD_DATA_H_