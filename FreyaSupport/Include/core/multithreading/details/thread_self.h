/* File   : core/multithreading/details/thread_self.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_DETAILS_THREAD_SELF_H_
#define FREYA_MULTITHREADING_DETAILS_THREAD_SELF_H_

#include "date_time/details/system_clock.h" //interface only

namespace core
{
	namespace multithreading
	{
		/// \brief This namespace contains functions to control the thread of execution.
		namespace thread_self
		{
			/// \brief Yields CPU time to another thread.
			/** \return Boolean value. True on success. False does not mean an error,
			  * but execution of the calling thread will be continued. */
			inline bool yield();

			/// \brief Makes thread of execution to sleep for a specified time.
			/** \param ms Time to sleep in milliseconds. */
			inline void sleep(const date_time::system_clock::duration_t ms);

			/// \brief Retrieve Freya specific thread id.
			/** Returned value lies in [0..n] interval, where 'n' is a total thread
			  * number that had been created. Zero value corresponds to the main
			  * thread. NB: The id value does not reflect the order in which thread
			  * was created, but uniqueness is guaranteed.
			  * \return Unsigned integral value. */
			inline unsigned get_freya_id();
		}//namespace thread_self
	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_DETAILS_THREAD_SELF_H_