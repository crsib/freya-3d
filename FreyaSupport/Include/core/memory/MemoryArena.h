/* File		: core/memory/MemoryArena.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef MEMORYARENA_H_
#define MEMORYARENA_H_

#include <cstdlib>

#include "core/memory/MemoryPools.h"
#include "FreyaSupportInternal.h"

#include "containers/vector.h"
#include "containers/policies/memory/Malloc.h"
#include "containers/policies/multithreading/AtomicLock.h"
#include "containers/policies/storage/Greedy.h"

#include "core/memory/MemoryDebug.h"

namespace core
{
namespace memory
{

	//! Allocates memory from Freya 3D Engine memory management system
	/*!
	 * Allocate a memory block from MemoryArena
	 * \param size is size of desired memory block in bytes
	 * \param pool is memory pool to use for memory allocation
	 * \return pointer to allocated memory block or NULL if an error has occurred
	 */
FREYA_SUPPORT_EXPORT void*	alloc(size_t size, unsigned pool = core::memory::GENERIC_POOL) throw();

	//! Returns the memory block back to memory management system
	/*!
	 * Try to return the memory block back to MemoryArena
	 * \param p is a pointer to a memory block to be freed
	 * \param pool is a memory pool used to allocate the block
	 */
FREYA_SUPPORT_EXPORT void	dealloc(void* p, unsigned pool = core::memory::GENERIC_POOL) throw();	

	//! Allocates memory from Freya 3D Engine memory management system
	/*!
	 * Allocate a memory block from MemoryArena
	 * \tparam T block type
	 * \param count is a number of blocs of type T
	 * \param pool is memory pool to use for memory allocation
	 * \return pointer to allocated memory block or NULL if an error has occurred
	 */
	template<typename T> T* 
	alloc(size_t count, unsigned pool = core::memory::GENERIC_POOL) throw()
	{
		return reinterpret_cast<T*> (alloc(sizeof(T) * count, pool));
	}

extern FREYA_SUPPORT_EXPORT unsigned memory_allocated;
extern FREYA_SUPPORT_EXPORT unsigned allocation_count;
extern FREYA_SUPPORT_EXPORT unsigned deallocation_count;
extern FREYA_SUPPORT_EXPORT unsigned alloc_dealloc_dif;
extern FREYA_SUPPORT_EXPORT unsigned allocated_for_buffers;

namespace __internal
{
class MemoryPool;
}

//! \brief Core memory management routine
class FREYA_SUPPORT_EXPORT MemoryArena
{
public:
	//! \brief Retrieve the current instance of memory arena
	static MemoryArena*		GetInstance();
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

#ifdef MEMORY_DEBUGGING_ENABLED
	int         getOwner(void* p);
#endif
private:
	//std::vector<__internal::MemoryPool*>		m_Pools;
	typedef containers::vector<__internal::MemoryPool*, 
		containers::policies::memory::Malloc, 
		containers::policies::multithreading::AtomicLock,
		containers::policies::storage::Greedy> pool_vector_t;
	pool_vector_t	m_Pools;
};

} //Namespace memory
} //Namespace core

#endif /* MEMORYARENA_H_ */
