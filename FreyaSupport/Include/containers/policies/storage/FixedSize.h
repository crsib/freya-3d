/* File		: containers/policies/storage/Exponential.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_FixedSize_h__
#define Containers_Policies_FixedSize_h__

#include "integer.h"

namespace containers
{
	namespace policies
	{
		namespace storage
		{
			//! Fixed-size growth of storage space
			/*! 
			 * Returns n * sz, where n is the smallest to satisfy the following inequality required_size <= current_size <= sz * n
			 * \tparam sz is a size parameter
			 */
			//! \ingroup grpContainers_Policies_Storage
			template<size_t sz>
			class FixedSize
			{
			public:
				size_t		get_vector_size( size_t required_size, size_t current_size ) const
				{
					if(current_size >= 2*sz && required_size < (current_size - sz) )
						return (current_size - sz);
					while(required_size > current_size)
						current_size += sz;
					return current_size;
				}
			};
		}
	}
}

#endif // Containers_Policies_FixedSize_h__