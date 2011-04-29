/* File   : core/multithreading/details/condition_variable.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_DETAILS_CONDITION_VARIABLE_H_
#define FREYA_MULTITHREADING_DETAILS_CONDITION_VARIABLE_H_

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"
 
namespace core
{
	namespace multithreading
	{
		//predefinitions
		class mutex;

		/// \brief This class provides functionality to implement conditional syncronization.
		/** Class instances are not copyable. */
		class FREYA_SUPPORT_EXPORT condition_variable : private details::condition_variable_rep
		{
		public:
			/// \brief Default constructor. Initializes class instance.
			inline condition_variable();
			
			/// \breif Default destructor.
			inline ~condition_variable();

			/// \brief Makes thread sleep until one of the broadcast() or signal() events will happen.
			/** Before performing this operation thread should lock the mutex(same as methods' argument).
			 * Mutex will be unlocked automatically before the thread will sleep, and locked again after
			 * the thread will wakeup.
			 * \param sync Mutex object to be unlocked. */
			inline void wait(mutex* sync);

			/// \brief Makes thread sleep for a specified time, until one of the broadcast() or signal() events will happen .
			/** Before performing this operation thread should lock the mutex(same as methods' argument).
			 * Mutex will be unlocked automatically before the thread will sleep, and locked again after
			 * the thread will wakeup.
			 * \param sync Mutex object to be unlocked.
			 * \return Boolean value. True if variable is signaled, false if waiting time had been elapsed. */
			inline bool wait(mutex* sync, const unsigned timeout);
			
			/// \brief Wake up all the threads waiting on this condition.
			inline void broadcast();
			
			/// \brief Wake up only one of the threads waiting on this condition.
			inline void signal();
		private:
			/// \brief Copying instances is forbidden.
			condition_variable(const condition_variable&);
			/// \brief Copying instances is forbidden.
			condition_variable& operator=(const condition_variable&);
		};
	}
}

#endif//FREYA_MULTITHREADING_DETAILS_CONDITION_VARIABLE_H_