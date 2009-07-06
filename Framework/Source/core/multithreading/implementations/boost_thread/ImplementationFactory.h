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

#include "BoostThread.h"
#include "BoostMutex.h"
#include "BoostCondition.h"

#include <list>
#include <algorithm>
#include <map>

#include "core/memory/MemoryAllocator.h"

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

extern ThreadID*	MainThreadID;
extern std::map<boost::thread::id,BoostThreadID*> ThreadMap;
class ImplementationFactory: public EngineSubsystem
{
	template<typename __impl>
	friend class core::multithreading::ImplementationFactory;
	ImplementationFactory()
	{
		MainThreadID = new BoostThreadID(boost::this_thread::get_id());
	}
	virtual ~ImplementationFactory()
	{
		for(std::map<boost::thread::id,BoostThreadID*>::iterator it = ThreadMap.begin();it!=ThreadMap.end();it++)
			delete it->second;
		for(ThreadList::iterator it = m_Threads.begin();it != m_Threads.end();it++)
			delete (*it);
		for(MutexList::iterator it = m_Muticies.begin();it != m_Muticies.end();it++)
			delete (*it);
		for(ConditionList::iterator it = m_Conds.begin();it != m_Conds.end();it++)
			delete (*it);
	}
public:
	template<typename Callable>
	core::multithreading::Thread*		createThread(Callable proc)
	{
		m_Threads.push_back(new BoostThread(proc));
		return m_Threads.back();
	}

	void		destroyThread(core::multithreading::Thread* thrd)
	{
		ThreadList::iterator it = std::find(m_Threads.begin(),m_Threads.end(),thrd);
		m_Threads.erase(it);
		delete thrd;
	}

	core::multithreading::Mutex*		createMutex()
	{
		m_Muticies.push_back(new BoostMutex());
		//m_Muticies.back()->unlock();
		return m_Muticies.back();
	}

	void		destroyMutex(core::multithreading::Mutex* mutex)
	{
		MutexList::iterator it = std::find(m_Muticies.begin(),m_Muticies.end(),mutex);
		m_Muticies.erase(it);
		delete mutex;
	}

	core::multithreading::Condition*	createCondition()
	{
		m_Conds.push_back(new BoostCondition());
		return m_Conds.back();
	}

	void		destroyCondition(core::multithreading::Condition* cond)
	{
		ConditionList::iterator it = std::find(m_Conds.begin(),m_Conds.end(),cond);
		m_Conds.erase(it);
		delete cond;
	}
private:
	typedef std::list<BoostThread*,core::memory::MemoryAllocator<BoostThread*> > ThreadList;
	ThreadList			m_Threads;
	typedef std::list<BoostMutex*,core::memory::MemoryAllocator<BoostMutex*> > MutexList;
	MutexList			m_Muticies;
	typedef std::list<BoostCondition*,core::memory::MemoryAllocator<BoostCondition*> > ConditionList;
	ConditionList		m_Conds;
};

}

}

}

}

#endif /* IMPLEMENTATIONFACTORY_H_ */
