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

namespace containers
{
	namespace policies
	{
		namespace rehash
		{
			class FREYA_SUPPORT_EXPORT PrimeNumber
			{
				float				m_LoadFactor;
				mutable size_t		m_NextRehashSize; //This parameter is lazy evaluated in get_bucket_count
			public:
				explicit PrimeNumber(float load_factor)  
					: m_LoadFactor(load_factor) , m_NextRehashSize( 0 ) {}
				bool	rehash_needed(size_t elem_count, size_t bucket_count) const 
				{
					if(elem_count <= m_NextRehashSize)
						return false;
					return (static_cast<float>(elem_count) / bucket_count) > m_LoadFactor;
				}

				uint32_t get_bucket_count( size_t elem, size_t bucket_count ) const;
			};
		}
	}
}

#endif // PrimeNumber_h__