/*
 * Shutdown.h
 *
 *  Created on: 26.05.2009
 *      Author: vedenko
 */

#ifndef SHUTDOWN_H_
#define SHUTDOWN_H_

/*
 *
 */
#include "core/taskmanager/Task.h"

namespace core
{

namespace taskmanager
{

class Shutdown: public core::taskmanager::Task
{
public:
	Shutdown();
	virtual ~Shutdown();
	virtual int operator () ();
};

}

}

#endif /* SHUTDOWN_H_ */
