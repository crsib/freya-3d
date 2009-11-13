/*
 * TaskManager.cpp
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

#include "core/taskmanager/TaskManager.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskThread.h"

#include "core/multithreading/ThreadBlocks.h"
#include "core/EngineCore.h"
#include "core/multithreading/Thread.h"
#include "core/multithreading/Mutex.h"
#include "core/multithreading/Runnable.h"
#include "core/multithreading/Lock.h"
#include "core/EngineException.h"
#include <iostream>

#include <cassert>

#ifdef _MSC_VER
#include <windows.h>
LONGLONG 	freq;
LONGLONG    count = 0;
#endif

namespace core
{

namespace taskmanager
{

namespace __internal
{

bool		_compare(const TaskThread* _1,const TaskThread* _2)
{
	return (*_1) < (*_2);
}

#ifdef _MSC_VER
#	define test_and_set InterlockedBitTestAndSet
#else
#	define test_and_set __sync_lock_test_and_set
#endif

class __aux_thread_func : public core::multithreading::Runnable
{
public:
	core::taskmanager::TaskManager*	man;
	virtual int			operator ()()
					{
		while(man->m_ThreadActive != 0)
		{
			try
			{
				if(man->m_SecThreadSchedule.size())
				{
					core::taskmanager::Task*	task = NULL;
					//synchronize(man->m_MutexAux)
					//{
					while(test_and_set(&man->m_AuxLock,1))
						core::multithreading::yield();

					task = man->m_SecThreadSchedule.front();
					man->m_SecThreadSchedule.pop_front();
					man->m_AuxLock = 0;

					//}//synchronize(man->m_MutexAux)
					if(task)
					{
						//std::cout << "Adding task to buffer" << std::endl; 
						man->m_Threads.front()->addTask(task);
						//std::cout << "Done" << std::endl;
						man->m_Threads.sort(_compare);
					}//if(task)
					core::multithreading::yield();
					continue;
				}//if(man->m_SecThreadSchedule.size())
			}//try
			catch(const ::EngineException& ex)
			{
				std::cout << "Aux thread " << ex.message() << std::endl;
				return 1;
			}
			//Let another threads to run
			core::multithreading::yield();
		}//catch
		//std::cout << "Balancer stopped" << std::endl;
		return 0;
					}//operator ()
};

}


TaskManager::TaskManager()
{
#ifdef _MSC_VER
	QueryPerformanceFrequency((LARGE_INTEGER*)(&freq));
	if(freq == 0)
		freq = 1;
	QueryPerformanceCounter((LARGE_INTEGER*)(&count));
#endif
	m_ThreadNumber = 1;
	m_ThreadActive = 1;
	m_Threads.push_front(new core::taskmanager::__internal::TaskThread());

	m_Func = new __internal::__aux_thread_func();
	m_Func->man = this;
	m_Thread = core::EngineCore::createThread(*m_Func);
	m_PrimaryLock = m_AuxLock = 0;
}

TaskManager::~TaskManager()
{
	m_ThreadActive = 0;
	m_AuxLock = 0;
	std::cout << "Destroying SUB threads" << std::endl;
	std::list<core::taskmanager::__internal::TaskThread*,core::memory::MemoryAllocator<core::taskmanager::__internal::TaskThread*> >::iterator it;
	for(it = m_Threads.begin(); it != m_Threads.end();++it)
	{
		delete *it;
	}
	std::cout << "Awaiting AUX thread " << m_Thread << std::endl;
	m_Thread->wait();
	std::cout << "Returning AUX thread" << std::endl;
	delete m_Func;
	core::EngineCore::destroyThread(m_Thread);
	std::cout << "Destroying tasks from main queue" << std::endl;
	for(unsigned i = 0; i < m_MainThreadSchedule.size();i++)
		while(m_MainThreadSchedule[i]->retainCount())
			m_MainThreadSchedule[i]->release();
	std::cout << "Destroying tasks from AUX queue" << std::endl;
	for(unsigned i = 0; i < m_SecThreadSchedule.size();i++)
		while(m_SecThreadSchedule[i]->retainCount())
			m_SecThreadSchedule[i]->release();
}

void TaskManager::addTask(Task* task)
{
	if(core::EngineCore::isRunning())
	{
		//std::cout << "Entering critical section " << std::endl;
		//synchronize(m_MutexPri)
		//{
		while(test_and_set(&m_PrimaryLock,1))
			core::multithreading::yield();
		task->retain();
		//	std::cout << "Adding task to main thread scheduler " << task << " " << task->retainCount() << std::endl;
		m_MainThreadSchedule.push_back(task);
			//std::cout << "Main scheduler queue size " << m_MainThreadSchedule.size() << std::endl;
		//	assert(m_MainThreadSchedule.back() == task);
		m_PrimaryLock = 0;
		//}
	}
}

void TaskManager::addAsynchronousTask(Task* task)
{
	if(m_ThreadActive)
	{
		while(test_and_set(&m_AuxLock,1))
						core::multithreading::yield();
			task->retain();
			//std::cout << "Adding task to sec thread scheduler " << task << std::endl;
			m_SecThreadSchedule.push_back(task);
			assert(m_SecThreadSchedule.back() == task);
		m_AuxLock = 0;
	}
}

void TaskManager::setThreadNumber(size_t n)
{
	if(n > m_ThreadNumber)
	{
		size_t dif = n - m_ThreadNumber;
		for(size_t i = 0; i < dif; i++ )
			m_Threads.push_front(new core::taskmanager::__internal::TaskThread());
		m_Threads.sort();
	}
}

size_t TaskManager::getThreadNumber()
{
	return m_ThreadNumber;
}

void TaskManager::enterMainLoop()
{
	while(!m_MainThreadSchedule.empty()&&core::EngineCore::isRunning())
	{
//#define PROFILE_TASKMANAGER
#if defined(_MSC_VER) && defined(PROFILE_TASKMANAGER)
	LARGE_INTEGER new_val;
	QueryPerformanceCounter(&new_val);
	__int64 dif = new_val.QuadPart - count;
	count = new_val.QuadPart;
	std::cout << "Time for task process: " << (double)(dif)/freq << std::endl;
#endif
		core::taskmanager::Task*	task = NULL;
		while(test_and_set(&m_PrimaryLock,1))
						core::multithreading::yield();
			task = m_MainThreadSchedule.front();
			m_MainThreadSchedule.pop_front();
		m_PrimaryLock = 0;
		//std::cout << "Running task " << task << std::endl;
		if(task)
		{
			int retval = (*task)();
			//retval <<= 2;
			switch(retval)
			{
			case core::taskmanager::Task::MAIN_THREAD:
		//		std::cout << "Adding task to main queue " << task << std::endl;
				addTask(task);
				break;
			case core::taskmanager::Task::SECONDARY_THREAD:
				addAsynchronousTask(task);
				break;
			}
			//std::cout << "Task returned " << retval << " expected " << core::taskmanager::Task::MAIN_THREAD << std::endl;
			task->release();
		}
		//This thread must have the highest priority.
		//Thus, we will not fûorce it to return control
		//core::multithreading::pause();
	}
}

}

}
