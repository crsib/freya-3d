/*
 * ImplemtationFactory.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef IMPLEMTATIONFACTORY_H_
#define IMPLEMTATIONFACTORY_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace core
{
class EngineCore;
namespace multithreading
{
class Thread;
class Mutex;
class Condition;

//! This is abstraction to provide correct implemetation factory
/*!
 * This is abstraction to provide correct implemetation factory
 * \tparam __impl is a pointer to class implementing of multithreading, which is actually the same class,
 * but with corretly implemeted members
 */
template<typename __impl>
class ImplementationFactory: virtual public EngineSubsystem
{
	friend class core::EngineCore;
	ImplementationFactory()
	{
		m_Impl = new __impl;
	}

	~ImplementationFactory()
	{
		delete m_Impl;
	}
public:

	template<typename Callable>
	Thread*		createThread(Callable proc)
	{
		return m_Impl->createThread(proc);
	}

	void		destroyThread(Thread* thrd)
	{
		m_Impl->destroyThread(thrd);
	}

	Mutex*		createMutex()
	{
		return m_Impl->createMutex();
	}

	void		destroyMutex(Mutex* mutex)
	{
		m_Impl->destroyMutex(mutex);
	}

	Condition*	createCondition()
	{
		return m_Impl->createCondition();
	}

	void		destroyCondition(Condition* cond)
	{
		m_Impl->destroyCondition(cond);
	}
private:
	__impl*			m_Impl;
};

}

}

#endif /* IMPLEMTATIONFACTORY_H_ */
