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
#include "containers/type_utils.h
#include "EASTL/type_traits.h"

namespace containers
{
	namespace details
	{
		template
		<
			typename Key,
			typename Value, 
			class Hash,
			class Compare,
			class ExtractKey,
			template<class> class MemoryAllocationPolicy,
			class ThreadSafetyPolicy,
			class RehashPolicy
		>
		class HashTable 
			: private MemoryAllocationPolicy<T>, private ThreadSafetyPolicy, private RehashPolicy
		{
		public:
			typedef Key		  key_type;
			typedef Key&      key_reference_type;
			typedef typename  const_reference<Key>::type key_const_reference_type;
			typedef Value     value_type;
			typedef	Value*    value_pointer_type;
			typedef Value&	  value_reference;
			typedef typename  const_reference<Value>::type value_const_reference;

			template<typename T>
			class iterator
			{

			};

			HashTable( float load_factor ) : RehashPolicy ( load_factor ), m_Buckets(NULL), m_NumBuckets(0), m_NumElements(0) {}

			void	rehash( uint32_t bucket_count );
			void	reset();
			void	insert(key_const_reference_type key,value_const_reference v);

			//value_reference	find(key_const_reference_type key); //Find the first element in sequence
			//value_const_reference find(key_const_reference_type key) const; //Find the first element in sequence
			
		private:
			struct	HashNode
			{
				T			node_ptr;
				HashNode*	next;
			};

			HashNode**		m_Buckets;
			size_t			m_NumBuckets;
			size_t			m_NumElements;

			Compare			m_Compare;
			ExtractKey		m_ExtractKey;

			static destroy_node_data(HashNode* node, eastl::true_type) {} //Empty for the POD types
			static destroy_node_data(HashNode* node, eastl::false_type){ node->node_ptr.~T() } //
			static destroy_node(HashNode* node) { destroy_node(node, eastl::has_trivial_destructor<T>()); }
		};
	} // namespace details
} // namespace containers


#endif // hashtable_h__