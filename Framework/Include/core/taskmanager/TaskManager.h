/*
 * TaskManager.h
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include "core/EngineSubsystem.h"
#include <queue>
#include <list>
#include "core/memory/MemoryAllocator.h"
/*
 *
 */

namespace core
{

class EngineCore;

namespace multithreading
{
class Thread;
class Mutex;
}

namespace taskmanager
{

namespace __internal
{
class TaskThread;
class __aux_thread_func;
}

class Task;

//!This class is a manger for task routines
/*!
 * This class is an implementation of a task manager. It allows the application to use flexible,
 * fast and reliable way to organize and execute various tasks in a multithreaded environment.
 * This class provides control over the way of controlling number of threads, correctly execute
 * tasks that must be executed exclusively on main thread and easing of implementation of multi-part
 * or reentrant tasks
 */
class TaskManager : virtual public ::EngineSubsystem
{
	friend class core::EngineCore;
	friend class core::taskmanager::__internal::__aux_thread_func;
private:
	TaskManager();
	virtual ~TaskManager();
public:
	//! Add a task to the main thread scheduler
	/*!
	 * Adds a task to the main thread scheduler for future execution
	 * \param task is a task to be scheduled
	 */
	void addTask(Task* task);
	//! Add a task to the secondary thread scheduler
	/*!
	 * Adds a task to the main thread scheduler for future execution
	 * \param task is a task to be scheduled
	 */
	void addAsynchronousTask(Task* task);
	//! Set the number of secondary threads.
	/*!
	 *  Set the number of secondary threads. Please note, that this number could not be decreased due to large synchronization
	 *  overhead. By default, there is always one secondary thread (i.e. execution is done on two threads)
	 *  \param n is a desired number of threads
	 */
	void setThreadNumber(size_t n);
	//! Retrieve current secondary threads number
	size_t getThreadNumber();
	//! Enter application's main loop
	/*!
	 * This method is used to enter applications main loop. This method should be called EXACTLY once to assure the correct functionality of engine
	 */
	void enterMainLoop();
private:
	std::queue<Task*,std::deque<Task*,core::memory::MemoryAllocator<Task* > > >	m_MainThreadSchedule;
	std::queue<Task*,std::deque<Task*,core::memory::MemoryAllocator<Task* > > >		m_SecThreadSchedule;
	std::list<core::taskmanager::__internal::TaskThread*,core::memory::MemoryAllocator<core::taskmanager::__internal::TaskThread*> > m_Threads;
	size_t														m_ThreadNumber;
	core::multithreading::Thread*								m_Thread;
	core::multithreading::Mutex*								m_MutexAux;
	core::multithreading::Mutex*								m_MutexPri;
	unsigned													m_ThreadActive;
	__internal::__aux_thread_func*								m_Func;
};

}

}

#endif /* TASKMANAGER_H_ */
