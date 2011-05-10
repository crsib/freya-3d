/* File   : core/multithreading/spinlock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_SPINLOCK_H_
#define FREYA_MULTITHREADING_SPINLOCK_H_

#include "FreyaSupportInternal.h"
#include "atomic/atomic.h"
#include "date_time/details/system_clock.h" //interface only
#include "core/multithreading/thread_self.h"

namespace core
{
	namespace multithreading
	{
		/// \breif This class is implemeted to be fast and lightweight mechanism, providing another mutual exclusion lock functionality.
		/** Class have "Lockable" compatible interface. */
		class FREYA_SUPPORT_EXPORT spinlock 
		{
			/// \cond
			atomic::atomic<int> m_lock;
			static const unsigned lock_bit = 0;
			/// \endcond
		public:
			/// \brief Default constructor. Spinlock will be initialized in non-locked state.
			inline spinlock()
				: m_lock(0)
			{
			}

			/// \brief Locks the spinlock instance.
			/** Attemt to lock one object twice by the same thread without it's release between, will lead to thread self-blocking.*/
			inline void lock()
			{
				while(true)
				{
					// we should try to avoid frequent system bus lock.
					while(m_lock.load() != 0)
						PAUSE;
					if(m_lock.bit_test_and_set(lock_bit)==0)
						return;
				}
			}

			/// \brief Locks the spinlock, timed version.
			/** \param timeout Time to wait in milliseconds.
			  * \return Boolean value. Positive value if spinlock was locked, false if not(timeout).*/
			inline bool lock(const date_time::system_clock::duration_t timeout)
			{
				while(true)
				{
					date_time::system_clock start;
					while(m_lock.load() != 0)
						if((date_time::system_clock::current() - start) <= timeout)
						{
							PAUSE;
						}
						else
							return false;
					if(m_lock.bit_test_and_set(lock_bit)==0)
						return true;
				}
			}
			/// \brief Tries to lock spinlock.
			/** If spinlock was already locked, thread will continue it's execution.
			  * \return Boolean value. True if spinlock was locked, false if not.*/
			inline bool try_lock()
			{
				return static_cast<bool>(m_lock.bit_test_and_set(lock_bit)); //MSVC is soo stupid
			}
			/// \brief Releases spinlock.
			inline void release()
			{
				m_lock.bit_test_and_reset(lock_bit);
			}
		};
	}//namespace multithreading
}//namespace core

//#include "core/multithreading/details/spinlock.h"

#endif//FREYA_MULTITHREADING_SPINLOCK_H_
