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
		m_Pools[id]->free(p);
		//::free(p);
	}
	catch(...)
	{
		throw;
	}
}

}
}
