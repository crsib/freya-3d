/* File	  : freya/core/multithreading/details/plat-win-thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 *
 * This file contains thread implementation for Win platform.
 * WARNING : Do not use it directly from your code.
 */

#ifndef FREYA_PLATFORM_WIN_THREAD_H_
#define FREYA_PLATFORM_WIN_THREAD_H_

#include <atomic/atomic.h>
#include "core/multithreading/thread-interface.h"

namespace core {
	namespace multithreading {
		
		namespace details
		{
			__declspec( dllimport ) atomic::atomic<unsigned> __process_thread_counter;
		}

		namespace thread_self
		{
			__declspec( dllimport ) extern core::multithreading::thread_self::local_variable user_id;
		}

		//Platform thread routine. See WinAPI documentation for details.
        template<typename ObjT, void (ObjT::*Function)(void)>
		DWORD WINAPI platform_win_thread_routine(LPVOID arg) {
			thread_self::user_id = details::__process_thread_counter++;
			ObjT* object = reinterpret_cast<ObjT*>(arg);
			(object->*Function)();
			return 0;
		}

		namespace thread_self
		{
			inline unsigned get_platform_id()
			{
				return static_cast<unsigned>( GetCurrentThreadId() );
			}

			inline void yield()
			{
				SwitchToThread();
			}

			inline void sleep(const unsigned ms)
			{
				Sleep( static_cast<DWORD>(ms) );
			}
		}//namespace thread_self

		thread::thread( )
		{
			m_platform_data.m_handle	= NULL;
			m_platform_data.m_id		= 0;
		}

		thread::~thread()
		{
			kill();
		}

		template<typename T, void (T::*Func)(void)>
		inline thread* thread::create(T& runable)
		{
			details::thread_data pdata = {NULL, 0};
			pdata.m_handle = 
				CreateThread(NULL, 0, static_cast<LPTHREAD_START_ROUTINE>(&platform_win_thread_routine<T, Func>), &runable, 0, &(pdata.m_id));
			if(pdata.m_handle)
			{
				thread* r = new thread;
				r->m_platform_data.m_handle = pdata.m_handle;
				r->m_platform_data.m_id = pdata.m_id;
				return r;
			}
			return NULL;
		}

		bool thread::is_active( ) const
		{
			return (m_platform_data.m_handle != NULL);
		}

		unsigned thread::get_platform_id(void) const
		{
			return static_cast<unsigned>(m_platform_data.m_id);
		}

		bool thread::join( )
		{
			bool signaled = static_cast<bool>( !WaitForSingleObject(m_platform_data.m_handle, INFINITE) );
			if(signaled)
				m_platform_data.m_handle = NULL;
			return signaled;
		}

		bool thread::join(const unsigned ms)
		{
			bool signaled = static_cast<bool>( !WaitForSingleObject(m_platform_data.m_handle, static_cast<DWORD>(ms)) );
			if(signaled)
				m_platform_data.m_handle = NULL;
			return signaled;
		}

		bool thread::kill()
		{
			bool terminated = (TerminateThread(m_platform_data.m_handle, -1) != 0);
			if(terminated)
				m_platform_data.m_handle = NULL;
			return terminated;
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_PLATFORM_WIN_THREAD_H_
