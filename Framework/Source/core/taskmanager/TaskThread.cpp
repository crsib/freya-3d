/*
 * TaskThread.cpp
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

#ifdef	_MSC_VER
#include <intrin.h>
extern "C"
{
	long _InterlockedCompareExchange (long volatile *, long, long);
	long __cdecl _InterlockedIncrement(long volatile *);
	long __cdecl _InterlockedDecrement(long volatile *);
}
#endif

#include "TaskThread.h"

#include "core/EngineCore.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"
#include "core/multithreading/Thread.h"
#include "core/multithreading/Runnable.h"
#include "core/multithreading/ThreadBlocks.h"
#include "core/multithreading/Condition.h"
#include "core/multithreading/Mutex.h"
#include "core/multithreading/Lock.h"
#include "core/EngineException.h"
#include <iostream>
namespace core
{

namespace taskmanager
{

namespace __internal
{

class __Task : public core::taskmanager::Task
{
public:
	virtual int operator () ()
	{
		return Task::DONE;
	}
};

class __thread_function : public core::multithreading::Runnable
{
public:
	//core::multithreading::RingBuffer<core::taskmanager::Task*,32>* rb;
	core::taskmanager::TaskManager*	man;
	multithreading::Mutex*			wait_mut;
	multithreading::Condition*      wait_cond;
	virtual int operator () ()
	{
		while(TaskThread::m_Active)
		{
			try
			{
				while(man == 0)
				{
					man = core::EngineCore::getTaskManager();
					core::multithreading::yield();
				}
				if(man->m_SecThreadSchedule.size())
				{
					core::taskmanager::Task*	task = NULL;

					while(test_and_set(&man->m_AuxLock,1))
						core::multithreading::yield();
					if(!man->m_SecThreadSchedule.empty())
					{
						task = man->m_SecThreadSchedule.front();
						man->m_SecThreadSchedule.pop_front();
						man->m_AuxLock = 0;

						if(task && task->retainCount() > 0)
						{
							switch((*task)())
							{
								case core::taskmanager::Task::MAIN_THREAD:
									core::EngineCore::getTaskManager()->addTask(task);
									break;
								case core::taskmanager::Task::SECONDARY_THREAD:
									core::EngineCore::getTaskManager()->addAsynchronousTask(task);
									break;
							}
							task->release();
						}//if(task)
					}//if(man->m_SecThreadSchedule.size()) internal
					else
					{
						man->m_AuxLock = 0;
						wait_mut->lock();
						++core::taskmanager::TaskManager::m_AwaitingThreads;

						wait_cond->wait(wait_mut);

						--core::taskmanager::TaskManager::m_AwaitingThreads;
						wait_mut->unlock();
					}
				}//if(man->m_SecThreadSchedule.size())
				else
				{
					wait_mut->lock();
					++core::taskmanager::TaskManager::m_AwaitingThreads;
					wait_cond->wait(wait_mut);
					--core::taskmanager::TaskManager::m_AwaitingThreads;
					wait_mut->unlock();
				}

			}
			catch(const ::EngineException& ex)
			{
				std::cout << "Sub thread " << ex.message() << std::endl;
			}

			core::multithreading::yield();
		}
		return 0;
	}
};
unsigned	TaskThread::m_Active = 0;

TaskThread::TaskThread(multithreading::Condition* cond, multithreading::Mutex* mut)
{
	m_Active = 1;
	m_Mutex = mut;
	m_Condition = cond;
	m_Func = new __thread_function();
	m_Func->man = core::EngineCore::getTaskManager();
	m_Func->wait_cond = m_Condition;
	m_Func->wait_mut = m_Mutex;
	m_Thread = core::EngineCore::createThread(*m_Func);
}

TaskThread::~TaskThread()
{
	m_Active = 0;
	m_Thread->wait();
	std::cout << "Returning sub thread " << std::endl;
	core::EngineCore::destroyThread(m_Thread);
	//core::EngineCore::destroyMutex(m_Mutex);
	delete m_Func;

}

}

}

}
