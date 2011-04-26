/* File   : core/multithreading/win32/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_PLATFORM_WIN_MUTEX_H_
#define FREYA_PLATFORM_WIN_MUTEX_H_

#include "core/multithreading/details/platform.h"
#include "core/multithreading/mutex.h"

namespace core
{
	namespace multithreading
	{
		inline mutex::mutex()
			: mutex_rep(CreateMutex(NULL, false, NULL))
		{
		}

		inline mutex::~mutex()
		{
			if(mutex_rep::m_mutex_handle != NULL)
			{
				CloseHandle(mutex_rep::m_mutex_handle);
				mutex_rep::m_mutex_handle = NULL;
			}
		}

		inline bool mutex::is_valid() const
		{
			return (mutex_rep::m_mutex_handle != NULL);
		}

		inline bool mutex::lock()
		{
			return (WaitForSingleObject(mutex_rep::m_mutex_handle, INFINITE) == WAIT_OBJECT_0);
		}

		inline bool mutex::lock(const unsigned timeout)
		{
			return (WaitForSingleObject(mutex_rep::m_mutex_handle, static_cast<DWORD>(timeout)) == WAIT_OBJECT_0);
		}

		inline bool mutex::try_lock()
		{
			return (WaitForSingleObject(mutex_rep::m_mutex_handle, 0) == WAIT_OBJECT_0);
		}

		inline bool mutex::release()
		{
			return (ReleaseMutex(mutex_rep::m_mutex_handle) == TRUE);
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_PLATFORM_WIN_MUTEX_H_