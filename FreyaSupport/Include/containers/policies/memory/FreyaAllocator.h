/* File		: containers/policies/memory/FreyaAllocator.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_FreyaAllocator_h__
#define Containers_Policies_FreyaAllocator_h__

#include "integer.h"
#include "core/memory/MemoryArena.h"

namespace containers
{
	namespace policies
	{
		namespace memory
		{
			//! \brief Memory management policy, which uses Freya MemoryArena for memory allocation
			//! \ingroup grpContainers_Policies_Memory
			template<typename T>
			class FreyaAllocator
			{
			public:
				//! Allocate space for "count" objects
				/*! 
				 * Allocate sizeof(T)*count bytes of memory
				 * \param count is a number of object of type T to allocate enough space for
				 * \return pointer to a newly allocated memory block
				 */
				T* allocate(size_t count) throw() { return reinterpret_cast<T*>(core::memory::alloc(sizeof(T)*count, core::memory::STL_POOL)); }
				//! Free previously allocate memory
				/*!
				 * Free the memory, allocated by calling New::allocate
				 * \param p is a pointer, which was retrieved by the call to New::allocate
				 */
				void deallocate(void* p) throw() { core::memory::dealloc(p,core::memory::STL_POOL); }
			};
		}
	}
}

#endif // Containers_Policies_FreyaAllocator_h__