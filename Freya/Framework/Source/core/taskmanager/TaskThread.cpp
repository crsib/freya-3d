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
#include "windowmanager/DriverSubsystems/Multithreading/Thread.h"
#include "core/multithreading/HardwarePrimitives.h"
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

int __thread_function(void* p)
{
	core::multithreading::RingBuffer<core::taskmanager::Task*,32>* rb = reinterpret_cast<core::multithreading::RingBuffer<core::taskmanager::Task*,32>*>(p);
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

		YIELD
	}
	return 0;
}

unsigned	TaskThread::m_Active = 0;

TaskThread::TaskThread()
{
	m_Active = 1;
	m_Buffer = new core::multithreading::RingBuffer<core::taskmanager::Task*,32>();
	m_Thread = core::EngineCore::getWindowManager()->createThread(__thread_function,m_Buffer);
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
	m_Thread->waitThread();
	std::cout << "Returning sub thread " << std::endl;
	core::EngineCore::getWindowManager()->destroyThread(m_Thread);
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
