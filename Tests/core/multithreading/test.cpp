#include <iostream>
#include <time.h>
//#include <atomic/atomic.h>
#include <core/multithreading/thread.h>

using namespace core::multithreading;

namespace core
{
	namespace multithreading
	{
		namespace tests
		{
			class simple_runable
			{
				volatile bool m_thread_run_check;
				static simple_runable* m_instance;
			public:

				static simple_runable* create_instance()
				{
					if(!m_instance)
						return m_instance = new simple_runable;
					return NULL;
				}

				static simple_runable* instance()
				{
					return m_instance;
				}

				static void destroy_instance()
				{
					if(m_instance)
					{
						delete m_instance;
						m_instance = NULL;
					}
				}

				void test(void)
				{
					m_thread_run_check = true;
					while(m_thread_run_check);
				}

				bool is_ok() const
				{ 
					return m_thread_run_check;
				}

				void end_thread_execution()
				{
					m_thread_run_check = false;
				}
			private:
				simple_runable() 
					: m_thread_run_check(false)
				{
				}
			};

			simple_runable* simple_runable::m_instance = 0;

			core::multithreading::thread* thread_ptr = NULL;
			
			bool thread_self_sleep(void)
			{
				std::cout << "thread_self::sleep(): ";
				const unsigned time_to_sleep = 10;//ms
	
				clock_t start = clock();
				thread_self::sleep(time_to_sleep);
				clock_t end = clock();
				const long time_diff = static_cast<long>(end) - static_cast<long>(start);
				std::cout << time_diff;
				if( (time_diff * 1000) >= (static_cast<long>(time_to_sleep) * CLOCKS_PER_SEC) )
				{
					std::cout << "passed.\n";
					return true;
				}
				std::cout << "failed.\n";
				return false;
			}

			bool thread_self_get_freya_id(void)
			{
				std::cout << "thread_self::get_freya_id(): ";
				if(thread_self::get_freya_id() == 0)
				{
					std::cout << "passed.\n";
					return true;
				}
				std::cout << "failed.\n";
				return false;
			}

			bool thread_create(void)
			{
				std::cout << "thread::create(): ";
				simple_runable* sr = simple_runable::create_instance();
				thread_ptr = thread::create<simple_runable, &simple_runable::test>(*sr);
				if( thread_ptr == NULL )
				{
					std::cout << " failed(unable to create thread).\n";
					return false;
				}
				const int check_times = 10;
				int checks = 0;
				while((!sr->is_ok()) && checks < check_times )
				{
					while(!thread_self::yield());
					checks++;
				}
				if(!sr->is_ok())
				{
					std::cout << "failed.\n";
					delete thread_ptr;
					return false;
				}
				std::cout << "passed.\n";
				return true;
			}

			bool thread_is_active(void)
			{
				std::cout << "thread::is_active(): ";
				if(!thread_ptr)
				{
					std::cout << "failed(run thread_create test before).\n";
					return false;
				}
				if(thread_ptr->is_active() == false)
				{
					std::cout << "failed.\n";
					return false;
				}
				std::cout << "passed.\n";
				return true;
			}

			bool thread_timed_join(void)
			{

				const unsigned timeout = 50;
				std::cout << "thread::join(timeout): ";
				if(!thread_ptr)
				{
					std::cout << "failed(run thread_create test before).\n";
					return false;
				}
				if(thread_ptr->join(timeout))
				{
					std::cout << "failed.\n";
					return false;
				}
				std::cout << "passed.\n";
				return true;
			}

			bool thread_join(void)
			{
				std::cout << "thread::join(): ";
				if(!thread_ptr)
				{
					std::cout << "failed(run thread_create test before).\n";
					return false;
				}
				simple_runable::instance()->end_thread_execution();
				while(!thread_self::yield());
				if(!thread_ptr->join())
				{
					std::cout << "failed.\n";
					return false;
				}
				delete thread_ptr;
				simple_runable::destroy_instance();
				return true;
			}
		}//namespace tests
	}//namespace multithreading
}//namespace core

int main(void)
{
	using namespace core::multithreading;

	std::cout<<"Running multithreading test... ";
	if(!tests::thread_self_sleep())
	{
		system("PAUSE");
		return 0;
	}
	if(!tests::thread_self_get_freya_id())
	{
		system("PAUSE");
		return 0;
	}
	if(!tests::thread_create())
	{
		system("PAUSE");
		return 0;
	}
	if(!tests::thread_is_active())
	{
		system("PAUSE");
		return 0;
	}
	if(!tests::thread_timed_join())
	{
		system("PAUSE");
		return 0;
	}
	if(!tests::thread_join())
	{
		system("PAUSE");
		return 0;
	}
}

/*#include <iostream>

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
		//std::cout << "--> PID: " << thread_self::get_platform_id() << std::endl;
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
		//std::cout << "--> PID: " << thread_self::get_platform_id << std::endl;
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
}*/

