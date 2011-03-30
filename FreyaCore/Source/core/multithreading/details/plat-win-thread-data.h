/* File	  : freya/core/multithreading/details/plat-win-thread-data.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 *
 * This file contains platform-specific thread data implementation.
 * WARNING : Do not use it directly from your code.
 */

#ifndef PLATFORM_WIN_THREAD_DATA_H_
#define PLATFORM_WIN_THREAD_DATA_H_

#include <Windows.h>

namespace core {
	namespace multithreading {
		namespace details {

			struct thread_data {
				HANDLE	m_handle;
				DWORD	m_id;
			};

			//TODO add synchronization
			inline void sync_release_thread_data(thread_data* pdata) {
				CloseHandle(pdata->m_handle);
				pdata->m_handle = NULL;
				pdata->m_id = 0;
			}

		}
	}
}

#endif//PLATFORM_WIN_THREAD_DATA_H_
