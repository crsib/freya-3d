#include <iostream>

#include "../atomic/atomic.h"
#include "thread.h"
#include "ThreadManager.h"

atomic::atomic<int> console_sync(1);
static const int console_sync_bit = 0;

inline bool try_grub_console()
{
	std::cout << static_cast<int>(console_sync);
	return console_sync.bit_test_and_set(console_sync_bit) == 0;
}

inline void release_console()
{
	//console_sync.bit_test_and_reset(console_sync_bit);//clear CF flag
	console_sync.store(0);
	std::cout << "rel: " << static_cast<int>(console_sync);
}


class ThreadRoutine {
public:
	ThreadRoutine(unsigned int arg) : m_data(arg) {
		while(!try_grub_console());
		std::cout << "Creating ThreadRoutine instance. arg: " /*<< m_data*/ << std::endl;
		release_console();
	}
	void run() {
		using core::multithreading::thread;
		using core::multithreading::ThreadManager;

		while(!try_grub_console());
		//	thread::yield();
		std::cout << "->From : " << thread::self().get_platform_id() << std::endl << "->Arg : " /*<< m_data*/ << std::endl;
		release_console();
	}

	~ThreadRoutine() {
		while(!try_grub_console());
			//core::multithreading::thread::yield();
		std::cout << "Destroying ThreadRoutine instance. arg: " /*<< m_data*/ << std::endl;
		release_console();
	}

private:
	unsigned int m_data;
};


int main(void) {
	using core::multithreading::ThreadManager;
	using core::multithreading::thread;
	
	//check load op
	if(console_sync.load() != 0)
		console_sync.store(0);


	ThreadManager* thread_manager = ThreadManager::createInstance();

	unsigned id_1 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(1))));
	unsigned id_2 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(2))));

	if(thread_manager->getThread(id_1).join())
	{
		while(!try_grub_console());
			//thread::yield();
		std::cout << "Waiting done " << id_1 << std::endl;
		release_console();
	}

	if(thread_manager->getThread(id_2).join())
	{
		while(!try_grub_console());
			//thread::yield();
		std::cout << "Waiting done " << id_2 << std::endl;
		release_console();
	}

	ThreadManager::destroyInstance();

	system("PAUSE");
}
