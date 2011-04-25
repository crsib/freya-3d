/* File   : core/multithreading/details/platform.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREADS_PLATFORM_H_
#define FREYA_THREADS_PLATFORM_H_

//Exactly one symbol must be defined.
#if !(defined(PLATFORM_WIN_THREADS) ^ defined(PLATFORM_POSIX_THREADS))
	#error Thread platform section mismatch: only one symbol should be defined.
#endif

#ifdef PLATFORM_WIN_THREADS
#	include <Windows.h>
#elif defined(PLATFORM_POSIX_THREADS)
#	error core::multithreading library for posix platform is not implemented yet.
#endif

#include "FreyaSupportInternal.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
//-----------------------------------------------------------------------------
#if defined(PLATFORM_WIN_THREADS)

			struct FREYA_SUPPORT_EXPORT thread_rep
			{
				__forceinline thread_rep(HANDLE handle = NULL, DWORD id = 0)
					: m_handle(handle), m_id(id)
				{
				}
				HANDLE	m_handle;
				DWORD	m_id;
			};

			struct thread_local_rep
			{
				typedef LPVOID tls_data_t;

				__forceinline thread_local_rep(DWORD index)
					: m_tls_index(index)
				{
				}

				DWORD m_tls_index;
			};
			
			struct FREYA_SUPPORT_EXPORT mutex_rep
			{
				HANDLE m_mutex_handle;
			};
//-----------------------------------------------------------------------------
#elif defined(PLATFORM_POSIX_THREADS)
#endif
		}//namespace details
	}//namespace multithreading
}//namespace core

#endif//FREYA_THREADS_PLATFORM_H_