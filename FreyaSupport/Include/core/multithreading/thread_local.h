/* File   : core/multithreading/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_LOCAL
#define FREYA_THREAD_LOCAL

#include "thread_local-interface.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "details/plat-win-tls.h"
#elif defined(PLATFORM_POSIX_THREADS)
#endif

#endif//FREYA_THREAD_LOCAL