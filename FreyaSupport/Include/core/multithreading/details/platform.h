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
	#error core::multithreading library for posix platform is not implemented yet.
	#include <pthread.h>
#endif

#include "FreyaSupportInternal.h"

#if defined(PLATFORM_WIN_THREADS)
namespace core
{
	namespace multithreading
	{
		namespace details
		{
			///\cond
			struct FREYA_SUPPORT_EXPORT thread_rep
			{
				__forceinline thread_rep(HANDLE handle = NULL, DWORD id = 0)
					: m_handle(handle), m_id(id)
				{
				}
				HANDLE	m_handle;
				DWORD	m_id;
			};

			// There is no need to export this structure, because of thread_local is a template class
			struct thread_local_rep
			{
				typedef LPVOID tls_data_t;//type of tls cell
				typedef DWORD  tls_index_t;//type of index of tls cell

				__forceinline thread_local_rep(DWORD index)
					: m_tls_index(index)
				{
				}

				tls_index_t m_tls_index;
			};
			
			struct FREYA_SUPPORT_EXPORT mutex_rep
			{
				CRITICAL_SECTION	m_critical_section;
				volatile bool		m_locked;// used to prevent recursive lock

				/* Important: use this function AFTER the thread had owned mutex.
				 * It will return the underlying CRITICAL_SECTION into "normal, 
				 * first time locked" state, to provide behaviour more like 
				 * non-recursive mutex. */
				__forceinline bool twice_lock_protect()
				{
					if(m_locked == false)// locked by the current thread first time
						m_locked = true;
					else// mutex is locked twice by the current thread
					{
						//this does not unlock the mutex. thread still own it.
						LeaveCriticalSection(&(mutex_rep::m_critical_section));
						return false;
					}
					return true;
				}
			};

			struct FREYA_SUPPORT_EXPORT condition_variable_rep
			{
				CONDITION_VARIABLE m_cond_var;
			};
			///\endcond
		}//namespace details
	}//namespace multithreading
}//namespace core
#elif defined(PLATFORM_POSIX_THREADS)
#endif

#endif//FREYA_THREADS_PLATFORM_H_