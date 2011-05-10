/* File   : date_time/posix/system_clock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_POSIX_SYSTEM_CLOCK_H
#define	FREYA_DATE_TIME_POSIX_SYSTEM_CLOCK_H

#include "date_time/details/platform.h"
#include "date_time/details/system_clock.h"

#if 0 && defined(FREYA_DATE_TIME_HAVE_HIRES_CLOCK)
#else// fallback

namespace date_time
{
    
    inline system_clock::system_clock()
    {
        gettimeofday(&(clock_rep::m_time_data), NULL);
    }
    
    inline system_clock::system_clock(const system_clock& other)
    {
        clock_rep::m_time_data.tv_sec = other.m_time_data.tv_sec;
        clock_rep::m_time_data.tv_usec = other.m_time_data.tv_usec;
    }
    
    inline system_clock& system_clock::operator =(const system_clock& other)
    {
        clock_rep::m_time_data.tv_sec = other.m_time_data.tv_sec;
        clock_rep::m_time_data.tv_usec = other.m_time_data.tv_usec;
        return *this;
    }
    
    inline system_clock::duration_t system_clock::operator -(const system_clock& other) const
    {
        //:TODO: clac overflow
        static const long ms_per_sec = 1000;
        static const long us_per_ms = 1000;
        system_clock::duration_t diff = clock_rep::m_time_data.tv_sec * ms_per_sec;
        diff += clock_rep::m_time_data.tv_usec / us_per_ms;
        diff -= (other.m_time_data.tv_sec * ms_per_sec);
        diff -= (other.m_time_data.tv_usec / us_per_ms);
        return diff;
    }
    
    inline system_clock& system_clock::update()
    {
        gettimeofday(&(clock_rep::m_time_data), NULL);
        return *this;
    }
    
    inline system_clock system_clock::current()
    {
        return system_clock();
    }
}

#endif

#endif/*FREYA_DATE_TIME_POSIX_SYSTEM_CLOCK_H*/

