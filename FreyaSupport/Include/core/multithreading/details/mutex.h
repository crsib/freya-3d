/* File	  : core/multithreading/details/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_DETAILS_MUTEX_H_
#define FREYA_MULTITHREADING_DETAILS_MUTEX_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"

#include "date_time/details/system_clock.h" // interface only

namespace core
{
	namespace multithreading
	{
		/// \brief This class provides basic operations on mutex objects.
		/** Mutex instances are not copiable. Mutex can not be locked
		 * recursievly by the owner thread. Class have "Lockable" compatible interface. */
		class FREYA_SUPPORT_EXPORT mutex : private details::mutex_rep
		{
		public:
			typedef mutex lockable_type_t;

			/// \brief Creates mutex object.
			inline mutex();

			/// \brief Destroy mutex object.
			inline ~mutex();

			/// \brief Locks the mutex.
			/** If the mutex object was locked by some other thread before, execution
			 * of calling thread will be stoped until mutex object will be released.
			 */
			inline void lock();

			///brief Locks the mutex (timed version).
			/** If the mutex object was locked by some other thread before, execution
			 * of calling thread will be stoped until mutex object will be released or
			 * waiting time have been elapsed.
			 * \param timeout Time to wait in milliseconds.
			 * \return Boolean value. Positive if mutex was locked, negative if waiting
			 * time have been elapsed, or error was occurred.
			 */
			inline bool lock(const date_time::system_clock::duration_t timeout);
			
			/// \brief Tries to lock the mutex object.
			/** If the mutex object was locked by some other thread before, calling
			 * thread will continue it's execution immediately.
			 * \return Boolead value. True if mutex was locked.
			 */
			inline bool try_lock();
			
			/// \brief Release the mutex object.
			/** Operation complimentary to lock. Mutex can be released only by the
			 * thread owned it before.
			 */
			inline void release();

		private:
			// Copy constructor is forbidden.
			mutex(const mutex&);
			// Assignment operator if forbidden.
			mutex& operator=(const mutex&);
		};

	}//namespace multithreading
}//namespace core


#endif//FREYA_MULTITHREADING_DETAILS_MUTEX_H_
