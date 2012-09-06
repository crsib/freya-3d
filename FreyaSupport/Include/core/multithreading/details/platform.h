/* File   : core/multithreading/details/platform.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREADS_PLATFORM_H_
#define FREYA_THREADS_PLATFORM_H_

//Exactly one symbol must be defined.
#if defined(MARMALADE_USED) && !defined(PLATFORM_POSIX_TREADS)
#	define PLATFORM_POSIX_THREADS
#endif

#if !(defined(PLATFORM_WIN_THREADS) ^ defined(PLATFORM_POSIX_THREADS))
	#error Thread platform section mismatch: only one symbol should be defined.
#endif

#ifdef PLATFORM_WIN_THREADS
        #include <Windows.h>
#elif defined(PLATFORM_POSIX_THREADS)
	#include <pthread.h>
#endif

#include "FreyaSupportInternal.h"

#if defined(PLATFORM_POSIX_THREADS)
namespace core
{
    namespace multithreading
    {
        namespace details
        {
            ///\cond
            struct FREYA_SUPPORT_EXPORT thread_rep
            {
                pthread_t m_handle;
            };
            
            struct FREYA_SUPPORT_EXPORT mutex_rep
            {
                pthread_mutex_t m_mutex;
            };
            
            struct FREYA_SUPPORT_EXPORT condition_variable_rep
            {
                pthread_cond_t m_var;
            };
            
            struct thread_local_rep
            {
                pthread_key_t m_key;
            };
            
            
            ///\endcond
        }//namespace details
    }//namespace multithreading
}//namespace core

#elif defined(PLATFORM_WIN_THREADS)
namespace core
{
	namespace multithreading
	{
		namespace details
		{
			///\cond
			struct FREYA_SUPPORT_EXPORT thread_rep
			{
				FREYA_SUPPORT_FORCE_INLINE thread_rep(HANDLE handle = NULL, DWORD id = 0)
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

				FREYA_SUPPORT_FORCE_INLINE thread_local_rep(DWORD index)
					: m_tls_index(index)
				{
				}

				tls_index_t m_tls_index;
			};
			
			struct FREYA_SUPPORT_EXPORT mutex_rep
			{
				CRITICAL_SECTION	m_critical_section;

				/* Important: use this function AFTER the thread had owned mutex.
				 * Using this function before lock will lead to UB.
				 * It will return the underlying CRITICAL_SECTION into "normal, 
				 * first time locked" state, to provide behaviour more like 
				 * non-recursive mutex. */
				FREYA_SUPPORT_FORCE_INLINE bool twice_lock_protect()
				{
					if(m_critical_section.RecursionCount == 1)
						return true;
					else// mutex is locked twice by the current thread, or was not locked at all(UB)...
					{
						//this does not unlock the mutex. thread still own it.
						LeaveCriticalSection(&(mutex_rep::m_critical_section));
						return false;
					}
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
#endif//PLATFORM_WIN_THREADS

#endif//FREYA_THREADS_PLATFORM_H_