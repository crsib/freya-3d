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
#include "core/EngineException.h"
#include <iostream>
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
	virtual int			operator ()()
	{
		while(man->m_ThreadActive != 0)
		{
			try
			{
				while((man->m_SecThreadSchedule.size() > 0) && man->m_ThreadActive)
				{
					man->m_Mutex->lock();
					core::taskmanager::Task* task = man->m_SecThreadSchedule.front();
					man->m_SecThreadSchedule.pop();
					man->m_Mutex->unlock();
					if(task)
					{
						man->m_Threads.front()->addTask(task);
						man->m_Threads.sort(_compare);
					}
					core::multithreading::yield();
				}
			}
			catch(const ::EngineException& ex)
			{
				std::cout << "Aux thread " << ex.message() << std::endl;
				return 1;
			}
			//Let another threads to run
			core::multithreading::yield();
		}
		return 0;
	}
};

}


TaskManager::TaskManager()
{
	m_ThreadNumber = 1;
	m_ThreadActive = 1;
	m_Threads.push_front(new core::taskmanager::__internal::TaskThread());

	m_Mutex  = core::EngineCore::createMutex();
	m_Func = new __internal::__aux_thread_func();
	m_Func->man = this;
	m_Thread = core::EngineCore::createThread(*m_Func);
}

TaskManager::~TaskManager()
{
	m_Mutex->lock();
	m_ThreadActive = 0;
	m_Mutex->unlock();
	std::cout << "Awaiting AUX thread" << std::endl;
	m_Thread->wait();
	delete m_Func;
	std::cout << "Returning AUX thread" << std::endl;
	core::EngineCore::destroyMutex(m_Mutex);
	core::EngineCore::destroyThread(m_Thread);
	std::list<core::taskmanager::__internal::TaskThread*,core::memory::MemoryAllocator<core::taskmanager::__internal::TaskThread*> >::iterator it;
	for(it = m_Threads.begin(); it != m_Threads.end();++it)
	{
		delete *it;
	}
}

void TaskManager::addTask(Task* task)
{
	if(core::EngineCore::isRunning())
		m_MainThreadSchedule.push(task);
}

void TaskManager::addAsynchronousTask(Task* task)
{
	if(m_ThreadActive)
	{
		m_Mutex->lock();
		m_SecThreadSchedule.push(task);
		m_Mutex->unlock();
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
	while((!m_MainThreadSchedule.empty())&&core::EngineCore::isRunning())
	{
		core::taskmanager::Task*	task = m_MainThreadSchedule.front();
		switch((*task)())
		{
		case core::taskmanager::Task::MAIN_THREAD:
			m_MainThreadSchedule.push(task);
			break;
		case core::taskmanager::Task::SECONDARY_THREAD:
			m_SecThreadSchedule.push(task);
			break;
		default:
			delete task;
		}
		m_MainThreadSchedule.pop();
		//This thread must have the highest priority.
		//Thus, we will not force it to return control
		core::multithreading::pause();
	}
}

}

}
