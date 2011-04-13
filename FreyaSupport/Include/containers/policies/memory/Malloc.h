/* File		: containers/policies/memory/Malloc.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_Malloc_h__
#define Containers_Policies_Malloc_h__

#include "integer.h"
#include <stdlib.h>

namespace containers
{
	namespace policies
	{
		namespace memory
		{
			//! Memory management policy, which uses malloc(sizeof(T)*count) operator for memory allocation
			template<typename T>
			class Malloc
			{
			public:
				//! Allocate space for "count" objects
				/*! 
				 * Allocate sizeof(T)*count bytes of memory
				 * \param count is a number of object of type T to allocate enough space for
				 * \return pointer to a newly allocated memory block
				 */
				T* allocate(size_t count) throw() { return reinterpret_cast<T*>(calloc(count,sizeof(T))); }
				//! Free previously allocate memory
				/*!
				 * Free the memory, allocated by calling New::allocate
				 * \param p is a pointer, which was retrieved by the call to New::allocate
				 */
				void deallocate(void* p) throw() { free(p);}
			};
		}
	}
}


#endif // Containers_Policies_Malloc_h__