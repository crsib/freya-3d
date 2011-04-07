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

#include "plat-win-thread-data.h"
#include "../thread.h"

//:TODO: some checks looks unnecessary.

namespace core {
	namespace multithreading {
		
		//Platform thread routine. See WinAPI documentation for details.
        template<typename ObjT, void (ObjT::*Function)(void)>
		DWORD WINAPI platform_win_thread_routine(LPVOID arg) {
			ObjT* object = reinterpret_cast<ObjT*>(arg);
			(object->*Function)();
            delete object;
			return 0;
		}

		thread::thread() : m_platform_data(NULL), m_rights(NoAccessRights) { }

		thread::thread(const thread& other) : m_rights(other.m_rights) { 
			if(other.get_access_rights() & PseudoThread) {
				m_platform_data = new details::thread_data;
				m_platform_data->m_handle = other.m_platform_data->m_handle;
				m_platform_data->m_id = other.m_platform_data->m_id;
			} else
				m_platform_data = other.m_platform_data;
		}

		thread::~thread() {
			if(m_rights & PseudoThread)
				delete m_platform_data;
		}

		thread& thread::operator=(const thread& other) {
			m_platform_data = other.m_platform_data;
			m_rights		= other.m_rights;
			return *this;
		}

		bool thread::operator ==(const thread& other) const {
			bool eq = (this->get_platform_id() == other.get_platform_id());
			return eq;
		}

		bool thread::operator !=(const thread& other) const {
			bool neq = (this->get_platform_id() != other.get_platform_id());
			return neq;
		}

		bool thread::is_valid(void) const {
			return (m_platform_data != NULL) && (m_platform_data->m_handle != NULL);
		}

		unsigned int thread::get_platform_id(void) const {
			return static_cast<unsigned int>(m_platform_data->m_id);
		}

		void thread::yield(void) {
			SwitchToThread();
		}

		void thread::sleep(const unsigned ms) {
			Sleep(static_cast<DWORD>(ms));
		}

		thread thread::self(void) {
			thread self_thread;
			self_thread.m_platform_data = new details::thread_data;
			self_thread.m_platform_data->m_handle = NULL;
			self_thread.m_platform_data->m_id = GetCurrentThreadId();
			self_thread.m_rights = PseudoThread; //Thread is not allowed to make self-join or self-kill.
			return self_thread;
		}

        template<typename ObjT, void (ObjT::*Function)(void)>
		thread thread::create(ObjT& object) {
			thread new_thread;
			//Save in stack first...
			details::thread_data pdata = {NULL, 0};
			pdata.m_handle = 
                    CreateThread(NULL, 0, static_cast<LPTHREAD_START_ROUTINE>(&platform_win_thread_routine<ObjT, Function>), &object, 0, &(pdata.m_id));
			if(pdata.m_handle) {
				//then copy to thread object...
				new_thread.m_platform_data = new details::thread_data;
				new_thread.m_platform_data->m_handle = pdata.m_handle;
				new_thread.m_platform_data->m_id = pdata.m_id;
				new_thread.m_rights = AllAccessRights;
			}
			return new_thread;
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_PLATFORM_WIN_THREAD_H_
