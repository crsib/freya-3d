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
#include "containers/type_utils.h"
#include "EASTL/type_traits.h"
#include "containers/iterator.h"

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
			: private MemoryAllocationPolicy<Value>, private ThreadSafetyPolicy, private RehashPolicy
		{
			struct	HashNode
			{
				Value		node_ptr;
				HashNode*	next;
			};
		public:
			typedef Key		  key_type;
			typedef Key&      key_reference_type;
			typedef typename  const_reference<Key>::type key_const_reference_type;
			typedef Value     value_type;
			typedef	Value*    value_pointer_type;
			typedef Value&	  value_reference;
			typedef typename  const_reference<Value>::type value_const_reference;

			template<typename V> //V is provided to create both const and non const version of iterators
			class iterator_impl
			{
				iterator_impl();
				friend class HashTable;
				template<typename U>
				friend class iterator_impl;

				HashTable*	m_Parent; //Parent
				size_t		m_CurrentBucket; //Current bucket idx
				HashNode*	m_Node; // Current Node
				
				bool		increment_bucket()
				{
					// Increment bucket idx
					++m_CurrentBucket;
					// Skip empty buckets
					while( m_CurrentBucket < m_Parent->m_NumBuckets && !m_Parent->m_Buckets[m_CurrentBucket] )
						++m_CurrentBucket;
					// Check, if the bucket was actually incremented
					if( m_CurrentBucket < m_Parent->m_NumBuckets )
						return true;
					// Well, after 2^32 - 1 iterations m_CurrentBucket will overflow. But who cares?
					return false;
				}

				void		incr()
				{
					if(m_Node) // If we do have a current node
					{
						m_Node = m_Node->next; // Try to traverse the list
						if(!m_Node && increment_bucket()) // Nope, gonna to get the next bucket
							m_Node = m_Parent->m_Buckets[m_CurrentBucket];
					}
				}

				iterator_impl(HashTable* parent) : m_Parent(parent) 
				{
					while( m_CurrentBucket < m_Parent->m_NumBuckets && !m_Parent->m_Buckets[m_CurrentBucket] )
						++m_CurrentBucket;
					m_Node = (m_CurrentBucket < m_Parent->m_NumBuckets) ? 
						 m_Parent->m_Buckets[m_CurrentBucket] : NULL;
				}

				iterator_impl(HashTable* parent, size_t idx, HashNode* node) : m_Parent(parent), m_CurrentBucket(idx), m_Node(node) {}
				
			public:
				typedef V type; // Iterator type
				typedef forward_iterator_tag iterator_type;

				iterator_impl(const iterator_impl& iter) : m_Parent(iter.m_Parent), m_CurrentBucket(iter.m_CurrentBucket), m_Node(iter.m_Node) {}
			
				template<typename U>
				iterator_impl(const iterator_impl<U>& iter) : m_Parent(iter.m_Parent), m_CurrentBucket(iter.m_CurrentBucket), m_Node(iter.m_Node) { /*const_cast<U>(*m_Node->node_ptr);*/ }	
				
				iterator_impl& operator = (const iterator_impl& iter) 
				{
					m_Parent = iter.m_Parent;
					m_CurrentBucket = iter.m_CurrentBucket;
					m_Node = iter.m_Node;
					return *this;
				}
				template<typename U>
				iterator_impl& operator = (const iterator_impl<U>& iter) 
				{
					//const_cast<U>(*m_Node->node_ptr);
					m_Parent = iter.m_Parent;
					m_CurrentBucket = iter.m_CurrentBucket;
					m_Node = iter.m_Node;
					return *this;
				}
				
				//! Prefix ++ operator
				iterator_impl&	operator++ () { incr(); return *this; }
				iterator_impl	operator++ (int) { iterator temp(*this); incr(); return it; }

				V&			operator * () { FREYA_SUPPORT_ASSERT(m_Node, "Invalid node"); return *m_Node; }
				typename const_reference<V>::type
					operator * () const { FREYA_SUPPORT_ASSERT(m_Node, "Invalid node"); return *m_Node; }

				V*			operator-> () { return m_Node; }
				typename const_pointer<V> operator -> () const { return m_Node; }

				bool		operator == (const iterator_impl& rhs) const { return m_Node == rhs.m_Node; } // 
				bool		operator != (const iterator_impl& rhs) const { return m_Node != rhs.m_Node; } // 
			};

			typedef iterator_impl<Value> iterator;
			typedef iterator_impl<typename constant<Value>::type> const_iterator;

			HashTable( float load_factor ) : RehashPolicy ( load_factor ), m_Buckets(NULL), m_NumBuckets(0), m_NumElements(0) {}

			void	rehash( uint32_t bucket_count );
			void	reset();
			void	insert(key_const_reference_type key,value_const_reference v);

			iterator begin() { return iterator(this); }
			iterator end() { return iterator(this, m_NumBuckets, NULL); }

			const_iterator begin() const { return const_iterator(this); }
			const_iterator end() const { return const_iterator(this, m_NumBuckets, NULL); }

			//value_reference	find(key_const_reference_type key); //Find the first element in sequence
			//value_const_reference find(key_const_reference_type key) const; //Find the first element in sequence
			
		private:
			HashNode**		m_Buckets;
			size_t			m_NumBuckets;
			size_t			m_NumElements;

			Compare			m_Compare;
			ExtractKey		m_ExtractKey;

			static void destroy_node_data(HashNode* node, eastl::true_type) {} //Empty for the POD types
			static void destroy_node_data(HashNode* node, eastl::false_type){ node->node_ptr.~T() } //
			static void destroy_node(HashNode* node) { destroy_node(node, eastl::has_trivial_destructor<T>()); }
		};
	} // namespace details
} // namespace containers


#endif // hashtable_h__