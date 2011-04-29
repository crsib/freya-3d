/* File   : core/multithreading/win32/thread_self.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_WIN32_THREAD_SELF_H_
#define FREYA_MULTITHREADING_WIN32_THREAD_SELF_H_

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/thread_local.h" //interface only

#define PAUSE YieldProcessor()

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			FREYA_SUPPORT_EXPORT extern core::multithreading::thread_local<unsigned> freya_id;
		}//namespace details

		namespace thread_self
		{
			inline bool yield()
			{
				return (SwitchToThread() != 0);
			}

			inline void sleep(const unsigned ms)
			{
				Sleep( static_cast<DWORD>(ms) );
			}

			inline unsigned get_freya_id()
			{
				return static_cast<unsigned>(details::freya_id);
			}
		}//namespace thread_self
	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_WIN32_THREAD_SELF_H_
