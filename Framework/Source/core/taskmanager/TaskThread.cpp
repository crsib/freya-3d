/*
 * TaskThread.cpp
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

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
	virtual int operator () ()
	{
		while(TaskThread::m_Active)
		{
			try
			{
				core::taskmanager::Task*	task = rb->fetch();
				switch((*task)())
				{
				case core::taskmanager::Task::MAIN_THREAD:
					core::EngineCore::getTaskManager()->addTask(task);
					break;
				case core::taskmanager::Task::SECONDARY_THREAD:
					core::EngineCore::getTaskManager()->addAsynchronousTask(task);
					break;
				default:
					delete task;
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
	m_Buffer = new core::multithreading::RingBuffer<core::taskmanager::Task*,32>();
	m_Func = new __thread_function();
	m_Func->rb = m_Buffer;
	m_Thread = core::EngineCore::createThread(*m_Func);
}

TaskThread::~TaskThread()
{
	m_Active = 0;
	if(m_Buffer->empty())
	{
		std::cout << "Unloking sub thread [empty] " << std::endl;
		m_Buffer->deposit(new __Task);
	}
	if(m_Buffer->full())
	{
		std::cout << "Unloking sub thread [full]" << std::endl;
		m_Buffer->fetch();
	}
	std::cout << "Awaiting sub thread " << std::endl;
	m_Thread->wait();
	std::cout << "Returning sub thread " << std::endl;
	core::EngineCore::destroyThread(m_Thread);
	delete m_Func;
	delete m_Buffer;
}

void TaskThread::addTask(Task* task)
{
	m_Buffer->deposit(task);
	//std::cout << "[Sub thread] tasks: " << m_Buffer->count() << std::endl;
}

size_t TaskThread::count()
{
	return m_Buffer->count();
}

bool TaskThread::operator < (const TaskThread& other) const
{
	return (m_Buffer->count() < other.m_Buffer->count());
}

}

}

}
