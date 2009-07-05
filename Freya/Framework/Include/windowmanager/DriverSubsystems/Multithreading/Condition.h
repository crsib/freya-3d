/*
 * Condition.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef CONDITION__H_
#define CONDITION__H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace windowmanager
{
namespace multithreading
{
class Mutex;
class Condition: virtual public ::EngineSubsystem
{
	friend class WindowManagerDriver;
protected:
	Condition()
	{
	}
	virtual ~Condition()
	{
	}
public:
	virtual void signal() = 0;
	virtual void broadcast() = 0;
	virtual void wait(const Mutex* mut) = 0;
};

}
}

#endif /* CONDITION_H_ */
