/* File	  : core/multithreading/details/thread-interface.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_INTERFACE_H_
#define FREYA_THREAD_INTERFACE_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/thread-data.h"

namespace core 
{
	/// \brief Contains some useful tools for thread management.
	namespace multithreading 
	{

		/// \brief This namespace contains functions to control thread of execution.
		namespace thread_self
		{
			/// \brief Yield cpu time to another thread.
			inline void yield();

			/// \brief Makes thread of execution to sleep for a specified time.
			/** \param ms Time to sleep in milliseconds. */
			inline void sleep(const unsigned ms);

			/// \brief 
			inline unsigned get_freya_id();
		}//namespace thread_self

        /// \brief Wrapper over platform provided thread management functions.
        /**  */
		class FREYA_SUPPORT_EXPORT thread {
		public:
			/// \brief
			template<typename T, void (T::*Func)(void)>
			inline static thread* create(T& runable);

			/// \brief
			inline ~thread();

			/// \brief
			inline bool join();

			/// \brief
			inline bool join(const unsigned timeout);

			/// \brief 
			inline bool kill();

			/// \brief
			inline bool is_active() const;

			/// \brief Retrieve platform specific thread id.
			inline unsigned get_platform_id() const;

		private:
            /// \brief Default constructor. Used to create class instance in a platform specific way.
			inline thread();
			/// Copy constructor. Forbidden.
			thread(const thread&);
			///
			thread& operator=(const thread&);

			details::thread_data m_platform_data; 	///< Platform specific thread data.
		};//class thread

	}//namespace multithreading
}//namespace core

#endif//FREYA_THREAD_INTERFACE_H_