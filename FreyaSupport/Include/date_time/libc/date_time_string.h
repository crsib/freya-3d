/* File		: date_time/libc/date_time_string.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef DateTime_libc_date_time_string_h__
#define DateTime_libc_date_time_string_h__

#include "date_time/date_time_string.h"
#include "core/smart_ptr.h"
#include <time.h>
namespace date_time
{
	FREYA_SUPPORT_EXPORT inline core::string	date_time_string(const core::string& fmt)
	{
		core::string	output;

		char* data_ptr = core::memory::alloc<char>(128);

		::time_t raw_time;
		::time(&raw_time);
		if(::strftime(data_ptr,128,fmt.c_str(),::localtime(&raw_time)))
			output += data_ptr;

		core::memory::dealloc(data_ptr);

		return output;
	}
}

#endif // DateTime_libc_date_time_string_h__