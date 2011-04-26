/* File   : core/multithreading/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MUTEX_H_
#define FREYA_MUTEX_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"

namespace core
{
	namespace multithreading
	{
		/// \brief This class provides basic operations on mutex objects.
		/** Mutex instances are not copiable. Mutex can not be locked
		 * recursievly by the owner thread. */
		class FREYA_SUPPORT_EXPORT mutex : private details::mutex_rep
		{
		public:
			/// \brief Creates mutex object. Use mutex::is_valid() to check that object was properly created.
			inline mutex();

			/// \brief Destroy mutex object.
			inline ~mutex();

			/// \brief Retrieve state of the object.
			/** Normaly it should always return positive value. 
			  * \return Boolean value. True if object is valid. */
			inline bool is_valid() const;

			/// \brief Locks the mutex.
			/** If the mutex object was locked by some other thread before, execution
			 * of calling thread will be stoped until mutex object will be released.
			 * \return Boolean value. Positive if mutex was locked, negative in case of
			 * error.
			 */
			inline bool lock();

			///brief Locks the mutex (timed version).
			/** If the mutex object was locked by some other thread before, execution
			 * of calling thread will be stoped until mutex object will be released or
			 * waiting time have been elapsed.
			 * \param timeout Time to wait in milliseconds.
			 * \return Boolean value. Positive if mutex was locked, negative in case of
			 * error or timeout elapse.
			 */
			inline bool lock(const unsigned timeout);\
			
			/// \brief Tries to lock the mutex object.
			/** If the mutex object was locked by some other thread before, calling
			 * thread will continue it's execution immediately.
			 * \return Boolead value. True if mutex was locked, false in case of 
			 * error or mutex was locked.
			 */
			inline bool try_lock();
			
			/// \brief Release the mutex object.
			/** Operation complimentary to lock. Mutex can be released only by the
			 * thread owned it before.
			 * \return Boolean value. True on success, false in case of error.
			 */
			inline bool release();

		private:
			// Copy constructor is forbidden.
			mutex(const mutex&);
			// Assignment operator if forbidden.
			mutex& operator=(const mutex&);
		};
	}//namespace multithreading
}//namespace core

#include "core/multithreading/details/mutex.h"

#endif//FREYA_MUTEX_H_