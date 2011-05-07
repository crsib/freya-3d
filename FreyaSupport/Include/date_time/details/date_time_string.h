/* File		: date_time/details/date_time_string.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef DateTime_details_date_time_string_h__
#define DateTime_details_date_time_string_h__

#include "core/string.h"
#include "FreyaSupportInternal.h"
namespace date_time
{
	//! Retrieve current local date time string
	/*!
	 * Create date time string using \a fmt as format. 
	 * fmt string should support at least formats defined <A href="http://cplusplus.com/reference/clibrary/ctime/strftime/">here</A>
	 */
	FREYA_SUPPORT_EXPORT inline core::string	date_time_string(const core::string& fmt);
}

#endif // DateTime_libc_date_time_string_h__