/* File	  : freya/core/multithreading/ThreadManager.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */
/** This file contains a ThreadManager singleton class interface.
 *
 */
#ifndef FREYA_THREAD_MANAGER_H_
#define FREYA_THREAD_MANAGER_H_

namespace core {
	namespace multithreading {

		//Predefinitions :
		class thread;

        /// ThreadManager singleton class interface.
		class ThreadManager {
		public:
			static const unsigned MainThread = 0;	///< Id number of main thread.

			/// Create ThreadManager instance if not exist.
			static ThreadManager* createInstance(const size_t capacity = 8);
			/// Retrieve ThreadManager instance if exist.
			static ThreadManager* getInstance();
			/// Destroy ThreadManager instance if exist.
			static void destroyInstance();

			/// Add new thread to the table.
			/** Thread instance should have thread::AllAccessRights permissions.
			 * May fail if thread was already registered, access rights mismatch
			 * (see thread::AcessRights), table overflow(see ThreadManager::capacity).
			 * @param other Thread instance.
			 * @return Thread number in table. Zero if failed to register thread.
			 */
			unsigned registerNewThread(const thread& other);

			/// Retrieve thread instance by it's number.
			/** May fail if there is no thread in table with such number.
			 * @param which Thread number.
			 * @return Valid thread instance or invalid instance if fail
			 * (use thread::is_valid()).
			 */
            thread& getThread(const unsigned which);

            /// \brief
            /**
             *
             */
            unsigned find(const thread&) const;

		private:
            /// ThreadManager constructor.
			ThreadManager(const size_t capacity);
			/// ThreadManager destructor.
			~ThreadManager();

			const size_t	m_capacity;
			size_t			m_top;
			thread**		m_thread_stack;

			/// Singleton instance pointer.
			static ThreadManager*	m_instance;
		};//class ThreadManager

	}//namespace multithreading
}//namespace core

#endif//FREYA_THREAD_MANAGER_H_
