#include "../thread.h"

namespace core {
	namespace multithreading {

			thread thread::InvalidThread = thread();

			bool thread::join() {
				if((m_rights & Synchronization) && is_valid()) {
					bool result = !WaitForSingleObject(m_platform_data->m_handle, INFINITE);
					if(result) {
						details::sync_release_thread_data(m_platform_data);
						m_rights = NoAccessRights;
					}
					return result;
				}
				return false;
			}

			bool thread::join(const unsigned timeout) {
				if((m_rights & Synchronization) && is_valid()) {
					bool result = !WaitForSingleObject(m_platform_data->m_handle, static_cast<DWORD>(timeout));
					if(result) {
						details::sync_release_thread_data(m_platform_data);
						m_rights = NoAccessRights;
					}
					return result;
				}
				return false;
			}

			bool thread::kill() {
				if((m_rights & Termination) && is_valid()) {
	                if(TerminateThread(m_platform_data->m_handle, -1)) {
	                	details::sync_release_thread_data(m_platform_data);
	                    m_rights = NoAccessRights;
	                    return true;
	                }
				}
				return false;
			}

			void thread::destroy(thread& other) {
				if(other.m_rights & Termination) {	//check if we have permission
	                other.kill();					// kill thread if it wasn't
					delete other.m_platform_data;
					other.m_platform_data = NULL;
					other.m_rights = NoAccessRights;
				}
			}

	}//namespace multithreading
}//namespace core
