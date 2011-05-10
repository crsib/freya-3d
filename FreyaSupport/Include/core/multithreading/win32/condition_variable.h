/* File   : core/multithreading/win32/condition_variable.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_WIN32_CONDITION_VARIABLE_H_
#define FREYA_MULTITHREADING_WIN32_CONDITION_VARIABLE_H_

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/condition_variable.h"
#include "date_time/details/system_clock.h"

namespace core
{
	namespace multithreading
	{
		class mutex;

		inline condition_variable::condition_variable()
		{
			InitializeConditionVariable(&(condition_variable_rep::m_cond_var));
		}

		inline condition_variable::~condition_variable()
		{
		}

		inline void condition_variable::wait(mutex* sync)
		{
			PCRITICAL_SECTION cs = &(reinterpret_cast<details::mutex_rep*>(sync)->m_critical_section);
			SleepConditionVariableCS(&(condition_variable_rep::m_cond_var), cs, INFINITE);
		}

		inline bool condition_variable::wait(mutex* sync, const date_time::system_clock::duration_t timeout)
		{
			PCRITICAL_SECTION cs = &(reinterpret_cast<details::mutex_rep*>(sync)->m_critical_section);
			return (SleepConditionVariableCS(&(condition_variable_rep::m_cond_var), cs, static_cast<DWORD>(timeout)) != 0);
		}

		inline void condition_variable::broadcast()
		{
			WakeAllConditionVariable(&(condition_variable_rep::m_cond_var));
		}

		inline void condition_variable::signal()
		{
			WakeConditionVariable(&(condition_variable_rep::m_cond_var));
		}
	
	}
}

#endif//FREYA_MULTITHREADING_WIN32_CONDITION_VARIABLE_H_