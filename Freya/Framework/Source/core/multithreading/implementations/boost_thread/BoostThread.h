/*
 * BoostThread.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef BOOSTTHREAD_H_
#define BOOSTTHREAD_H_

/*
 *
 */
#include "core/multithreading/Thread.h"

namespace core
{

namespace multithreading
{

namespace implementations
{

namespace boost_thread
{

class BoostThread: public core::multithreading::Thread
{
public:
	BoostThread();
	virtual ~BoostThread();
};

}

}

}

}

#endif /* BOOSTTHREAD_H_ */
