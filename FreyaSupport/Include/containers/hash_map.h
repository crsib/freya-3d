/* File		: containers/iterator.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_hash_map_h__
#define Containers_hash_map_h__

#include "FreyaSupportInternal.h"
#include "containers/details/hashtable.h"
#include "containers/utils.h"

namespace containers
{
	namespace policies
	{
		namespace memory { template<class> class FreyaAllocator; }
		namespace multithreading { class NoLock; }
		namespace rehash { class PrimeNumber; }
	}

	//! Container, implementing associative array semantics
	/*!
	 * hash_map is a container, which implements the semantics of associative array.
	 * It uses sparse array (a.k.a hash table) as an internal implementation 
	 * to provide a very efficient way of searching entries by the value of the key.
	 * hash_map guaranties, that a key is unique across the container. To store multiple
	 * object with the same key consider using containers::hash_multimap. Key and value should be copy constructible types.
	 * Please note, that current implementation does not allow to reduce the number of buckets upon erase operation, as it
	 * assumes, that associative containers more often are required for efficient insert/lookup operation and erasing is 
	 * rare. In order, to restore the hash_map to initial state, please use reset() method.
	 * <BR><BR>
	 * The hash_map is controlled by the following policies:
	 * - MemoryAllocationPolicy controls, which kind of memory management routines will be used to allocate storage space for the hash_map.
	 *    vector supports all policies in \ref grpContainers_Policies_Memory
	 * - LockPolicy controls the thread safety properties. Selected policy will control the thread safety of operations modifying hash_map storage space.
	 *    Policy is not applied to access/modification of elements, contained inside the vector. 
	 *    Please, remember that modifying a hash table using insert/erase/operator [] will 
	 *    invalidate all previously obtained iterators. All policies in \ref grpContainers_Policies_MultiThreading are supported
	 * - RehashPolicy controls, when to rehash the hash table in order to improve lookup performance. All policies in \ref grpContainers_Policies_Rehash are supported
	 * \tparam Key is a type of key object. Please note, that key are always stored as constant objects
	 * \tparam T is a type of mapped value
	 * \tparam Hash is an unary functor, used to retrieve the hash value of the key
	 * \tparam Equal is a binary predicate, used to compare keys for equality
	 * \tparam RehashPolicy controls the rehashing policy. Default is the policy, that uses prime numbers for retrieving the new size of table.
	 * \tparam MemoryAllocationPolicy controls the memory allocation policy. Default is the allocator, based on Freya internal memory management functions
	 * \tparam LockPolicy controls the thread safety of the vector. Default is not thread safe hash_map
	 */
	//! \ingroup grpContainers
	template
	<
		typename Key,
		typename T, 
		class Hash = hash<typename constant<Key>::type>,
		class Equal = equal<typename constant<Key>::type>,
		class RehashPolicy = policies::rehash::PrimeNumber,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class ThreadSafetyPolicy = policies::multithreading::NoLock
	>
	class hash_map
	{
	public:
		//! Type of the key. Always constant
		typedef typename constant<Key>::type              key_type;
		//! Type of the mapped value
		typedef T                                         mapped_type;
		//! Type of the values, stored in the container
		typedef pair<typename constant<Key>::type, T>     value_type;
		//! Type of hasher
		typedef Hash                                      hasher_type;
		//! Type of equlity predicate
		typedef Equal									  compare_type;
	private:
		hash_map(const hash_map& );
		hash_map& operator = (const hash_map&);
		struct pair_extractor { key_type*	operator()(const value_type& p) const  { return &p.first; } };
		typedef details::HashTable
			< key_type, value_type, hasher_type, compare_type,
			  pair_extractor, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy > hash_table_t;
		hash_table_t		m_Implementation;
	public:
		//! Forward access iterator
		typedef typename hash_table_t::iterator			iterator;
		//! Constant forward access iterator
		typedef typename hash_table_t::const_iterator	const_iterator;
		
		//! Default construct. Allows to specify the load factor of the hash table
		hash_map( float load_factor = 0.75 ) : m_Implementation(0.75) {}	
		//! Retrieve the iterator to the first stored element
		iterator	begin() { return m_Implementation.begin(); }
		//! Retrieve the iterator to the one-past-end element
		iterator	end()   { return m_Implementation.end(); }
		//! Retrieve the iterator to the first stored element (const version)
		const_iterator begin() const { return m_Implementation.begin(); }
		//! Retrieve the iterator to the one-past-end element (const version)
		const_iterator end() const { return m_Implementation.end(); } 
		//! Check, if the container is empty
		bool		empty() const { return m_Implementation.get_elements_count() == 0; }
		//! Get the number of elements stored in the container
		size_t		size() const { return m_Implementation.get_elements_count(); }
		//! Destroy all the elements within the container without deallocating the buckets structure
		void		clear() const { return m_Implementation.clear(); }
		//! Destroy all the elements within the container and deallocates the buckets structure
		void		reset() const { return m_Implementation.reset(); }
		//! Retrieve an element inside the container. If element does not exists - create it
		mapped_type&	operator [] (typename const_reference<key_type>::type key )
		{
			iterator it = m_Implementation.find_first(key);
			if( it != m_Implementation.end() )
				return it->second;

			value_type val(key, mapped_type());
			return m_Implementation.insert(val)->second;
		}
		//! Search for the element within the container
		iterator    find( typename const_reference<key_type>::type key )
		{ return m_Implementation.find_first(key); }
		//! Search for the element within the container (const version)
		const_iterator    find( typename const_reference<key_type>::type key ) const
		{ return m_Implementation.find_first(key); }
		//! Insert an element into the container
		/*! 
		 * Check, if the container does not already contain the key and insert an element.
		 * If key already exists, do nothing.
		 * \return iterator to the newly inserted or to the already contained element in first, true in second
		 *          if the insertion has actually ocurred, false otherwise
		 */
		pair<iterator, bool> insert( typename const_reference<value_type>::type value )
		{
			iterator it = m_Implementation.find_first(value.first);
			if( it != m_Implementation.end() )
				return make_pair(it, false);
			else
				return make_pair(m_Implementation.insert(value),true);
		}
		//! Insert range of elements into the container
		template< class InputIterator >
		void	insert( InputIterator first, InputIterator last )
		{
			for( ; first != last; ++first )
				insert(*first);
		}
		//! Erase an element by its key
		void	erase( typename const_reference<key_type>::type key )
		{ m_Implementation.erase( m_Implementation.find_first(key) ); }
		//! Erase an element at iterator position
		void	erase( const iterator& position )
		{ m_Implementation.erase(position); }
		//! Erase range of elements
		void	erase( const iterator& first, const iterator& last )
		{ m_Implementation.erase(first,last); }
	};


} // namespace containers

#endif // hash_map_h__