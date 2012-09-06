/* File		: containers/details/hashtable.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_hashtable_h__
#define Containers_hashtable_h__

#include <new>
#include "integer.h"
#include "FreyaSupportInternal.h"
#include "containers/utils.h"
#include "containers/type_utils.h"
#include "containers/iterator.h"
#include "EASTL/type_traits.h"

namespace containers
{
	namespace details
	{
		//!\cond
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
			: private RehashPolicy
		{
			struct	HashNode
			{
				Value		value;
				HashNode*	next;
			};
		public:
			typedef Key		  key_type;
			typedef Key&      key_reference_type;
			typedef typename  make_const_reference<Key>::type key_const_reference_type;
			typedef Value     value_type;
			typedef	Value*    value_pointer_type;
			typedef Value&	  value_reference;
			typedef typename  make_const_reference<Value>::type value_const_reference;

			template<typename V, bool is_constant> //V is provided to create both const and non const version of iterators
			class iterator_impl
			{
				iterator_impl();
				friend class HashTable;
				template<typename U, bool>
				friend class iterator_impl;

				typedef typename select_type<const HashTable*, HashTable*, is_constant>::type parent_type;
				typedef typename select_type<const HashNode*, HashNode*, is_constant >::type node_type;

				parent_type	m_Parent; //Parent
				size_t		m_CurrentBucket; //Current bucket idx
				node_type	m_Node; // Current Node
				
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

				iterator_impl(parent_type parent) : m_Parent(parent) 
				{
					m_CurrentBucket = 0;
					while( m_CurrentBucket < m_Parent->m_NumBuckets && !m_Parent->m_Buckets[m_CurrentBucket] )
						++m_CurrentBucket;
					m_Node = (m_CurrentBucket < m_Parent->m_NumBuckets) ? 
						 m_Parent->m_Buckets[m_CurrentBucket] : NULL;
				}

				iterator_impl( parent_type parent, const size_t idx,  node_type node) : m_Parent(parent), m_CurrentBucket(idx), m_Node(node) {}
				
			public:
				typedef V type; // Iterator type
				typedef forward_iterator_tag iterator_type;

				iterator_impl(const iterator_impl& iter) : m_Parent(iter.m_Parent), m_CurrentBucket(iter.m_CurrentBucket), m_Node(iter.m_Node) {}
			
				template<typename U>
				iterator_impl(const iterator_impl<U, false>& iter) : m_Parent(iter.m_Parent), m_CurrentBucket(iter.m_CurrentBucket), m_Node(iter.m_Node) { /*const_cast<U>(*m_Node->node_ptr);*/ }	
				
				iterator_impl& operator = (const iterator_impl& iter) 
				{
					m_Parent = iter.m_Parent;
					m_CurrentBucket = iter.m_CurrentBucket;
					m_Node = iter.m_Node;
					return *this;
				}
				template<typename U>
				iterator_impl& operator = (const iterator_impl<U,false>& iter) 
				{
					//const_cast<U>(*m_Node->node_ptr);
					m_Parent = iter.m_Parent;
					m_CurrentBucket = iter.m_CurrentBucket;
					m_Node = iter.m_Node;
					return *this;
				}
				
				//! Prefix ++ operator
				iterator_impl&	operator++ () { incr(); return *this; }
				iterator_impl	operator++ (int) { iterator_impl temp(*this); incr(); return temp; }

				V&			operator * () { FREYA_SUPPORT_ASSERT(m_Node, "Invalid node"); return m_Node->value; }
				typename make_const_reference<V>::type
					operator * () const { FREYA_SUPPORT_ASSERT(m_Node, "Invalid node"); return m_Node->value; }

				V*			operator-> () { return &m_Node->value; }
				const_pointer<V> operator -> () const { return &m_Node->value; }

				bool		operator == (const iterator_impl& rhs) const { return m_Node == rhs.m_Node; } // 
				bool		operator != (const iterator_impl& rhs) const { return m_Node != rhs.m_Node; } // 
			};

			typedef iterator_impl<Value,false> iterator;
			typedef iterator_impl<typename constant<Value>::type,true> const_iterator;

			typedef pair<iterator,iterator> iterator_range;
			typedef pair<const_iterator, const_iterator> const_iterator_range;

			HashTable( float load_factor ) : RehashPolicy ( load_factor ), m_Buckets(NULL), m_NumBuckets(0), m_NumElements(0) {}
			~HashTable() { reset(); }

			void	rehash( uint32_t bucket_count );

			void	reset(); // Cleans up all the memory
			void	clear(); // Destroys all items, but does not destroy m_Buckets

			iterator	insert(value_const_reference v);
			void		insert(const_iterator begin, const_iterator end);// Insert range

			iterator begin() { return iterator(this); }
			iterator end() { return iterator(this, m_NumBuckets, NULL); }

			const_iterator begin() const { return const_iterator(this); }
			const_iterator end() const { return const_iterator(this, m_NumBuckets, NULL); }

			iterator_range	find(key_const_reference_type key); //Find the first element in sequence
			const_iterator_range find(key_const_reference_type key) const; //Find the first element in sequence

			iterator		find_first(key_const_reference_type key);
			const_iterator	find_first(key_const_reference_type key) const;

			void	erase(const iterator& it );  
			void	erase(const iterator& first, const iterator& last);
			void	erase(const iterator_range& range)
			{
				erase(range.first, range.second);
			}
			
			
			ThreadSafetyPolicy& lock_policy() { return m_LockPolicy; }

			size_t			get_elements_count() const { return m_NumElements; }
			size_t			get_buckets_count() const { return m_NumBuckets; }

                        float           load_factor() const { return RehashPolicy::getLoadFactor(); }
		private:
			HashNode**		m_Buckets;
			size_t			m_NumBuckets;
			size_t			m_NumElements;

			Compare								m_Compare;
			ExtractKey							m_ExtractKey;
			MemoryAllocationPolicy<HashNode>	m_NodeAllocator;
			MemoryAllocationPolicy<HashNode*>	m_BucketAllocator;
			ThreadSafetyPolicy					m_LockPolicy;
			Hash								m_Hasher;

			static void destroy_node_data(HashNode* node, eastl::true_type) {} //Empty for the POD types
			static void destroy_node_data(HashNode* node, eastl::false_type){ node->value.~Value(); } //
			static void destroy_node_data(HashNode* node) { destroy_node_data(node, eastl::has_trivial_destructor<Value>()); }

			static void set_value(HashNode* node, typename make_const_reference<Value>::type val, eastl::true_type) 
			{
				MEMCPY( reinterpret_cast<void*>(const_cast<typename drop_const<Value>::type*>(&node->value)), &val, sizeof(Value));
			}
			static void set_value(HashNode* node, typename make_const_reference<Value>::type val, eastl::false_type) 
			{
				::new(reinterpret_cast<void*>(const_cast<typename drop_const<Value>::type*>(&node->value))) Value(val);
			}
			static void set_value(HashNode* node, typename make_const_reference<Value>::type val) { set_value(node, val, eastl::has_trivial_copy<Value>()); }

			iterator insert_hash_node(HashNode* node, HashNode** buckets, size_t buckets_count);

			HashTable();
			HashTable(const HashTable&);
			HashTable& operator = (const HashTable&);
		};

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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::iterator 
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::insert_hash_node( HashNode* node, HashNode** buckets, size_t buckets_count )
		{
			// Calculate hash
			const uint32_t hash_value = m_Hasher(*m_ExtractKey(node->value));
			const uint32_t bucket_idx = hash_value % buckets_count;

			if(buckets[bucket_idx])
			{
				HashNode* stored_node = buckets[bucket_idx];

				while( stored_node->next )
				{
					if( m_Compare(*m_ExtractKey(node->value), *m_ExtractKey(stored_node->value)) )
					{
						node->next = stored_node->next;
						stored_node->next = node;
						return iterator(this, bucket_idx, node);;
					}
					stored_node = stored_node->next;
				} 
				
				// 
				node->next = NULL;
				stored_node->next = node;
			}
			else
			{
				node->next = NULL;
				buckets[bucket_idx] = node;
			}
			return iterator(this, bucket_idx, node);
		} //Insert hash node


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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::rehash( uint32_t bucket_count )
		{
			if( bucket_count > m_NumBuckets )
			{
				HashNode**	new_buckets = m_BucketAllocator.allocate(bucket_count);
				MEMSET(new_buckets, static_cast<int>(NULL), sizeof(HashNode*)*bucket_count);
				if(m_Buckets)
				{
					for( size_t i = 0; i < m_NumBuckets; ++i )
					{
						if(m_Buckets[i])
						{
							HashNode* node = m_Buckets[i];
							do 
							{
								HashNode* next = node->next;
								insert_hash_node(node, new_buckets, bucket_count);
								node = next;
							} while (node);
						}
					}
					m_BucketAllocator.deallocate(m_Buckets);
				}
				m_NumBuckets = bucket_count;
				m_Buckets = new_buckets;
			}
		} //Rehash


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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::reset()
		{
			clear();
			m_LockPolicy.lock();
			m_BucketAllocator.deallocate(m_Buckets);
			m_NumBuckets = 0;
			m_Buckets = NULL;
			RehashPolicy::reset();
			m_LockPolicy.unlock();
		} // reset


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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::clear()
		{
			m_LockPolicy.lock();
			for( size_t i = 0; i < m_NumBuckets; ++i )
			{
				if(m_Buckets[i])
				{
					HashNode* node = m_Buckets[i];
					while( node->next )
					{
						HashNode* next = node->next;
						destroy_node_data(node);
						m_NodeAllocator.deallocate(node);
						node = next;
					}
					destroy_node_data(node);
					m_Buckets[i] = NULL;
					m_NodeAllocator.deallocate(node);
				}
			}
			m_NumElements = 0;
			m_LockPolicy.unlock();
		} // clear


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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::iterator 
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::insert( value_const_reference v )
		{
			m_LockPolicy.lock();
			if( RehashPolicy::rehash_needed( m_NumElements + 1, m_NumBuckets ) )
				rehash( RehashPolicy::get_bucket_count( m_NumElements + 1, m_NumBuckets ) );

			//Create a node
			HashNode* node = m_NodeAllocator.allocate( 1 );
			set_value(node, v);
			iterator it = insert_hash_node(node, m_Buckets, m_NumBuckets);
			m_NumElements++;
			m_LockPolicy.unlock();
			return it;
		} // Insert 


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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::insert( const_iterator begin, const_iterator end )
		{
			for( ; begin != end; ++begin )
				insert( *begin );
		} //Insert range


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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::iterator_range
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::find( key_const_reference_type key )
		{
			if(m_NumElements == 0)
				return iterator_range(end(),end());
			// Get da bucket number
			const uint32_t bucket_idx = m_Hasher( key ) % m_NumBuckets;

			
			if( m_Buckets[bucket_idx] )
			{
				HashNode* node = m_Buckets[bucket_idx];
				
				while( node )
				{
					if( m_Compare( *m_ExtractKey( node->value ), key ) )
					{
						iterator first ( this, bucket_idx, node );

						while ( node->next )
						{
							node = node->next;

							if( !m_Compare( *m_ExtractKey( node->value ), key ) )
								return iterator_range( first, iterator ( this, bucket_idx, node ) );
						}

						iterator last ( this, bucket_idx, node );

						return iterator_range(first, ++last);
					}
					node = node->next;
				}
			}

			return iterator_range(end(), end());
		} // find 


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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::const_iterator_range 
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::find( key_const_reference_type key ) const
		{
			// Get da bucket number
			if(m_NumElements == 0)
				return const_iterator_range(end(),end());
			const uint32_t bucket_idx = m_Hasher( key ) % m_NumBuckets;

			if( m_Buckets[bucket_idx] )
			{
				HashNode* node = m_Buckets[bucket_idx];

				while( node )
				{
					if( m_Compare( *m_ExtractKey( node->value ), key ) )
					{
						const_iterator first ( this, bucket_idx, node );

						while ( node->next )
						{
							node = node->next;

							if( !m_Compare( *m_ExtractKey( node->value ), key ) )
								return const_iterator_range( first, iterator ( this, bucket_idx, node ) );
						}

						const_iterator last ( this, bucket_idx, node );

						return const_iterator_range(first, ++last);
					}
					node = node->next;
				}
			}

			return const_iterator_range(end(), end());
		} // Find const


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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::iterator 
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::find_first( key_const_reference_type key )
		{
			if(m_NumElements == 0)
				return end();

			const uint32_t bucket_idx = m_Hasher( key ) % m_NumBuckets;

			if( m_Buckets[bucket_idx] )
			{
				HashNode* node = m_Buckets[bucket_idx];

				while( node )
				{
					if( m_Compare( *m_ExtractKey( node->value ), key ) )
					{
						return iterator( this, bucket_idx, node );
					}
					node = node->next;
				}
			}
			return end();
		} // Find first of

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
		typename HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::const_iterator 
		HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::find_first( key_const_reference_type key ) const
		{
			if(m_NumElements == 0)
				return end();

			const uint32_t bucket_idx = m_Hasher( key ) % m_NumBuckets;

			if( m_Buckets[bucket_idx] )
			{
				HashNode* node = m_Buckets[bucket_idx];

				while( node )
				{
					if( m_Compare( *m_ExtractKey( node->value ), key ) )
					{
						return const_iterator( this, bucket_idx, node );
					}
					node = node->next;
				}
			}
			return end();
		} // find_first  const

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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::erase( const iterator& it )
		{
			if( m_NumElements && it != end() )
			{
				m_LockPolicy.lock();
				const uint32_t bucket_idx = m_Hasher( *m_ExtractKey( *it )) % m_NumBuckets;

				HashNode* node = m_Buckets[bucket_idx];
				HashNode* prev = NULL;

				while( node )
				{
					if( node == it.m_Node )
					{
						if( prev )
							prev->next = node->next;
						else
							m_Buckets[bucket_idx] = node->next;

						destroy_node_data(node);
						m_NodeAllocator.deallocate(node);

						m_NumElements--;
						break;
					}
					prev = node;
					node = node->next;
				}
				
				m_LockPolicy.unlock();
			}
		} // erase

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
		void HashTable<Key, Value, Hash, Compare, ExtractKey, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy>::erase( const iterator& first, const iterator& last )
		{
			m_LockPolicy.lock();
			for( iterator it = first; it != last;  )
			{
				iterator next = it; ++next;
				if( m_NumElements && it != end() )
				{
					const uint32_t bucket_idx = m_Hasher( *m_ExtractKey( *it )) % m_NumBuckets;

					HashNode* node = m_Buckets[bucket_idx];
					HashNode* prev = NULL;

					while( node )
					{
						if( node == it.m_Node )
						{
							if( prev )
								prev->next = node->next;
							else
								m_Buckets[bucket_idx] = node->next;

							destroy_node_data(node);
							m_NodeAllocator.deallocate(node);

							m_NumElements--;
							break;
						}
						prev = node;
						node = node->next;
					}
				}
				it = next;
			}
			m_LockPolicy.unlock();
		} // erase range
		//!\endcond
	} // namespace details
} // namespace containers


#endif // hashtable_h__
