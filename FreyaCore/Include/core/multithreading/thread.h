/* File   : freya/core/multithreading/thread.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_H_
#define FREYA_THREAD_H_

#include "FreyaCoreInternal.h"

/** \file thread.h This file contains platform independent thread class interface.
 *
 * The target platform, by default, will be chosen automatically. If it
 * is not what you want, or platform was detected incorrectly, please define
 * "FREYA_THREAD_PLATFORM_AUTODETECT_DISABLE" to disable auto detection,
 * and then define "PLATFORM_*_THREADS" with desired(WIN or POSIX)
 * platform instead of template symbol. */

namespace core 
{
	/// \brief Contains some useful tools for thread management.
	namespace multithreading 
	{

		/// \brief Contains platform specific code.
		namespace details {
            //Predefinitions :
			struct thread_data;
        }

		class ThreadManager;

        /// \brief Wrapper over thread management system provided by platform.
        /**  */
		class FREYA_CORE_EXPORT thread {
		public:
            /// Thread access rights control.
			enum AccessRights {
				NoAccessRights	= (0x0 << 0),	///< Special value. Only thread status can be retrieved. Means that thread was killed, destroyed was not properly created.

				Synchronization	= (0x1 << 0),	///< Thread could be joined.
                Termination     = (0x1 << 1),	///< Thread could be killed and destroyed.
                PseudoThread	= (0x1 << 2),	///< Same as thread::NoAccessRights, except that thread exists.

                AllAccessRights	= (0x3 << 0)	///< Special value. thread::Synchronization & thread::Termination.
			};

			/// Constant used to create invalid thread.
			static const thread InvalidThread;

            /// \brief Thread copy constructor. Access rights would be inherited.
			inline thread(const thread& other);

            /// \brief Thread destructor.
			inline ~thread();

            /// \brief Assignment operator. Same as copy constructor.
			inline thread& operator=(const thread& other);

			/// \brief Comparison operator. Equality.
			inline bool operator==(const thread& other) const;

			/// \brief Comparison operator. Inequality.
			inline bool operator!=(const thread& other) const;

            /// \brief Wait for this thread will complete execution.
            /** In case of success system resources will be freed.
             * Instance must have thread::Synchronization permission.
             * \return False if thread of execution and this thread are same,
             * thread have already done it's job, thread have been destroyed. */
			bool join();

            /// \brief Wait for this thread will complete execution for specified time.
            /** Class instance must have thread::Synchronization permission.
             * \param timeout Time to wait in milliseconds.
             * \return See thread::join() for details.*/
			bool join(const unsigned timeout);

            /// Kill thread. Unsafe.
            /** Class instance must have thread::Termination permission. Changes
             * access rights to thread::NoAccessRights.
             * \return False if instance does not have appropriate permission,
             * , thread was already canceled, thread of execution and this thread
             * are same. */
			bool kill();

            /// Thread validation.
            /** \return False if thread was not properly created or was killed. */
			inline bool is_valid() const;

            /// Get thread access rights.
			inline unsigned int get_access_rights() const { return m_rights; }

			/// Get platform id.
			inline unsigned int get_platform_id() const;

            /// Switch execution to another thread.
			inline static void yield();

            /// Sleeps thread of execution on a specified time.
            /** \param ms time to sleep in milliseconds. */
			inline static void sleep(const unsigned ms);
			
            /// Thread of execution. Gets thread::PseudoThread.
            /** \return thread which have called this method. */
			inline static thread self();

            /// Create new thread in process.
            /** This function takes some class instance as argument and executes
             * one of it's function, specified as template parameter, from the
             * new thread. Object should be allocated on heap.
             * \tparam ObjT Object type name.
             * \tparam Function Callback function name.
             * \param object Reference to the object.
             * \return New thread. If thread was properly created it gets
             * thread::AllAccessRight permissions. */
            template<typename ObjT, void (ObjT::*Function)()>
			static thread create(ObjT& object);
			
            /// Destroy thread.
            /** Thread should have thread::Termination permission. Changes
             * access rights to thread::NoAccessRights.
             * \param other Thread to be destroyed. */
			static void destroy(thread& other);

		private:
            /// Default constructor. Used to create class instance in a platform specific way.
			inline thread();

			details::thread_data*	m_platform_data; 	///< Pointer to a platform specific thread description.
			unsigned int			m_rights;			///< Instance rights.
		};//class thread

	}//namespace multithreading
}//namespace core

#include "details/thread-details.h"

#endif//FREYA_THREAD_H_
