/*
 * EngineSubsystem.h
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#ifndef ENGINESUBSYSTEM_H_
#define ENGINESUBSYSTEM_H_

#include <cstdlib>
namespace core
{
namespace memory
{
	void* Allocate(size_t,unsigned);
	void  Free(void*,unsigned);
}
}
//!This class corrects memory management routines for any engine class except EngineCore and MemoryArena
/*!
 * All Freya subclasses should inherited is some way from this class, as it defines correct memory management while creating them
 */
class EngineSubsystem {
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
		return core::memory::Allocate(sz,3);
	}
	//!Overloaded delete operator
	static void  operator delete(void* p)
	{
		core::memory::Free(p,3);
	}
	//!Overloaded new[] operator
	static void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,3);
	}
	//!Overloaded delete[] operator
	static void  operator delete[](void* p)
	{
		core::memory::Free(p,3);
	}

};

#endif /* ENGINESUBSYSTEM_H_ */