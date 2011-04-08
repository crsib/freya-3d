#include <iostream>

#include <atomic/atomic.h>
#include <core/multithreading/thread.h>
#include <core/multithreading/ThreadManager.h>

// variable used to thread-safe stdout access, initially locked
atomic::atomic<int> stdout_sync(1);
// stdout_sync bit number used to synchronization
static const int stdout_sync_bit = 0;

// tries to lock stdout, on success returns true
inline bool try_lock_stdout()
{
	return stdout_sync.bit_test_and_set(stdout_sync_bit) == 0;
}

// unlock stdout, so that other threads could access it.
inline void release_stdout()
{
	stdout_sync.bit_test_and_reset(stdout_sync_bit);
}


class ThreadRoutine {
public:
	// prints arg value passed, which is used to identify object/thread
	ThreadRoutine(unsigned int arg) : m_data(arg) {
		using core::multithreading::thread;

		while(!try_lock_stdout()) // try to acquire stdout
			thread::yield(); // switch to another thread on fail
		std::cout << "Creating ThreadRoutine instance. arg: " << m_data << std::endl;
		release_stdout();
	}
	// thread routine
	void run() {
		using core::multithreading::thread;
		using core::multithreading::ThreadManager;

		while(!try_lock_stdout())
			thread::yield();
		std::cout << "->From : " << thread::self().get_platform_id() << std::endl << "->Arg : " << m_data << std::endl;
		release_stdout();
	}

	// prints arg value passed
	~ThreadRoutine() {
		using core::multithreading::thread;
		while(!try_lock_stdout());
			thread::yield();
		std::cout << "Destroying ThreadRoutine instance. arg: " << m_data << std::endl;
		release_stdout();
	}

private:
	unsigned int m_data;
};


int main(void) {
	using core::multithreading::ThreadManager;
	using core::multithreading::thread;
	
	// unlock stdout, at this moment exists only one thread(main),
	// but we use store to ensure that all thread created a below
	// will see that stdout is free to write.
	if(stdout_sync.load() != 0)
		stdout_sync.store(0);

	ThreadManager* thread_manager = ThreadManager::createInstance();

	// Create two threads. Runable objects should be allocated on heap.
	// Then register new threads in thread manager, that should return
	// unique thread id, which is used for fast access to thread instances. 
	unsigned id_1 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(1))));
	unsigned id_2 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(2))));

	// Wait until first thread will be terminated.
	if(thread_manager->getThread(id_1).join())
	{
		// second thread, may be, is running
		while(!try_lock_stdout());
			thread::yield();
		std::cout << "Waiting done " << id_1 << std::endl;
		release_stdout();
	}

	if(thread_manager->getThread(id_2).join())
		// there is no need in synchronization
		std::cout << "Waiting done " << id_2 << std::endl;

	// release all resources allocated by threads and ThreadManager;
	ThreadManager::destroyInstance();

	system("PAUSE");
}
