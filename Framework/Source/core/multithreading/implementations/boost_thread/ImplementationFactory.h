/*
 * ImplementationFactory.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef IMPLEMENTATIONFACTORY_H_
#define IMPLEMENTATIONFACTORY_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace core
{

namespace multithreading
{
template<typename __impl>
class ImplementationFactory;

class Thread;
class Condition;
class Mutex;

namespace implementations
{

namespace boost_thread
{

class ImplementationFactory: public EngineSubsystem
{
	template<typename __impl>
	friend class core::multithreading::ImplementationFactory;
	ImplementationFactory();
	virtual ~ImplementationFactory();
public:
	template<typename Callable>
	core::multithreading::Thread*		createThread(Callable proc)
	{

	}

	void		destroyThread(core::multithreading::Thread* thrd)
	{

	}

	core::multithreading::Mutex*		createMutex()
	{
		return m_Impl->createMutex;
	}

	void		destroyMutex(core::multithreading::Mutex* mutex)
	{

	}

	core::multithreading::Condition*	createCondition()
	{

	}

	void		destroyCondition(core::multithreading::Condition& cond)
	{

	}
};

}

}

}

}

#endif /* IMPLEMENTATIONFACTORY_H_ */
