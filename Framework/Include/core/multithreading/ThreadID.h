/*
 * ThreadID.h
 *
 *  Created on: 04.06.2009
 *      Author: vedenko
 */

#ifndef THREADID_H_
#define THREADID_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace core
{

namespace multithreading
{

class ThreadID: public virtual ::EngineSubsystem
{
public:
	virtual bool operator==(const ThreadID& other) const = 0;
	virtual bool operator!=(const ThreadID& other) const = 0;
};

}

}

#endif /* THREADID_H_ */
