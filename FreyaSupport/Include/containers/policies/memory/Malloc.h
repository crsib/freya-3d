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
			class Malloc
			{
				//! Allocate space for "count" objects
				/*! 
				 * Allocate sizeof(T)*count bytes of memory
				 * \param count is a number of object of type T to allocate enough space for
				 * \tparam T is a type
				 * \return pointer to a newly allocated memory block
				 */
				template<typename T>
				static void* allocate(size_t count) throw() { return calloc(count,sizeof(T)); }
				//! Free previously allocate memory
				/*!
				 * Free the memory, allocated by calling New::allocate
				 * \param p is a pointer, which was retrieved by the call to New::allocate
				 */
				static void* deallocate(void* p) throw() { free(p);}
			};
		}
	}
}


#endif // Containers_Policies_Malloc_h__