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
#include "core/multithreading/Lock.h"


namespace core
{
namespace multithreading
{
class Thread;
}

namespace taskmanager
{
class TaskManager;
class Task;

namespace __internal
{
class __thread_function;

class TaskThread: virtual public ::EngineSubsystem
{
	friend class core::taskmanager::TaskManager;
	friend class __thread_function;
private:
	TaskThread();

public:
	virtual ~TaskThread();
	void addTask(Task* task);
	size_t count();
	bool operator < (const TaskThread& other) const;
private:
	core::multithreading::RingBuffer<Task*,32>*		m_Buffer;
	core::multithreading::Thread*					m_Thread;
	static unsigned									m_Active;
	__thread_function*								m_Func;
};

}

}

}

#endif /* TASKTHREAD_H_ */
