/* File		: containers/policies/memory/FreyaAllocator.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_New_h__
#define Containers_Policies_New_h__

#include "integer.h"

namespace containers
{
	namespace policies
	{
		namespace memory
		{
			//! Memory management policy, which uses new uint8_t[sizeof(T)*count] operator for memory allocation
			class New
			{
				//! Allocate space for "count" objects
				/*! 
				 * Allocate sizeof(T)*count bytes of memory
				 * \param count is a number of object of type T to allocate enough space for
				 * \tparam T is a type
				 * \return pointer to a newly allocated memory block
				 */
				template<typename T>
				static void* allocate(size_t count) throw() { return reinterpret_cast<void*>(new(nothrow) uint8_t[sizeof(T)*count]); }
				//! Free previously allocate memory
				/*!
				 * Free the memory, allocated by calling New::allocate
				 * \param p is a pointer, which was retrieved by the call to New::allocate
				 */
				static void* deallocate(void* p) throw() { delete [] reinterpret_cast<uint8_t*>(p);}
			};
		}
	}
}


#endif // Containers_Policies_New_h__