/* File		: containers/details/hashtable.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_hashtable_h__
#define Containers_hashtable_h__

#include "integer.h"
#include "FreyaSupportInternal.h"

#include "containers/utils.h"

namespace containers
{
	namespace details
	{
		template
		<
			typename T, 
			class Hash,
			class Compare,
			template<class> class MemoryAllocationPolicy,
			class ThreadSafetyPolicy,
			class RehashPolicy
		>
		class HashTable 
			: private MemoryAllocationPolicy<T>, private ThreadSafetyPolicy, private RehashPolicy
		{
		public:
			HashTable( float load_factor ) : RehashPolicy ( load_factor ) {}
		};
	} // namespace details
} // namespace containers


#endif // hashtable_h__