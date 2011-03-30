#include <iostream>

#include "thread.h"
#include "ThreadManager.h"

class ThreadRoutine {
public:
	ThreadRoutine(unsigned int arg) : m_data(arg) {
		//std::cout << "Creating ThreadRoutine instance.\n";
	}
	void run() {
		using core::multithreading::thread;
		using core::multithreading::ThreadManager;

		std::cout << "From : " << thread::self().get_platform_id() << " \nArg : " << m_data << std::endl;
		thread::sleep(10);
	}

	~ThreadRoutine() {
		//std::cout << "Destroying ThreadRoutine instance.\n";
	}

private:
	unsigned int m_data;
};


int main(void) {
	using core::multithreading::ThreadManager;
	using core::multithreading::thread;

	ThreadManager* thread_manager = ThreadManager::createInstance();

	unsigned id_1 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(1))));
	unsigned id_2 = thread_manager->registerNewThread(thread::create<ThreadRoutine, &ThreadRoutine::run>(*(new ThreadRoutine(2))));

	//std::cout << "Waiting for : " << thread_manager->getThread(id_1).get_platform_id() << std::endl;
	if(thread_manager->getThread(id_1).join()) 
		std::cout << "Waiting done.";
	//std::cout << "Waiting for : " << thread_manager->getThread(id_2).get_platform_id() << std::endl;
	if(thread_manager->getThread(id_2).join())
		std::cout << "Waiting done.";

	ThreadManager::destroyInstance();

	system("PAUSE");
}
