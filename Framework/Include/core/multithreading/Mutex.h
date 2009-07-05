/*
 * Mutex.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef MUTEX_H_
#define MUTEX_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"

namespace core
{

namespace multithreading
{
//! This is implementation independent abstraction of mutex concept
class Mutex: public core::drivermodel::Driver
{
public:
	//! Always returns "mutex"
	virtual EString id() const {return "mutex";}
	//! Lock the mutex for the exclusive access or wait until the mutex is available
	virtual void	lock() = 0;
	//! Try to lock the mutex for the exclusive access
	/*!
	 * Tries to lock the mutex for the exclusive access.
	 * \return true if mutex is successfully locked, false otherwise
	 */
	virtual bool    tryLock() = 0;
	//! Unlock the previously locked mutex
	virtual void    unlock() = 0;
};

}

}

#endif /* MUTEX_H_ */
