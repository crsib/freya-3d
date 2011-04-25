/* File	  : core/multithreading/details/thread.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_DETAILS_H_
#define FREYA_THREAD_DETAILS_H_

#if defined(PLATFORM_WIN_THREADS)
	#include "../win32/thread.h"
#elif defined(PLATFOR_POSIX_THREADS)
#endif//PLATFORM_WIN_THREADS

#endif//FREYA_THREAD_DETAILS_H_
