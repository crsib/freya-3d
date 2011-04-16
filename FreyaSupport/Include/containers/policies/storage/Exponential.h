/* File		: containers/policies/storage/Exponential.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_Exponential_h__
#define Containers_Policies_Exponential_h__

namespace containers
{
	namespace policies
	{
		namespace storage
		{
			class Exponential
			{
			public:
				size_t		get_vector_size( size_t required_size, size_t current_size ) const
				{
					//if( 2*required_size <= current_size )
					//	return current_size / 2;
					if(current_size == 0)
						current_size = 1;
					while(required_size > current_size)
						current_size *= 2;
					return current_size;
				}
			};
		}
	}
}

#endif // Containers_Policies_Exponential_h__