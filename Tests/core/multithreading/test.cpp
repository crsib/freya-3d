#include <iostream>

#include <atomic/atomic.h>
#include <core/multithreading/thread.h>

// variable used to thread-safe stdout access, initially locked
atomic::atomic<short> stdout_sync(1);
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
		using namespace core::multithreading;

		while(!try_lock_stdout()) // try to acquire stdout
			thread_self::yield(); // switch to another thread on fail
		std::cout << "Creating ThreadRoutine instance..." << std::endl;
		std::cout << "--> Arg: " << m_data << std::endl;
		std::cout << "--> UID: " << thread_self::get_freya_id() << std::endl;
		release_stdout();
	}
	// thread routine
	void run() {
		using namespace core::multithreading;

		while(!try_lock_stdout())
			thread_self::yield();
		std::cout << "Thread routine..." << std::endl;
		std::cout << "--> From instance " << m_data << std::endl;
		std::cout << "--> UID: " << thread_self::get_freya_id() << std::endl;
		release_stdout();
	}

	// prints arg value passed
	~ThreadRoutine() {
		using namespace core::multithreading;

		while(!try_lock_stdout());
			thread_self::yield();
		std::cout << "Destroying ThreadRoutine instance " << m_data << "..." << std::endl;
		release_stdout();
	}

private:
	unsigned int m_data;
};


int main(void) {
	using namespace core::multithreading;
	
	// unlock stdout, at this moment exists only one thread(main),
	// but we use store to ensure that all thread created below
	// will see that stdout is free to write.
	if(stdout_sync.load() != 0)
		stdout_sync.store(0);

	std::cout << "Main Thread UID : " << thread_self::get_freya_id() << std::endl;

	ThreadRoutine r1(1);
	ThreadRoutine r2(2);
	thread* t1 = thread::create<ThreadRoutine, &ThreadRoutine::run>(r1);
	thread* t2 = thread::create<ThreadRoutine, &ThreadRoutine::run>(r2);
	// Wait until first thread will be terminated.
	if(t1->join())
	{
		// second thread, may be, is running
		while(!try_lock_stdout());
			thread_self::yield();
		std::cout << "Thread " << t1->get_platform_id() << " joined." << std::endl;
		release_stdout();
	}

	if(t2->join())
		// there is no need in synchronization
		std::cout << "Thread " << t2->get_platform_id() << " joined." << std::endl;

	delete t1;
	delete t2;
	system("PAUSE");
}
