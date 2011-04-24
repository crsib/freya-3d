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

	//!
	template
	<
		typename Key,
		typename T, 
		class Hash = hash<typename constant<Key>::type>,
		class RehashPolicy = policies::rehash::PrimeNumber,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class ThreadSafetyPolicy = policies::multithreading::NoLock
	>
	class hash_map
	{
	public:
		//!
		typedef typename constant<Key>::type              key_type;
		//!
		typedef T                                         mapped_type;
		//!
		typedef pair<typename constant<Key>::type, T>     value_type;
		//!
		typedef Hash                                      hasher_type;
		//!
		typedef equal< key_type >                         compare_type;
	private:
		hash_map(const hash_map& );
		hash_map& operator = (const hash_map&);
		struct pair_extractor { key_type*	operator()(const value_type& p) const  { return &p.first; } };
		typedef details::HashTable
			< key_type, value_type, hasher_type, compare_type,
			  pair_extractor, MemoryAllocationPolicy, ThreadSafetyPolicy, RehashPolicy > hash_table_t;
		hash_table_t		m_Implementation;
	public:
		typedef typename hash_table_t::iterator			iterator;
		typedef typename hash_table_t::const_iterator	const_iterator;
		
		//!
		hash_map( float load_factor = 0.75 ) : m_Implementation(0.75) {}	
		//!
		iterator	begin() { return m_Implementation.begin(); }
		//!
		iterator	end()   { return m_Implementation.end(); }
		//!
		const_iterator begin() const { return m_Implementation.begin(); }
		//! 
		const_iterator end() const { return m_Implementation.end(); } 
		//!
		bool		empty() const { return m_Implementation.get_elements_count() == 0; }
		//!
		size_t		size() const { return m_Implementation.get_elements_count(); }
		//!
		void		clear() const { return m_Implementation.clear(); }
		//! 
		void		reset() const { return m_Implementation.reset(); }
		//!
		mapped_type&	operator [] (typename const_reference<key_type>::type key )
		{
			iterator it = m_Implementation.find_first(key);
			if( it != m_Implementation.end() )
				return it->second;

			value_type val(key, mapped_type());
			return m_Implementation.insert(val)->second;
		}
		//!
		iterator    find( typename const_reference<key_type>::type key )
		{ return m_Implementation.find_first(key); }
		//!
		const_iterator    find( typename const_reference<key_type>::type key ) const
		{ return m_Implementation.find_first(key); }
		//!
		pair<iterator, bool> insert( typename const_reference<value_type>::type value )
		{
			iterator it = m_Implementation.find_first(value.first);
			if( it != m_Implementation.end() )
				return make_pair(it, false);
			else
				return make_pair(m_Implementation.insert(value),true);
		}
		//!
		template< class InputIterator >
		void	insert( InputIterator first, InputIterator last )
		{
			for( ; first != last; ++first )
				insert(*first);
		}
		//! 
		void	erase( typename const_reference<key_type>::type key )
		{ m_Implementation.erase( m_Implementation.find_first(key) ); }
		//!
		void	erase( const iterator& position )
		{ m_Implementation.erase(position); }
		//!
		void	erase( const iterator& first, const iterator& last )
		{ m_Implementation.erase(first,last); }
	};
} // namespace containers

#endif // hash_map_h__