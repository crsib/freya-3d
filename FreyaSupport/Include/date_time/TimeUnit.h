/* File   : date_time/TimeUnit.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_TIME_UNIT_H_
#define FREYA_DATE_TIME_TIME_UNIT_H_

/// This namespace contains tools for work with time.
namespace date_time
{
	/// Enumeration of time units.
	enum TimeUnit
	{
		Microseconds,
		Milliseconds,
		Seconds,
		Minutes,
		Hours,
		Days
	};

}//namespace date_time

#endif//FREYA_DATE_TIME_TIME_UNIT_H_