#include <iostream>
#include <time.h>
#include <core/multithreading/thread_self.h>
#include <core/multithreading/thread.h>
#include <date_time/system_clock.h>

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
				const date_time::system_clock::duration_t time_to_sleep = 500;//ms
	
				date_time::system_clock start;
				thread_self::sleep(time_to_sleep);
				date_time::system_clock end;
				date_time::system_clock::duration_t time_diff = end - start;
				std::cout << time_diff;
				if( time_diff >= time_to_sleep )
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
				const int check_times = 100;
				int checks = 0;
				while((!sr->is_ok()) && checks < check_times )
				{
					while(!thread_self::yield());
                                        thread_self::sleep(10);
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
                                std::cout << "passed.\n";
				return true;
			}
		}//namespace tests
	}//namespace multithreading
}//namespace core


int main(void)
{
	using namespace core::multithreading;

	std::cout<<"Running multithreading test... \n";
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
        std::cout << "Completed!";
}
