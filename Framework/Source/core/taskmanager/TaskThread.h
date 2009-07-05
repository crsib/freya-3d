/*
 * TaskThread.h
 *
 *  Created on: 11.05.2009
 *      Author: vedenko
 */

#ifndef TASKTHREAD_H_
#define TASKTHREAD_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "core/multithreading/RingBuffer.h"


namespace windowmanager
{
namespace multithreading
{
class Thread;
}
}
namespace core
{
namespace taskmanager
{
class TaskManager;
class Task;

namespace __internal
{
int __thread_function(void* p);

class TaskThread: virtual public ::EngineSubsystem
{
	friend class core::taskmanager::TaskManager;
	friend int __thread_function(void* p);
private:
	TaskThread();

public:
	virtual ~TaskThread();
	void addTask(Task* task);
	size_t count();
	bool operator < (const TaskThread& other) const;
private:
	core::multithreading::RingBuffer<Task*,32>*		m_Buffer;
	windowmanager::multithreading::Thread*			m_Thread;
	static unsigned									m_Active;
};

}

}

}

#endif /* TASKTHREAD_H_ */
