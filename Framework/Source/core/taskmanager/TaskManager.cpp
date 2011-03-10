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

namespace core
{

namespace taskmanager
{
//No awaiting thread on the start
unsigned TaskManager::m_AwaitingThreads = 0;

TaskManager::TaskManager()
{
	m_ThreadNumber = core::multithreading::numHardwareThreads();
	if(m_ThreadNumber > 1)
		--m_ThreadNumber;
	//Get the lock mutex and cond
	m_TaskWaitMutex = core::EngineCore::createMutex();
	m_TaskWaitCondition = core::EngineCore::createCondition();
	for(size_t i = 0; i < m_ThreadNumber; i++)
		m_Threads.push_front(new core::taskmanager::__internal::TaskThread(m_TaskWaitCondition, m_TaskWaitMutex));
	m_PrimaryLock = m_AuxLock = 0;
	
}

TaskManager::~TaskManager()
{
	m_AuxLock = 0;
	std::cout << "Destroying SUB threads" << std::endl;
	std::list<core::taskmanager::__internal::TaskThread*,core::memory::MemoryAllocator<core::taskmanager::__internal::TaskThread*> >::iterator it;
	for(it = m_Threads.begin(); it != m_Threads.end();++it)
	{
		m_TaskWaitCondition->broadcast();
		delete *it;
	}

	core::EngineCore::destroyCondition(m_TaskWaitCondition);
	core::EngineCore::destroyMutex(m_TaskWaitMutex);

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
	while(test_and_set(&m_AuxLock,1))
		core::multithreading::yield();
	task->retain();
	m_AuxLock = 0;
	m_SecThreadSchedule.push_back(task);
	{
			if(m_AwaitingThreads)
				m_TaskWaitCondition->signal();
	}
}

void TaskManager::setThreadNumber(size_t n)
{
	if(n > m_ThreadNumber)
	{
		size_t dif = n - m_ThreadNumber;
		for(size_t i = 0; i < dif; i++ )
			m_Threads.push_front(new core::taskmanager::__internal::TaskThread(m_TaskWaitCondition, m_TaskWaitMutex));
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
		core::multithreading::yield();
	}
}

}

}
