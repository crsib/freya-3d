/* File	  : multithreading/details/plat-win-thread-data.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
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

			typedef DWORD tls_index_t;
		}
	}
}

#endif//PLATFORM_WIN_THREAD_DATA_H_
