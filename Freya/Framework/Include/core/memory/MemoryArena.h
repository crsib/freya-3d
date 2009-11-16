/*
 * MemoryArena.h
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYARENA_H_
#define MEMORYARENA_H_

/*
 *
 */
#include "MemoryPools.h"
#include <cstdlib>
#include <vector>
#include "internal.h"

namespace core
{
namespace memory
{


extern EXPORT unsigned memory_allocated;
extern EXPORT unsigned allocation_count;
extern EXPORT unsigned deallocation_count;
extern EXPORT unsigned alloc_dealloc_dif;
extern EXPORT unsigned allocated_for_buffers;

namespace __internal
{
class MemoryPool;
}

class MemoryArena
{
public:
	static MemoryArena*		instance();
	MemoryArena();
	virtual ~MemoryArena();
public:
	//! Add a pool to memory arena.
	/*!
	 * Adds a pool to memory arena.
	 * \param size is a desired preallocated size in bytes
	 * \param alignment is a desired memory alignment in bytes
	 * \throw MemoryException if pool allocation failed
	 */
	unsigned	addPool(size_t size,size_t alignment);

	//! Allocate memory block
	/*!
	 *	Allocates a memory block
	 *	\param size is a desired memory block size in bytes
	 *	\param pool is an ID of memory pool to do allocation in
	 *	\return Pointer to a newly allocated memory block
	 *	\throw  MemoryException on allocation failure
	 */
	void*		allocate(size_t size, unsigned pool = 0);

	//! Free memory block
	/*!
	 * Frees memory block
	 * \param p is a pointer to a block to be free
	 * \param pool is an ID of memory pool to search pointer in
	 * \throw MemoryException if a block is not found inside the pool
	 */
	void		free(void* p,unsigned pool = 0);
private:
	std::vector<__internal::MemoryPool*>		m_Pools;

};

} //Namespace memory
} //Namespace core
#endif /* MEMORYARENA_H_ */
