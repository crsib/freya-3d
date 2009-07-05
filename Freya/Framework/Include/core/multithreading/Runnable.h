/*
 * Runnable.h
 *
 *  Created on: 10.05.2009
 *      Author: vedenko
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include "core/EngineSubsystem.h"

/*
 *
 */
namespace core
{

namespace multithreading
{
//! Base abstraction for class, that could be executed on separate thread
/*!
 * All classes, that are going to be executed on a different thread should be inherited from this class
 */
class Runnable : virtual public ::EngineSubsystem
{
public:
	//! Overload this function in subclass to implement the behavior of runnable object
	virtual int operator () () = 0;
};

}

}

#endif /* RUNNABLE_H_ */
