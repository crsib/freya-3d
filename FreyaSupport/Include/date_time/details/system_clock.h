/* File   : date_time/details/system_clock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_DATE_TIME_DETAILS_SYSTEM_CLOCK_H_
#define FREYA_DATE_TIME_DETAILS_SYSTEM_CLOCK_H_

#include "FreyaSupportInternal.h"
#include "date_time/details/platform.h"

#include "date_time/TimeUnit.h"

namespace date_time
{
	/// \brief This class provides funcitons to work with system clocks.
	/** */
	class FREYA_SUPPORT_EXPORT system_clock : private details::clock_rep
	{
	public:
		typedef details::clock_rep::clock_diff_t duration_t; ///< Integral type used to represent an time intervals.

		static const date_time::TimeUnit Resolution = date_time::Milliseconds; ///< This constant should be interpreted as 'resolution of time interval returned by the clock substraction'.
		static const unsigned Precision = 1; ///< This constant should be interpreted as 'precision of time interval returned by the clock substraction'.

		/// Default constructor. Initializes instance with current system clock value.
		inline system_clock();
		/// Copy constructor.
		inline system_clock(const system_clock& other);

		/// Assignment operator.
		inline system_clock& operator=(const system_clock& other);
		
		/// Substraction operator.
		/** \return Integral value.*/
		inline duration_t operator-(const system_clock& other) const;

		/// Updates with current time.
		inline system_clock& update();

		///
		inline static system_clock current();
	};
}//namespace date_time

#endif//FREYA_DATE_TIME_DETAILS_SYSTEM_CLOCK_H_