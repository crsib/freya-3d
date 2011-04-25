/* File	  : core/multithreading/win32/thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_PLATFORM_WIN_THREAD_H_
#define FREYA_PLATFORM_WIN_THREAD_H_

#include "atomic/atomic.h"
#include "core/multithreading/thread_local.h"

#include "core/multithreading/details/platform.h"
#include "core/multithreading/thread.h"


namespace core {
	namespace multithreading {
		
		namespace details
		{
			FREYA_SUPPORT_EXPORT extern atomic::atomic<unsigned> __process_thread_counter;
			FREYA_SUPPORT_EXPORT extern core::multithreading::thread_local<unsigned> freya_id;
		}//namespace details

		//Platform thread routine. See WinAPI documentation for details.
        template<typename ObjT, void (ObjT::*Function)(void)>
		DWORD WINAPI platform_win_thread_routine(LPVOID arg) {
			details::freya_id = details::__process_thread_counter++;
			ObjT* object = reinterpret_cast<ObjT*>(arg);
			(object->*Function)();
			return 0;
		}

		namespace thread_self
		{
			inline bool yield()
			{
				return (SwitchToThread() != 0);
			}

			inline void sleep(const unsigned ms)
			{
				Sleep( static_cast<DWORD>(ms) );
			}

			inline unsigned get_freya_id()
			{
				return static_cast<unsigned>(details::freya_id);
			}
		}//namespace thread_self

		inline thread::thread()
			: thread_rep()
		{
		}

		inline thread::~thread()
		{
			kill();
		}

		template<typename T, void (T::*Func)(void)>
		inline thread* thread::create(T& runable)
		{
			details::thread_rep pdata(NULL, 0);
			pdata.m_handle = 
				CreateThread(NULL, 0, static_cast<LPTHREAD_START_ROUTINE>(&platform_win_thread_routine<T, Func>), &runable, 0, &(pdata.m_id));
			if(pdata.m_handle)
			{
				thread* r = new thread;
				r->m_handle = pdata.m_handle;
				r->m_id = pdata.m_id;
				return r;
			}
			return NULL;
		}

		inline bool thread::is_active( ) const
		{
			return (thread_rep::m_handle != NULL);
		}

		inline unsigned thread::get_platform_id(void) const
		{
			return static_cast<unsigned>(thread_rep::m_id);
		}

		inline bool thread::join( )
		{
			bool signaled = (WaitForSingleObject(thread_rep::m_handle, INFINITE) == 0 );
			if(signaled)
			{
				CloseHandle(thread_rep::m_handle);
				thread_rep::m_handle = NULL;
			}
			return signaled;
		}

		inline bool thread::join(const unsigned ms)
		{
			bool signaled = (WaitForSingleObject(thread_rep::m_handle, static_cast<DWORD>(ms)) == 0 );
			if(signaled)
			{
				CloseHandle(thread_rep::m_handle);
				thread_rep::m_handle = NULL;
			}
			return signaled;
		}

		inline bool thread::kill()
		{
			bool terminated = (TerminateThread(thread_rep::m_handle, -1) != 0);
			if(terminated)
			{
				CloseHandle(thread_rep::m_handle);
				thread_rep::m_handle = NULL;
			}
			return terminated;
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_PLATFORM_WIN_THREAD_H_
