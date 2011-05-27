/* File		: log test:log_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "core/memory/MemoryArena.h"
#include "core/Log.h"
#include "core/multithreading/multithreading.h"
#include <iostream>

class Runnable
{
	core::multithreading::thread* m_Thread;
public:
	Runnable()
	{
		InfoLog("Creating thread");
		m_Thread = core::multithreading::thread::create<Runnable, &Runnable::run>(*this);
	}

	~Runnable()
	{
		m_Thread->join();
		delete m_Thread;
		InfoLog("Thread destroyed");
	}

	void run()
	{
		CriticalLog("From thread %u",core::multithreading::thread_self::get_freya_id());
	}
};

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
	{

		InfoLog("AppStarted");

		ErrorLog("Starting threads");

		{
			Runnable _1,_2,_3,_4;
		}

		core::Log::GetInstance().setLogLevel(core::Log::Error);

		InfoLog("Info");
		DebugLog("Debug");
		ErrorLog("Error");
		CriticalLog("Critical").append(" error test").append(" of append") << " using operator << " << 10;

		//core::Log::LogStream log = ErrorLog("");
		ErrorLog() << 10.0f;
	}

	core::Log::GetInstance().flush();

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;
	system("pause");
	return 0;
}
