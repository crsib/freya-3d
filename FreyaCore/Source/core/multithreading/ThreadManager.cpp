/* freya/core/multithreading/ThreadManager.cpp
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 */

#include "core/multithreading/thread.h"
#include "core/multithreading/ThreadManager.h"

namespace core {
	namespace multithreading {

		ThreadManager* ThreadManager::m_instance = NULL;

		ThreadManager* ThreadManager::createInstance(const size_t capacity) {
			if(!m_instance)
				m_instance = new ThreadManager(capacity);
			return m_instance;
		}

		ThreadManager* ThreadManager::getInstance() {
			if(m_instance)
				return m_instance;
			return NULL;
		}

		void ThreadManager::destroyInstance() {
			if(m_instance) {
				m_instance->~ThreadManager();
				m_instance = NULL;
			}
		}

		ThreadManager::ThreadManager(const size_t capacity) : m_capacity(capacity), m_top(0), m_thread_stack(NULL) {
			m_thread_stack = new thread* [m_capacity];
			//Push the main thread first.
			m_thread_stack[ThreadManager::MainThread] = new thread(thread::self());
			m_top++;
		}

		ThreadManager::~ThreadManager() {
			for(unsigned i = m_top - 1; i >= 0 ; i --) {
				//cleanup pointers to threads first.
				thread::destroy(*(m_thread_stack[i]));
				delete m_thread_stack[i];
			}
			delete[] m_thread_stack;
		}

		unsigned ThreadManager::registerNewThread(const thread& other) {
			if(m_top < m_capacity) {
				m_thread_stack[m_top] = new thread(other);
				return m_top++;
			}
			return 0;
		}

		thread& ThreadManager::getThread(unsigned int which) {
			if(which < m_top)
				return *(m_thread_stack[which]);
			return thread::InvalidThread;
		}

	}// namespace multithreading
}//namespace core

