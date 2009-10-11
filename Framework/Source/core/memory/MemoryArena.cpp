/*
 * MemoryArena.cpp
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#include "core/memory/MemoryArena.h"
#include "core/memory/MemoryPool.h"
#include "core/memory/MemoryException.h"

namespace core
{
namespace memory
{

#ifdef _FREYA_DEBUG_MEMORY
	unsigned memory_allocated = 0;
	unsigned allocation_count = 0;
	unsigned deallocation_count = 0;
	unsigned alloc_dealloc_dif = 0;
	unsigned allocated_for_buffers = 0;
#endif

MemoryArena::MemoryArena()
{


}

MemoryArena::~MemoryArena()
{
	for(unsigned i = 0; i < m_Pools.size(); i++)
		delete m_Pools[i];
}

unsigned	MemoryArena::addPool(size_t size,size_t alligment)
{
	try
	{
		m_Pools.push_back(new __internal::MemoryPool(size,alligment));
	}
	catch(...)
	{
		throw;
	}
	return m_Pools.size() - 1;
}

void*		MemoryArena::allocate(size_t sz,unsigned id)
{
	try
	{
#ifdef _FREYA_DEBUG_MEMORY
		allocation_count++;
		alloc_dealloc_dif++;
#endif
		return m_Pools[id]->allocate(sz);;
		//return malloc(sz);
	}
	catch(...)
	{
		throw;
	}
}

void		MemoryArena::free(void* p,unsigned id)
{
	try
	{
		if(p != NULL)
			m_Pools[id]->free(p);
		//::free(p);
	}
	catch(...)
	{
		throw;
	}
#ifdef _FREYA_DEBUG_MEMORY
	if(p != NULL)
	{
		deallocation_count++;
		alloc_dealloc_dif--;
	}
#endif
}

}
}
