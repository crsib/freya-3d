/* File		: containers/policies/rehash/hashtable.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_PrimeNumber_h__
#define Containers_PrimeNumber_h__

#include "integer.h"
#include "FreyaSupportInternal.h"

#include <cmath>
#include <stddef.h>

namespace containers
{
	namespace policies
	{
		namespace rehash
		{
			//! Prime number rehash policy
			/*!
			 * This policy will return the closest not-least prime number to generate at least
			 * elem_count/load_factor buckets. To optimize number of rehashes this policy will also check,
			 * the new bucket count is at least twice as large as the previous. This policy is not designed
			 * to allow shrinking of the buckets count. See containers::hash_map for details on shrinking 
			 * the bucket count
			 *  \ingroup grpContainers_Policies_Rehash
			 */
			class FREYA_SUPPORT_EXPORT PrimeNumber
			{
				float				m_LoadFactor;
				mutable size_t		m_NextRehashSize; //This parameter is lazy evaluated in get_bucket_count
			public:
				//! Construct a rehash policy with load factor, specified as \a load_factor
				explicit PrimeNumber(float load_factor)  
					: m_LoadFactor(load_factor) , m_NextRehashSize( 0 ) {}
				//! Check, if rehash is needed
				bool	rehash_needed(size_t elem_count, size_t bucket_count) const 
				{
					if(elem_count <= m_NextRehashSize)
						return false;
					return (static_cast<float>(elem_count) / bucket_count) > m_LoadFactor;
				}
				//! Retrieve the new bucket count
				uint32_t get_bucket_count( size_t elem, size_t bucket_count ) const;

				//! Reset the policy to the initial state
				void	reset() { m_NextRehashSize = 0; }
			};
		}
	}
}

#endif // PrimeNumber_h__