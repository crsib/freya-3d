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
	core::multithreading::RingBuffer<core::taskmanager::Task*,32>* rb;
	core::taskmanager::TaskManager*	man;
	virtual int operator () ()
	{
		while(TaskThread::m_Active)
		{
			try
			{
#if 0
				core::taskmanager::Task*	task = rb->fetch();
				if(task)
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
				}
#endif
				while(man == 0)
				{
					man = core::EngineCore::getTaskManager();
					core::multithreading::yield();
				}
				if(man->m_SecThreadSchedule.size())
				{
					core::taskmanager::Task*	task = NULL;
					//synchronize(man->m_MutexAux)
					//{
					while(test_and_set(&man->m_AuxLock,1))
						core::multithreading::yield();
					if(man->m_SecThreadSchedule.size())
					{
						task = man->m_SecThreadSchedule.front();
						//std::cout << "Fetched task: " << (void*) task << " ret " << task->retainCount() << std::endl;
						man->m_SecThreadSchedule.pop_front();
						man->m_AuxLock = 0;

						if(task)
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
						core::multithreading::yield();
					}
				}//if(man->m_SecThreadSchedule.size())
				else
				{
					core::multithreading::yield();
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

TaskThread::TaskThread()
{
	m_Active = 1;
	m_Func = new __thread_function();
	m_Func->man = core::EngineCore::getTaskManager();
	m_Thread = core::EngineCore::createThread(*m_Func);
}

TaskThread::~TaskThread()
{
	m_Active = 0;
	m_Thread->wait();
	std::cout << "Returning sub thread " << std::endl;
	core::EngineCore::destroyThread(m_Thread);
	delete m_Func;

}

}

}

}
