/*
 * EngineSubsystem.h
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#ifndef ENGINESUBSYSTEM_H_
#define ENGINESUBSYSTEM_H_

#include <cstdlib>
#include "internal.h"
#include "core/memory/MemoryPools.h"

namespace core
{
namespace memory
{
	EXPORT void* Allocate(size_t,unsigned);
	EXPORT void  Free(void*,unsigned);
}
}

//!This class corrects memory management routines for any engine class except EngineCore and MemoryArena
/*!
 * All Freya subclasses should inherited is some way from this class, as it defines correct memory management while creating them
 */
class EXPORT EngineSubsystem {
public:
	EngineSubsystem()
	{

	}
	virtual ~EngineSubsystem()
	{

	}
	//!Overloaded new operator
	static void* operator new(size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CLASS_POOL);
	}
	//!Overloaded delete operator
	static void  operator delete(void* p)
	{
		core::memory::Free(p,core::memory::CLASS_POOL);
	}
	//!Overloaded new[] operator
	static void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CLASS_POOL);
	}
	//!Overloaded delete[] operator
	static void  operator delete[](void* p)
	{
		core::memory::Free(p,core::memory::CLASS_POOL);
	}

};

#endif /* ENGINESUBSYSTEM_H_ */
