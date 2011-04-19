/* File		: containers/policies/storage/Exponential.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_Greedy_h__
#define Containers_Policies_Greedy_h__

#include "integer.h"

namespace containers
{
	namespace policies
	{
		namespace storage
		{
			//! "Greedy" growth of storage size
			/*! 
			 * Returns required_size always, allowing to allocate the storage space not larger,
			 * than needed
			 */
			//! \ingroup grpContainers_Policies_Storage
			class Greedy
			{
			public:
				size_t		get_vector_size( size_t required_size, size_t current_size ) const
				{
					return required_size; //Well, thats a hack ;)
				}
			};
		}
	}
}

#endif // Containers_Policies_Greedy_h__