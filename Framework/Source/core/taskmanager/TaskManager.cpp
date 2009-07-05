/*
 * TaskManager.cpp
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

#include "core/taskmanager/TaskManager.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskThread.h"

#include "core/multithreading/HardwarePrimitives.h"
#include "core/EngineCore.h"
#include "windowmanager/DriverSubsystems/Multithreading/Thread.h"
#include "windowmanager/DriverSubsystems/Multithreading/Mutex.h"
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

int			_aux_thread_func(void* p)
{
	core::taskmanager::TaskManager*	man = reinterpret_cast<core::taskmanager::TaskManager*>(p);
	while(man->m_ThreadActive != 0)
	{
		try
		{
			if(man->m_SecThreadSchedule.size())
			{
				man->m_Mutex->lock();
				core::taskmanager::Task* task = man->m_SecThreadSchedule.front();
				man->m_Mutex->unlock();
				man->m_SecThreadSchedule.pop();
				if(task)
				{
					man->m_Threads.front()->addTask(task);
					man->m_Threads.sort(_compare);
				}
			}
		}
		catch(const ::EngineException& ex)
		{
			std::cout << "Aux thread " << ex.message() << std::endl;
			return 1;
		}
		//Let another threads to run
		YIELD
	}
	return 0;
}
}

TaskManager::TaskManager()
{
	m_ThreadNumber = 1;
	m_ThreadActive = 1;
	m_Threads.push_front(new core::taskmanager::__internal::TaskThread());

	m_Mutex  = core::EngineCore::getWindowManager()->createMutex();
	m_Thread = core::EngineCore::getWindowManager()->createThread(core::taskmanager::__internal::_aux_thread_func,this);
}

TaskManager::~TaskManager()
{
	m_Mutex->lock();
	m_ThreadActive = 0;
	m_Mutex->unlock();
	std::cout << "Awaiting AUX thread" << std::endl;
	m_Thread->waitThread();
	std::cout << "Returning AUX thread" << std::endl;
	std::list<core::taskmanager::__internal::TaskThread*,core::memory::MemoryAllocator<core::taskmanager::__internal::TaskThread*> >::iterator it;
	for(it = m_Threads.begin(); it != m_Threads.end();++it)
	{
		delete *it;
	}
	core::EngineCore::getWindowManager()->destroyThread(m_Thread);
	core::EngineCore::getWindowManager()->destroyMutex(m_Mutex);
}

void TaskManager::addTask(Task* task)
{
	if(core::EngineCore::isRunning())
		m_MainThreadSchedule.push(task);
}

void TaskManager::addAsynchronousTask(Task* task)
{
	m_Mutex->lock();
	m_SecThreadSchedule.push(task);
	m_Mutex->unlock();
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
	while(!m_MainThreadSchedule.empty())
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
		PAUSE
	}
}

}

}
