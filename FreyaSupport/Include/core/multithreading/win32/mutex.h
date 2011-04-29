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
#include <time.h>

namespace core
{
	namespace multithreading
	{
		inline mutex::mutex()
		{
			mutex_rep::m_locked = false;
			InitializeCriticalSection(&(mutex_rep::m_critical_section));
		}

		inline mutex::~mutex()
		{
			DeleteCriticalSection(&(mutex_rep::m_critical_section));
		}

		inline bool mutex::lock()
		{
			EnterCriticalSection(&(mutex_rep::m_critical_section));
			return mutex_rep::twice_lock_protect();
		}

		inline bool mutex::lock(const unsigned timeout)
		{
			static const long ms_per_sec = 1000;
			const clock_t start = clock();
			//if the thread had locked this mutex before, first try will be successful.
			while(TryEnterCriticalSection(&(mutex_rep::m_critical_section)) == FALSE)
			{
				unsigned tries = 1;
				signed long time_elapsed = ((clock() - start) * ms_per_sec) / CLOCKS_PER_SEC;
				if(time_elapsed > static_cast<signed long>(timeout) )
					return false;//timeout
				thread_self::sleep(tries++);//increase sleep time lineary
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
			mutex_rep::m_locked = false;
			LeaveCriticalSection(&(mutex_rep::m_critical_section));
		}

	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_WIN32_MUTEX_H_