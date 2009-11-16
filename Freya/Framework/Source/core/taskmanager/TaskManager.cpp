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
#endif

#ifdef _MSC_VER
#	define test_and_set InterlockedBitTestAndSet
#else
inline long SyncInterlockedExchange(volatile long *Dest, long Val)
{
#if defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
	return  __sync_lock_test_and_set(Dest, Val);
#else
	register int result;
	__asm__ __volatile__("lock; xchg %0,%1"
			: "=r" (result), "=m" (*Dest)
			  : "0" (Val), "m" (*Dest)
			    : "memory");
	return result;
#endif
}

#	define test_and_set SyncInterlockedExchange
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

class __aux_thread_func : public core::multithreading::Runnable
{
public:
	core::taskmanager::TaskManager*	man;
	virtual int
	operator ()()
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

					if(task)
					{
						man->m_Threads.front()->addTask(task);
						man->m_Threads.sort(_compare);
					}//if(task)
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
		return 0;
	}//operator ()
};

}


TaskManager::TaskManager()
{
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
		while(test_and_set(&m_PrimaryLock,1))
			core::multithreading::yield();
		task->retain();
		m_MainThreadSchedule.push_back(task);
		m_PrimaryLock = 0;
	}
}

void TaskManager::addAsynchronousTask(Task* task)
{
	if(m_ThreadActive)
	{
		while(test_and_set(&m_AuxLock,1))
			core::multithreading::yield();
		task->retain();
		m_SecThreadSchedule.push_back(task);
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
		core::taskmanager::Task*	task = NULL;
		while(test_and_set(&m_PrimaryLock,1))
		{
			core::multithreading::yield();
		}

		task = m_MainThreadSchedule.front();
		m_MainThreadSchedule.pop_front();
		m_PrimaryLock = 0;
		if(task)
		{
			int retval = (*task)();

			switch(retval)
			{
				case core::taskmanager::Task::MAIN_THREAD:
					addTask(task);
					break;
				case core::taskmanager::Task::SECONDARY_THREAD:
					addAsynchronousTask(task);
					break;
			}
			task->release();
		}
		//This thread must have the highest priority.
		//Thus, we will not force it to return control
		core::multithreading::pause();
	}
}

}

}
