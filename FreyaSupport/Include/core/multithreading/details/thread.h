/* File	  : core/multithreading/details/thread.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_DETAILS_THREAD_H_
#define FREYA_MULTITHREADING_DETAILS_THREAD_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"
#include "date_time/details/system_clock.h"

namespace core 
{
	/// \brief Contains some useful tools for thread management.
	namespace multithreading 
	{
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
			inline bool join();

			/// \brief Wait for the thread termination for a specified time.
			/** \param timeout Time to wait in milliseconds.
			  * \return Boolean value. True on success.*/
			inline bool join(const date_time::system_clock::duration_t timeout);

			/// \brief Force the thread termination.
			inline void kill();

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

#endif//FREYA_MULTITHREADING_DETAILS_THREAD_H_
