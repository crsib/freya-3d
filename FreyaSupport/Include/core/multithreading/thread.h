/* File   : core/multithreading/thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_H_
#define FREYA_THREAD_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"

namespace core 
{
	/// \brief Contains some useful tools for thread management.
	namespace multithreading 
	{
		/// \brief This namespace contains functions to control the thread of execution.
		namespace thread_self
		{
			/// \brief Yields CPU time to another thread.
			inline bool yield();

			/// \brief Makes thread of execution to sleep for a specified time.
			/** \param ms Time to sleep in milliseconds. */
			inline void sleep(const unsigned ms);

			/// \brief Retrieve Freya specific thread id.
			/** Returned value lies in [0..n] interval, where 'n' is a total thread
			  * number that had been created. Zero value corresponds to the main
			  * thread. NB: The id value does not reflect the order in which thread
			  * was created, but uniqueness is guaranteed.
			  * \return Unsigned integral value. */
			inline unsigned get_freya_id();
		}//namespace thread_self

        /// \brief Wrapper over platform provided thread management functions.
        /** In order to enlighten implementation, thread instances could not
		  * copied or assigned by value.*/
		class FREYA_SUPPORT_EXPORT thread : private details::thread_rep {
		public:
			/// \brief Static function that creates new thread.
			/** \tparam T Runnable object type.
			  * \tparam Func Function name that should be called as a thread routine.
			  * \param runable reference to the instance of type T.
			  * \return Pointer to the new thread. In case of error function will return NULL.
			  */
			template<typename T, void (T::*Func)(void)>
			inline static thread* create(T& runable);

			/// \brief Instance destructor.
			/** Thread will be terminated if it wasn't.*/
			inline ~thread();

			/// \brief Wait for the thread termination.
			/** \return Boolean value. True on success.*/
			inline bool join();

			/// \brief Wait for the thread termination for a specified time.
			/** \param timeout Time to wait in milliseconds.
			  * \return Boolean value. True on success.*/
			inline bool join(const unsigned timeout);

			/// \brief Force the thread termination.
			/** \return Boolean value. True on success. */
			inline bool kill();

			/// \brief Retrieve thread state.
			/** \return Boolean value. True if the thread is running. */
			inline bool is_active() const;

			/// \brief Retrieve platform specific thread id.
			/** \return Unsigned integral value corresponding to the thread id, assigned
			  * by the system.*/
			inline unsigned get_platform_id() const;

		private:
            /// \brief Default constructor. Used to create class instance in a platform specific way. Forbidden to use outside class implementation.
			inline thread();
			/// \brief Copy constructor. Forbidden.
			thread(const thread&);
			/// \brief Assign operator is forbidden.
			thread& operator=(const thread&);
		};//class thread

	}//namespace multithreading
}//namespace core

#include "core/multithreading/details/thread.h"

#endif//FREYA_THREAD_H_
