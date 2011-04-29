/* File   : core/multithreading/thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_THREAD_H_
#define FREYA_MULTITHREADING_THREAD_H_

#include "core/multithreading/details/thread.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "core/multithreading/win32/thread.h"
#elif defined(PLATFORM_POSIX_THREADS)
#endif

#endif//FREYA_MULTITHREADING_THREAD_H_
