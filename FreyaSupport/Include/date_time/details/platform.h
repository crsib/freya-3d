/* File   : date_time/details/platform.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_DETAILS_PLATFORM_H_
#define FREYA_DATE_TIME_DETAILS_PLATFORM_H_

#include "FreyaSupportInternal.h"

#if defined(_WIN32)

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

#endif//win32

#endif//FREYA_DATE_TIME_DETAILS_PLATFORM_H_
