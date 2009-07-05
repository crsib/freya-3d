/*
 * MemoryPool.h
 *
 *  Created on: 24.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYPOOL_H_
#define MEMORYPOOL_H_
#include <cstdlib>
/*
 *
 */
namespace core
{

namespace memory
{
class MemoryArena;
namespace __internal
{
class MemoryBuffer;
class MemoryPool
{
	friend class core::memory::MemoryArena;
private:
	MemoryPool(size_t alloc_size,size_t alligment);
	virtual ~MemoryPool();

	//! \throws MemoryException
	void*		allocate(size_t size);

	//! \throws MemoryException

	void		free(void* p);
	//Data
	size_t 					m_Alligment;
	size_t					m_AllocSize;

	struct MemoryBufferListItem
	{
		MemoryBufferListItem*	Next;
		MemoryBuffer*   This;

		MemoryBufferListItem()
		{
			Next = NULL;
			This = NULL;
		}
		~MemoryBufferListItem()
		{
			if(Next)
				delete Next;
		}
	};

	MemoryBufferListItem*  m_First;
	MemoryBufferListItem*  m_Last;
	void*				   m_TaskControl;
	unsigned			   m_Blocked;
};

}

}

}

#endif /* MEMORYPOOL_H_ */
