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
		class FREYA_SUPPORT_EXPORT mutex : public details::mutex_rep
		{
		public:
			inline mutex();
			inline ~mutex();

			inline bool lock();
			inline bool lock(const unsigned ms);
			inline bool try_lock();
			inline void release();

		private:
			mutex(const mutex&);
			mutex& operator=(const mutex&);
		};
	}//namespace multithreading
}//namespace core

#include "core/multithreading/details/mutex.h"

#endif//FREYA_MUTEX_H_