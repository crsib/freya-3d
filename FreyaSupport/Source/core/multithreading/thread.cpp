#include "atomic/atomic.h"
#include "core/multithreading/thread_local.h"
#include "core/multithreading/thread.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			FREYA_SUPPORT_EXPORT atomic::atomic<unsigned> __process_thread_counter(0);
			FREYA_SUPPORT_EXPORT core::multithreading::thread_local<unsigned> freya_id = __process_thread_counter++; // main thread id = 0
		}
	}
}