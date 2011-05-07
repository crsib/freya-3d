#include "atomic/atomic.h"
#include "core/multithreading/thread_local.h"
#include "core/multithreading/thread.h"
#include "core/multithreading/mutex.h"
#include "core/multithreading/condition_variable.h"
#include "core/multithreading/thread_self.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			atomic::atomic<unsigned> __process_thread_counter(0);
			core::multithreading::thread_local<unsigned> freya_id = __process_thread_counter++; // main thread id = 0
		}
	}
}