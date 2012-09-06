/* File		: containers/vector.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_vector_h__
#define Containers_vector_h__

#include "containers/type_utils.h"
#include "FreyaSupportInternal.h"
#include "containers/iterator.h"
#include <cstddef>

namespace containers
{
	namespace policies
	{
		namespace memory
		{ template<typename T> class FreyaAllocator; }
		namespace multithreading
		{ class NoLock; }
		namespace storage
		{ class Exponential; }
	}

	//! Container, implementing dynamic array semantics
	/*!
	 * vector is a container, which implements the semantics of dynamic array.
	 * It has strictly linear in memory representation and constant time to access it's elements.
	 * On the other hand, inserting/erasing ranges in the vector could lead to expensive
	 * memory copying operations. Current implementation of vector is not an implementation of the C++ STL vector, despite it is very close to it
	 * <BR> <BR>
	 * The vector is controlled by the following policies:
	 * - MemoryAllocationPolicy controls, which kind of memory management routines will be used to allocate storage space for the vector.
	 *    vector supports all policies in \ref grpContainers_Policies_Memory
	 * - LockPolicy controls the thread safety properties. Selected policy will control the thread safety of operations modifying vector storage space.
	 *    Policy is not applied to access/modification of elements, contained inside the vector. All policies in \ref grpContainers_Policies_MultiThreading are supported
	 * - StorageResizePolicy controls the behavior of vector storage space resizing. Please note, that policy only controls vector storage expansion. 
	 *    vector storage will never shrink, unless reset is explicitly called. containers::policies::storage::Exponential, containers::policies::storage::FixedSize 
	 *    and containers::policies::storage::Greedy policies are supported by the implementation
	 * \tparam T denotes the type of the dynamic array created. Please note, that non pod types should provide both copy constructor and operator = in order to function correctly
	 * \tparam MemoryAllocationPolicy controls the memory allocation policy. Default is the allocator, based on Freya internal memory management functions
	 * \tparam LockPolicy controls the thread safety of the vector. Default is not thread safe vector
	 * \tparam StorageResizePolicy controls the storage resize of the vector. Default provides the same behavior, as most of std::vector implementations
	 */
	//! \ingroup grpContainers
	template
	<
		typename Iter,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class LockPolicy = policies::multithreading::NoLock,
		class StorageResizePolicy = policies::storage::Exponential
	>
	class vector 
		: private MemoryAllocationPolicy<Iter>, private LockPolicy, private StorageResizePolicy
	{
	public:
		//! Vector iterator type
		typedef Iter*		iterator;
		//! Vector const iterator type
		typedef typename const_pointer<Iter>::type const_iterator;
		//! Vector base type
		typedef Iter		type;

		typedef Iter        value_type;
		//! Reference to base type
		typedef Iter&		reference;
		//! Constant reference type
		typedef typename make_const_reference<Iter>::type constant_reference;

		typedef typename make_const_reference<Iter>::type const_reference;
		//! size_type
		typedef size_t size_type;
		//! Reverse iterator implementation
		/*!
		 * This is a wrapper around an vector iterator, which allows reverse iteration through the container.
		 * It emulates the normal iterator behavior (a pointer, in this case)
		 * \tparam T denotes the internal type of the iterator
		 */
		template<typename I>
		class reverse_iterator_impl
		{
			template<typename U> 
			friend class reverse_iterator_impl;
			I*	m_Ptr;
			reverse_iterator_impl () {}
		public:
			typedef I type;
			typedef random_access_iterator_tag iterator_type;
			//! Create a reverse iterator starting at ptr
			explicit reverse_iterator_impl(I* ptr) { m_Ptr = ptr; }
			//! Copy constructor, provided for convenience
			reverse_iterator_impl(const reverse_iterator_impl& other) : m_Ptr(other.m_Ptr) {}
			//! Copy constructor, allowing to construct constant iterators from non constant ones
			template<typename U>
			reverse_iterator_impl(const reverse_iterator_impl<U>& other) : m_Ptr(other.m_Ptr) {}
			//! Assignment operator, provided for convenience
			reverse_iterator_impl& operator = (const reverse_iterator_impl& rhs) { m_Ptr = rhs.m_Ptr; return *this;}
			//! Prefix increment operator
			reverse_iterator_impl& operator ++ () { --m_Ptr; return *this; }
			//! Postfix increment operator
			reverse_iterator_impl  operator ++ (int) { return reverse_iterator_impl(m_Ptr--); }
			//! Prefix decrement operator
			reverse_iterator_impl& operator -- () { ++m_Ptr; return *this; }
			//! Postfix decrement operator
			reverse_iterator_impl  operator -- (int) { return reverse_iterator_impl(m_Ptr++); }
			//! Addition operator, to provide random access semantics
			reverse_iterator_impl  operator + (size_t offset) const { return reverse_iterator_impl(m_Ptr - offset); }
			//! Subtraction operator, to provide random access semantics
			reverse_iterator_impl  operator - (size_t offset) const { return reverse_iterator_impl(m_Ptr + offset); }
			//! Subtraction operator for distance calculations
			ptrdiff_t  operator - (reverse_iterator_impl const& offset) const { return reverse_iterator_impl(offset.m_Ptr - m_Ptr); }
			//! Addition operator, to provide random access semantics
			reverse_iterator_impl&  operator += (size_t offset) { return *this = reverse_iterator_impl(m_Ptr - offset); }
			//! Subtraction operator, to provide random access semantics
			reverse_iterator_impl&  operator -= (size_t offset) { return *this = reverse_iterator_impl(m_Ptr + offset); }

			//! Retrieve the reference to the type
			I&	operator * () { return *m_Ptr; }
			//! Retrieve the const reference to the type
			typename make_const_reference<I>::type
				operator * () const { return *m_Ptr; }
			//! Provide pointer semantics
			I*	operator -> () { return m_Ptr; }
			//! Provide const pointer semantics
			typename const_pointer<I>::type
				operator -> () const { return m_Ptr; }
			//! Compare two iterators for equality
			friend
				inline bool operator == (const reverse_iterator_impl& lhs, const reverse_iterator_impl& rhs) { return lhs.m_Ptr == rhs.m_Ptr; }
			//! Compare two iterators for inequality
			friend
				inline bool operator != (const reverse_iterator_impl& lhs, const reverse_iterator_impl& rhs) { return lhs.m_Ptr != rhs.m_Ptr; }

		};
		//! Reverse iterator
		typedef reverse_iterator_impl<Iter>	reverse_iterator;
		//! Constant reverse iterator
		typedef reverse_iterator_impl<typename constant<Iter>::type> const_reverse_iterator;
		//! Destroy a vector
		~vector();
		//! Constructs an empty vector
		vector() : m_AllocatedCount(0),  m_Begin(NULL), m_End(NULL) {}
		//! Construct an empty vector with reserved storage
		vector(size_t reserve_count) 
			: m_AllocatedCount(StorageResizePolicy::get_vector_size(reserve_count, 0)), m_Begin(MemoryAllocationPolicy<Iter>::allocate(reserve_count)), m_End(m_Begin) {}
		//! Construct a vector initialized with [_begin, _end)
		vector(const_iterator _begin, const_iterator _end); 

		//Accessing vector data
		//! Overloaded operator []
		reference	operator [] (size_t idx) 
		{
			FREYA_SUPPORT_ASSERT(m_Begin, "Empty vector");
			FREYA_SUPPORT_ASSERT(idx < static_cast<size_t>(m_End - m_Begin), "Out of range");
			return *(m_Begin + idx);
		}
		//! Overloaded operator [] (const version)
		constant_reference operator [] (size_t idx) const
		{
			FREYA_SUPPORT_ASSERT(m_Begin, "Empty vector");
			FREYA_SUPPORT_ASSERT(idx < static_cast<size_t>(m_End - m_Begin), "Out of range");
			return *(m_Begin + idx);
		}

		//! Returns an iterator referring to the first element in the vector container
		iterator		begin() { return m_Begin; }
		//! Returns an iterator referring to the past-the-end element in the vector container
		iterator		end() { return m_End; }
		//! Returns an iterator referring to the first element in the vector container (const version)
		const_iterator	begin() const { return m_Begin; }
		//! Returns an iterator referring to the past-the-end element in the vector container (const version)
		const_iterator  end() const { return m_End; }
		//! Returns a reverse iterator referring to the last element in the vector container
		reverse_iterator rbegin() { FREYA_SUPPORT_ASSERT(m_End,"Empty vector"); return reverse_iterator(m_End - 1); }
		//! Returns a reverse iterator referring to the before-the-first element in the vector container
		reverse_iterator rend() { FREYA_SUPPORT_ASSERT(m_Begin,"Empty vector"); return reverse_iterator(m_Begin - 1);}
		//! Returns a reverse iterator referring to the before-the-first element in the vector container (const version)
		const_reverse_iterator rbegin() const { FREYA_SUPPORT_ASSERT(m_End,"Empty vector"); return const_reverse_iterator(m_End - 1); }
		//! Returns a reverse iterator referring to the before-the-first element in the vector container (const version)
		const_reverse_iterator rend() const { FREYA_SUPPORT_ASSERT(m_Begin,"Empty vector"); return const_reverse_iterator(m_Begin - 1);}
		//! Return the reference to the first element
		reference			   front() { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *m_Begin; }
		//! Return the reference to the last element
		reference			   back()  { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *(m_End-1); }	
		//! Return constant reference to the first element
		constant_reference	   front() const { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *m_Begin; }
		//! Return constant reverence to the last element
		constant_reference	   back() const { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *(m_End-1); }	
		//! Get reserved space size
		size_t	capacity() const { return m_AllocatedCount; }
		//! Get reserved space size in bytes
		size_t	storage_size() const { return m_AllocatedCount * sizeof(Iter); }
		//! Check, if vector is empty
		bool	empty() const { return m_Begin == m_End; }
		//! Get the number of elements in the vector.
		size_t	size() const { return m_End - m_Begin; }

		// Manipulating the vector
		//! Push an item to vector
		void	push_back(constant_reference	obj);
		//!Pop an item  from the vector
		void	pop_back();

		//! Insert an item into vector
		void	insert(iterator	position, constant_reference	obj );
		//! Insert n copies of item into vector
		void	insert(iterator	position, size_t n, constant_reference	obj );
		//! Insert range of items into the vector
		void	insert(iterator	position, const_iterator first, const_iterator last);

		//! Erase an element at position
		void	erase( iterator position );
		//! Erase [first,last) range of elements 
		void	erase( iterator first, iterator last );

		//! Reset the vector
		/*!
		 * Clean up the memory, used by the vector and delete all vector elements
		 */
		void	reset();

		//! Clear the vector
		/*!
		 * Destroy all objects within the vector without deallocating memory used
		 */
		void	clear();

		//! Reserve the storage space in vector
		void	reserve(size_t count); 

		vector(const vector& v) : m_AllocatedCount(0), m_Begin(NULL), m_End(NULL)
		{
			insert(begin(), v.begin(), v.end());
		}

		vector& operator = (const vector& v)
		{
			clear();
			insert(begin(), v.begin(), v.end());
			return *this;
		}

	private:
		size_t	m_AllocatedCount;
		Iter*	   m_Begin;
		Iter*	   m_End;
	};
}

#ifndef Containers_vector_impl_h__
#include "containers/details/vector_impl.h"
#endif

#endif // vector_h__
