#include "atomic/atomic.h"
#include "core/multithreading/thread.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			FREYA_CORE_EXPORT atomic::atomic<unsigned> __process_thread_counter(0);
		}
		namespace thread_self
		{
			FREYA_CORE_EXPORT local_variable user_id = details::__process_thread_counter++; // main thread id = 0
		}
	}
}