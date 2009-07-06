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
};

}

}

#endif /* TASK_H_ */
