/* File		: containers/hash_set.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_hash_set_h__
#define Containers_hash_set_h__

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

	//! Container, implementing set semantics
	/*!
	 * hash_set is a container, which implements set semantics. It provides fast
	 * insert and lookup operations based on element value 
	 * (unlike containers::hash_map - the value is the key in this case). The value is
	 * always stored as constant object. hash_set guarantees, that every element in the container is unique.
	 * Consider using hash_multiset if you need to store non unique elements. Internally hash_set is implemented as
	 * sparse array.
	 * Please note, that current implementation does not allow to reduce the number of buckets upon erase operation, as it
	 * assumes, that associative containers more often are used to insert/lookup for elements and erase operation is 
	 * rare. In order, to restore the hash_set to initial state, please use reset() method.
	 * <BR><BR>
	 * The hash_set is controlled by the following policies:
	 * - MemoryAllocationPolicy controls, which kind of memory management routines will be used to allocate storage space for the hash_set.
	 *    vector supports all policies in \ref grpContainers_Policies_Memory
	 * - LockPolicy controls the thread safety properties. Selected policy will control the thread safety of operations modifying hash_set storage space.
	 *    Policy is not applied to access/modification of elements, contained inside the vector. 
	 *    Please, remember that modifying a hash table using insert/erase/operator [] will 
	 *    invalidate all previously obtained iterators. All policies in \ref grpContainers_Policies_MultiThreading are supported
	 * - RehashPolicy controls, when to rehash the hash table in order to improve lookup performance. All policies in \ref grpContainers_Policies_Rehash are supported
	 * \tparam T is a type of stored value
	 * \tparam Hash is an unary functor, used to retrieve the hash value the element
	 * \tparam Equal is a binary predicate, used to compare values for equality
	 * \tparam RehashPolicy controls the rehashing policy. Default is the policy, that uses prime numbers for retrieving the new size of table.
	 * \tparam MemoryAllocationPolicy controls the memory allocation policy. Default is the allocator, based on Freya internal memory management functions
	 * \tparam LockPolicy controls the thread safety of the hash_set. Default is not thread safe hash_set
	 * \sa containers::hash_map
	 */
	//! \ingroup grpContainers

	template
	<
		typename T, 
		class Hash = hash<typename constant<T>::type>,
		class Equal = equal<typename constant<T>::type>,
		class RehashPolicy = policies::rehash::PrimeNumber,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class ThreadSafetyPolicy = policies::multithreading::NoLock
	>
	class hash_set
	{
	public:
		//! Type of the values, stored in the container
		typedef typename constant<T>::type                value_type;
		//! Type of hasher
		typedef Hash                                      hasher_type;
		//! Type of equality predicate
		typedef Equal									  compare_type;
	private:
		struct fake_extractor	{ value_type* operator() ( const value_type& p ) { return &p; } };
		typedef details::HashTable
			< value_type, value_type, hasher_type, compare_type,
			fake_extractor, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy > hash_table_t;
		hash_table_t		m_Implementation;

		//hash_set();
		hash_set(const hash_set&);
		hash_set& operator = (const hash_set&);
	public:
		//! Forward access iterator
		typedef typename hash_table_t::iterator			iterator;
		//! Constant forward access iterator
		typedef typename hash_table_t::const_iterator	const_iterator;

		//! Default construct. Allows to specify the load factor of the hash table
		hash_set( float load_factor = 0.75 ) : m_Implementation(0.75) {}	
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
		//! Search for the element within the container
		iterator    find( typename const_reference<value_type>::type key )
		{ return m_Implementation.find_first(key); }
		//! Search for the element within the container (const version)
		const_iterator    find( typename const_reference<value_type>::type key ) const
		{ return m_Implementation.find_first(key); }
		//! Insert an element into the container
		/*! 
		 * Check, if the container does not already contain the key and insert an element.
		 * If key already exists, do nothing.
		 * \return iterator to the newly inserted or to the already contained element in first, true in second
		 *          if the insertion has actually occurred, false otherwise
		 */
		pair<iterator, bool> insert( typename const_reference<value_type>::type value )
		{
			iterator it = m_Implementation.find_first(value);
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
		void	erase( typename const_reference<value_type>::type key )
		{ m_Implementation.erase( m_Implementation.find_first(key) ); }
		//! Erase an element at iterator position
		void	erase( const iterator& position )
		{ m_Implementation.erase(position); }
		//! Erase range of elements
		void	erase( const iterator& first, const iterator& last )
		{ m_Implementation.erase(first,last); }
	}; // class hash_set

	//! Container, implementing set semantics with non unique items
	/*!
	 * hash_set is a container, which implements set semantics with non unique items. It provides fast
	 * insert and lookup operations based on element value 
	 * (unlike containers::hash_multimap - the value is the key in this case). The value is
	 * always stored as constant object.  Internally hash_multiset is implemented as
	 * sparse array.
	 * Please note, that current implementation does not allow to reduce the number of buckets upon erase operation, as it
	 * assumes, that associative containers more often are used to insert/lookup for elements and erase operations are 
	 * rare. In order, to restore the hash_multiset to initial state, please use reset() method.
	 * <BR><BR>
	 * The hash_set is controlled by the following policies:
	 * - MemoryAllocationPolicy controls, which kind of memory management routines will be used to allocate storage space for the hash_muliset.
	 *    vector supports all policies in \ref grpContainers_Policies_Memory
	 * - LockPolicy controls the thread safety properties. Selected policy will control the thread safety of operations modifying hash_multiset storage space.
	 *    Policy is not applied to access/modification of elements, contained inside the vector. 
	 *    Please, remember that modifying a hash table using insert/erase/operator [] will 
	 *    invalidate all previously obtained iterators. All policies in \ref grpContainers_Policies_MultiThreading are supported
	 * - RehashPolicy controls, when to rehash the hash table in order to improve lookup performance. All policies in \ref grpContainers_Policies_Rehash are supported
	 * \tparam T is a type of stored value
	 * \tparam Hash is an unary functor, used to retrieve the hash value the element
	 * \tparam Equal is a binary predicate, used to compare values for equality
	 * \tparam RehashPolicy controls the rehashing policy. Default is the policy, that uses prime numbers for retrieving the new size of table.
	 * \tparam MemoryAllocationPolicy controls the memory allocation policy. Default is the allocator, based on Freya internal memory management functions
	 * \tparam LockPolicy controls the thread safety of the hash_multiset. Default is not thread safe hash_multiset
	 * \sa containers::hash_map, containers::hash_set
	 */
	//! \ingroup grpContainers

	template
	<
		typename T, 
		class Hash = hash<typename constant<T>::type>,
		class Equal = equal<typename constant<T>::type>,
		class RehashPolicy = policies::rehash::PrimeNumber,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class ThreadSafetyPolicy = policies::multithreading::NoLock
	>
	class hash_multiset
	{
	public:
		//! Type of the values, stored in the container
		typedef typename constant<T>::type                value_type;
		//! Type of hasher
		typedef Hash                                      hasher_type;
		//! Type of equality predicate
		typedef Equal									  compare_type;
	private:
		struct fake_extractor	{ value_type* operator() ( const value_type& p ) { return &p; } };
		typedef details::HashTable
			< value_type, value_type, hasher_type, compare_type,
			fake_extractor, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy > hash_table_t;
		hash_table_t		m_Implementation;

		//hash_multiset();
		hash_multiset(const hash_multiset&);
		hash_multiset& operator = (const hash_multiset&);
	public:
		//! Forward access iterator
		typedef typename hash_table_t::iterator			iterator;
		//! Constant forward access iterator
		typedef typename hash_table_t::const_iterator	const_iterator;
		//! Range of iterators
		/*!
		 * Iterator range is basically a pair of operators denoting the
		 * [first,second) range of elements
		 */
		typedef typename hash_table_t::iterator_range	iterator_range;
		//! Constant range of iterators
		//! \sa iterator_range
		typedef typename hash_table_t::const_iterator_range const_iterator_range;
		//! Default construct. Allows to specify the load factor of the hash table
		hash_multiset( float load_factor = 0.75 ) : m_Implementation(0.75) {}	
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
		//! Search for the element within the container
		iterator_range    find( typename const_reference<value_type>::type key )
		{ return m_Implementation.find(key); }
		//! Search for the element within the container (const version)
		const_iterator_range    find( typename const_reference<value_type>::type key ) const
		{ return m_Implementation.find(key); }
		//! Insert an element into the container
		iterator insert( typename const_reference<value_type>::type value )
		{ return m_Implementation.insert(value); }
		//! Insert range of elements into the container
		template< class InputIterator >
		void	insert( InputIterator first, InputIterator last )
		{
			for( ; first != last; ++first )
				insert(*first);
		}
		//! Erase all elements equal to \a key
		void	erase( typename const_reference<value_type>::type key )
		{ m_Implementation.erase( m_Implementation.find(key) ); }
		//! Erase an element at iterator position
		void	erase( const iterator& position )
		{ m_Implementation.erase(position); }
		//! Erase range of elements
		void	erase( const iterator& first, const iterator& last )
		{ m_Implementation.erase(first,last); }
		//! Erase range of elements
		void	erase( const iterator_range& range ) 
		{ m_Implementation.erase(range); }
	}; // class hash_set
} // namespace containers

#endif // hash_set_h__