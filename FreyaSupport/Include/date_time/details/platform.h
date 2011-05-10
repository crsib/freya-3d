/* File   : date_time/details/platform.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_DETAILS_PLATFORM_H_
#define FREYA_DATE_TIME_DETAILS_PLATFORM_H_

#include "FreyaSupportInternal.h"

#if defined(_WIN32) && defined(_MSC_VER)
#include <Windows.h>

namespace date_time
{
	/// \cond
	namespace details
	{
		struct FREYA_SUPPORT_EXPORT clock_rep
		{
			typedef DWORD clock_diff_t;
			DWORD m_value;
		};

	}//namespace details
	/// \endcond
}//namespace date_time
#elif defined(__unix__) || defined (__unix) || defined (__MINGW32__) || defined(__linux__) || defined(__linux)
#include <time.h>
#include <sys/time.h>

namespace date_time
{
    /// \cond
    namespace details
    {

        struct FREYA_SUPPORT_EXPORT clock_rep
        {
            typedef clock_t clock_diff_t;
//#if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
//        #define FREYA_DATE_TIME_HAVE_HIRES_CLOCK
//            timespec m_time_data;
//#else //fallback
            timeval m_time_data;
//#endif
        };
    }//namespace details
    /// \endcond

}//namespace date_time
#endif

#endif//FREYA_DATE_TIME_DETAILS_PLATFORM_H_
