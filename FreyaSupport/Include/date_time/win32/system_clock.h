/* File   : core/date_time/win32/system_clock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_WIN32_SYSTEM_CLOCK_H_
#define FREYA_DATE_TIME_WIN32_SYSTEM_CLOCK_H_

#include "date_time/details/platform.h"
#include "date_time/details/system_clock.h"

namespace date_time
{
	inline system_clock::system_clock()
	{
		clock_rep::m_value = timeGetTime();
	}

	inline system_clock::system_clock(const system_clock& other)
	{
		clock_rep::m_value = other.m_value;
	}

	inline system_clock& system_clock::operator=(const system_clock& other)
	{
		clock_rep::m_value = other.m_value;
		return *this;
	}

	inline system_clock::duration_t system_clock::operator-(const system_clock& other) const
	{
		duration_t diff = clock_rep::m_value - other.m_value;
		return diff;
	}

	inline system_clock& system_clock::update()
	{
		clock_rep::m_value = timeGetTime();
		return *this;
	}

	inline system_clock system_clock::current()
	{
		return system_clock();
	}
		
}//namespace date_time

#endif//FREYA_DATE_TIME_WIN32_SYSTEM_CLOCK_H_