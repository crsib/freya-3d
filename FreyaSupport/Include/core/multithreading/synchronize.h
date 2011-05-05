/* File   : core/multithreading/details/spinlock.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_SYNCHRONIZE_H_
#define FREYA_MULTITHREADING_SYNCHRONIZE_H_

/** /def synchronize(lockabele) This macros provides Java-syntax-style synchronization mechanism.
  * Any instance which class have "Lockable" compatible interface could be used as /a lockable.
  * /a lockable should be a pointer.
  * Locks /a lockable on the brackets entry, and releases it on terminate bracket.
  */
#define synchronize(lockable) for(volatile bool __freya_temp_synchronize_lock_once = core::multithreading::details::__synchronize_lock(lockable);\
									__freya_temp_synchronize_lock_once; \
									__freya_temp_synchronize_lock_once = core::multithreading::details::__synchronize_release(lockable))

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			/// \cond
			template<typename Lockable>
			bool __synchronize_lock(Lockable* ptr)
			{
				ptr->lock();
				return true;
			}

			template<typename Lockable>
			bool __synchronize_release(Lockable* ptr)
			{
				ptr->release();
				return false;
			}

			/// \endcond
		}//namespace details
	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_SYNCHRONIZE_H_