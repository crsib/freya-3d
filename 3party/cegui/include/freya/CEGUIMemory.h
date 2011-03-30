/*
 * CEGUIMemory.h
 *
 *  Created on: Oct 14, 2009
 *      Author: crsib
 */

#ifndef CEGUIMEMORY_H_
#define CEGUIMEMORY_H_
#include "core/memory/MemoryPools.h"
#include "internal.h"
#ifndef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
extern bool ArenaCreated;
EXPORT void* Allocate(size_t,unsigned);
EXPORT void  Free(void*,unsigned);
}
}
#endif

namespace CEGUI
{

class CEGUIMemory
{
public:
	virtual ~CEGUIMemory(){}
	static
	void* operator new(size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CEGUI_POOL);
	}
	//!Overloaded delete operator
	static
	void  operator delete(void* p)
	{
		core::memory::Free(p,core::memory::CEGUI_POOL);
	}
	//!Overloaded new[] operator
	static
	void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CEGUI_POOL);
	}
	//!Overloaded delete[] operator
	static
	void  operator delete[](void* p)
	{
		core::memory::Free(p,core::memory::CEGUI_POOL);
	}

};

}

#endif /* CEGUIMEMORY_H_ */
