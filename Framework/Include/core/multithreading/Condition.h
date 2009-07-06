/*
 * Condition.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef CONDITION_H_
#define CONDITION_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"

namespace core
{

namespace multithreading
{
class Mutex;
//! This is an platform independent abstraction of condition variable concept
class Condition: public core::drivermodel::Driver
{
public:
	//! Always returns "cond_var"
	virtual EString id() const {return "cond_var";}
	//! Block the current thread and release previously acquired mutex
	/*!
	 * Block the current thread and release previously acquired mutex until the one of signal or broadcast is called
	 * The mutex  <STRONG>must</STRONG> be previously locked
	 */
	virtual void wait(Mutex* mut) = 0;
	//! Notify one of the waiting threads to continue its job
	virtual void signal() = 0;
	//! Notify all waiting threads to continue their jobs
	virtual void broadcast() = 0;
};

}

}

#endif /* CONDITION_H_ */
