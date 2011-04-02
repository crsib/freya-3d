/* File	  : freya/core/multithreading/details/autodetect.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 *
 * Platform auto detection helper.
 * WARNING : Do not use it directly from your code.
 */

#ifndef FREYA_THREAD_AUTODETECT_H_
#define FREYA_THREAD_AUTODETECT_H_

//:TODO: check cygwin, mingw, msvc, clang

#if defined(linux) || defined(__linux__) || defined(__linux)
	#define PLATFORM_POSIX_THREADS
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
	#define PLATFORM_WIN_THREADS
#endif

#endif//FREYA_THREAD_AUTODETECT_H_
