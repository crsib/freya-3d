/* File   : core/multithreading/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_MUTEX_H_
#define FREYA_MULTITHREADING_MUTEX_H_

#include "core/multithreading/details/mutex.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "core/multithreading/win32/mutex.h"
#elif defined(PLATFORM_POSIX_THREADS)
        #include "core/multithreading/posix/mutex.h"
#endif

#endif//FREYA_MULTITHREADING_MUTEX_H_