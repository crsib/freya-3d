/* File   : date_time/system_clock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_SYSTEM_CLOCK_H_
#define FREYA_DATE_TIME_SYSTEM_CLOCK_H_

#include "date_time/details/system_clock.h"

#if defined(_WIN32)
	#include "date_time/win32/system_clock.h"
#elif (defined(__unix__) || defined(__unix))
	#error ERROR: date_time::system_clock for your platform not implemented yet.
#elif (defined(__APPLE__) && defined(__MACH__))
	#error ERROR: date_time::system_clock for your platform not implemented yet.
#endif

#endif//#ifndef FREYA_DATE_TIME_SYSTEM_CLOCK_H_