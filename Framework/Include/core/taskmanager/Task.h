/*
 * Task.h
 *
 *  Created on: 10.05.2009
 *      Author: vedenko
 */

#ifndef TASK_H_
#define TASK_H_

#include "core/multithreading/Runnable.h"
/*
 *
 */
namespace core
{
//! This namespace contains various classes connected with engines task management logic
namespace taskmanager
{
//! This class is a base class for a task
class Task : public core::multithreading::Runnable
{
private:
	unsigned m_TaskCounter;
protected:
	Task() : m_TaskCounter(0) {}
	virtual ~Task(){}
public:
	virtual int operator () () = 0;

	//! Return values enumeration
	enum ReturnValue
	{
		//!Remove from execution
		DONE = 0,
		//!Add to the main thread queue end
		MAIN_THREAD = 1,
		//!Add to the secondary thread queue end
		SECONDARY_THREAD = -1
	};

	//!This function increments task counter by 1 and return this
	Task*	retain();
	//!This function decrements task counter by 1 and destoys it when counter is 0
	void	release();
	
	unsigned retainCount();
};

}

}

#endif /* TASK_H_ */
