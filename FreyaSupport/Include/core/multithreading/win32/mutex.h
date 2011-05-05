/* File   : core/multithreading/win32/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_WIN32_MUTEX_H_
#define FREYA_MULTITHREADING_WIN32_MUTEX_H_

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/mutex.h"

#include "core/multithreading/thread_self.h"
#include "date_time/system_clock.h"

namespace core
{
	namespace multithreading
	{
		inline mutex::mutex()
		{
			InitializeCriticalSection(&(mutex_rep::m_critical_section));
		}

		inline mutex::~mutex()
		{
			DeleteCriticalSection(&(mutex_rep::m_critical_section));
		}

		inline void mutex::lock()
		{
			EnterCriticalSection(&(mutex_rep::m_critical_section));
			mutex_rep::twice_lock_protect();
		}

		inline bool mutex::lock(const date_time::system_clock::duration_t timeout)
		{
			//if the thread had locked this mutex before, first try will be successful.
			while(TryEnterCriticalSection(&(mutex_rep::m_critical_section)) == FALSE)
			{
				date_time::system_clock start;
				if((date_time::system_clock::current() - start) <= timeout)
					PAUSE;
				else
					return false;
			}
			return mutex_rep::twice_lock_protect();
		}

		inline bool mutex::try_lock()
		{
			if(TryEnterCriticalSection(&(mutex_rep::m_critical_section)) == TRUE)
				return mutex_rep::twice_lock_protect();
			return false;
		}

		inline void mutex::release()
		{
			LeaveCriticalSection(&(mutex_rep::m_critical_section));
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_WIN32_MUTEX_H_