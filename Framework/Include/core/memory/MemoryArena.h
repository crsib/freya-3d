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
#include <cstdlib>
#include <vector>

#include "core/taskmanager/Task.h"
namespace core
{
class EngineCore;
namespace memory
{

namespace __internal
{
	class MemoryPool;
	class MemoryBuffer;
}

class MemoryArena
{
	friend class core::EngineCore;
private:
	MemoryArena();
	virtual ~MemoryArena();
public:
	//! Add a pool to memory arena.
	/*!
	 * Adds a pool to memory arena.
	 * \param size is a desired preallocated size in bytes
	 * \param alligment is a desired memory alligment. This value is a \$ log_2 \$ of needed memory alligment in bytes
	 * \throw MemoryException if pool allocation failed
	 */
	unsigned	addPool(size_t size,size_t alligment);

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
