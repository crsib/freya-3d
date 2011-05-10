/* File   : core/multithreading/thread_self.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_THREAD_SELF_H_
#define FREYA_MULTITHREADING_THREAD_SELF_H_

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/thread_self.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "core/multithreading/win32/thread_self.h"
#elif defined(PLATFORM_POSIX_THREADS)
        #include "core/multithreading/posix/thread_self.h"
#endif

#endif//FREYA_MULTITHREADING_THREAD_SELF_H_