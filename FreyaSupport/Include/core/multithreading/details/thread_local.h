/* File	  : core/multithreading/details/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_LOCAL_DETAILS_H_
#define FREYA_THREAD_LOCAL_DETAILS_H_

#if defined(PLATFORM_WIN_THREADS)
	#include "../win32/thread_local.h"
#elif defined(PLATFORM_POSIX_THREADS)
#endif

#endif//_THREAD_LOCAL_DETAILS_H_