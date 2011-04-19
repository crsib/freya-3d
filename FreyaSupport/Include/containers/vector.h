/* File		: containers/vector.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef vector_h__
#define vector_h__

#include "containers/policies/Policies.h"
#include "containers/type_utils.h"

namespace containers
{
	template
	<
		typename T,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class LockPolicy = policies::multithreading::NoLock,
		class StorageResizePolicy = policies::storage::Exponential
	>
	class vector 
		: private MemoryAllocationPolicy<T>, private LockPolicy, private StorageResizePolicy
	{
	public:
		//! Vector iterator type
		typedef T*		iterator;
		//! Vector const iterator type
		typedef typename const_pointer<T>::type const_iterator;
		//! Vector base type
		typedef T		type;
		//! Reference to base type
		typedef T&		reference;
		//! Constant reference type
		typedef typename const_reference<T>::type constant_refernce;
		//! Reverse iterator implementation
		/*!
		 * This a wrapper around an vector iterator, which allows reverse iteration through the container
		 * It emulates the normal iterator behavior (a pointer, in this case)
		 */
		template<typename T>
		class reverse_iterator_impl
		{
			template<typename U> 
			friend class reverse_iterator_impl;
			T*	m_Ptr;
			reverse_iterator_impl () {}
		public:
			explicit reverse_iterator_impl(T* ptr) { m_Ptr = ptr; }
			reverse_iterator_impl(const reverse_iterator_impl& other) : m_Ptr(other.m_Ptr) {}
			//Requires implicit cast
			template<typename U>
			reverse_iterator_impl(const reverse_iterator_impl<U>& other) : m_Ptr(other.m_Ptr) {}
			reverse_iterator_impl& operator = (const reverse_iterator_impl& rhs) { m_Ptr = rhs.m_Ptr; return *this;}

			reverse_iterator_impl& operator ++ () { --m_Ptr; return *this; }
			reverse_iterator_impl  operator ++ (int) { return reverse_iterator_impl(m_Ptr--); }

			reverse_iterator_impl& operator -- () { ++m_Ptr; return *this; }
			reverse_iterator_impl  operator -- (int) { return reverse_iterator_impl(m_Ptr++); }

			reverse_iterator_impl  operator + (size_t offset) const { return reverse_iterator_impl(m_Ptr - offset); }
			reverse_iterator_impl  operator - (size_t offset) const { return reverse_iterator_impl(m_Ptr + offset); }
			ptrdiff_t  operator - (reverse_iterator_impl const& offset) const { return reverse_iterator_impl(offset.m_Ptr - m_Ptr); }

			reverse_iterator_impl&  operator += (size_t offset) { return *this = reverse_iterator_impl(m_Ptr - offset); }
			reverse_iterator_impl&  operator -= (size_t offset) { return *this = reverse_iterator_impl(m_Ptr + offset); }

			T&	operator * () { return *m_Ptr; }
			typename const_reference<T>::type
				operator * () const { return *m_Ptr; }
			T*	operator -> () { return m_Ptr; }
			typename const_pointer<T>::type
				operator -> () const { return m_Ptr; }

			friend
				inline bool operator == (const reverse_iterator_impl& lhs, const reverse_iterator_impl& rhs) { return lhs.m_Ptr == rhs.m_Ptr; }
			friend
				inline bool operator != (const reverse_iterator_impl& lhs, const reverse_iterator_impl& rhs) { return lhs.m_Ptr != rhs.m_Ptr; }

		};
		//! Reverse iterator
		typedef reverse_iterator_impl<T>	reverse_iterator;
		//! Constant reverse iterator
		typedef reverse_iterator_impl<typename constant<T>::type> const_reverse_iterator;
		//! Destroy a vector
		~vector();
		//! Constructs an empty vector
		vector() : m_AllocatedCount(0),  m_Begin(NULL), m_End(NULL) {}
		//! Construct an empty vector with reserved storage
		vector(size_t reserve_count) 
			: m_AllocatedCount(get_vector_size(reserve_count, 0)), m_Begin(allocate(reserve_count)), m_End(m_Begin) {}
		//! Construct a vector initialized with [_begin, _end)
		vector(iterator _begin, iterator _end); 

		//Accessing vector data
		//! Overloaded operator []
		reference	operator [] (size_t idx) 
		{
			FREYA_SUPPORT_ASSERT(m_Begin, "Empty vector");
			FREYA_SUPPORT_ASSERT(idx < static_cast<size_t>(m_End - m_Begin), "Out of range");
			return *(m_Begin + idx);
		}
		//! Overloaded operator [] (const version)
		constant_refernce operator [] (size_t idx) const
		{
			FREYA_SUPPORT_ASSERT(m_Begin, "Empty vector");
			FREYA_SUPPORT_ASSERT(idx < static_cast<size_t>(m_End - m_Begin), "Out of range");
			return *(m_Begin + idx);
		}

		//! 
		iterator		begin() { return m_Begin; }
		//! 
		iterator		end() { return m_End; }
		//!
		const_iterator	begin() const { return m_Begin; }
		//!
		const_iterator  end() const { return m_End; }
		//! 
		reverse_iterator rbegin() { FREYA_SUPPORT_ASSERT(m_End,"Empty vector"); return reverse_iterator(m_End - 1); }
		//!
		reverse_iterator rend() { FREYA_SUPPORT_ASSERT(m_Begin,"Empty vector"); return reverse_iterator(m_Begin - 1);}
		//! 
		const_reverse_iterator rbegin() const { FREYA_SUPPORT_ASSERT(m_End,"Empty vector"); return const_reverse_iterator(m_End - 1); }
		//!
		const_reverse_iterator rend() const { FREYA_SUPPORT_ASSERT(m_Begin,"Empty vector"); return const_reverse_iterator(m_Begin - 1);}
		//!
		reference			   front() { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *m_Begin; }
		//!
		reference			   back()  { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *(m_End-1); }	
		//!
		constant_refernce	   front() const { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *m_Begin; }
		//!
		constant_refernce	   back() const { FREYA_SUPPORT_ASSERT(m_Begin < m_End,"Empty vector"); return *(m_End-1); }	
		//! Get reserved space size
		size_t	capacity() const { return m_AllocatedCount; }
		//! Get reserved space size in bytes
		size_t	storage_size() const { return m_AllocatedCount * sizeof(T); }
		//! Check, if vector is empty
		bool	empty() const { return m_Begin == m_End; }
		//! Get the number of elements in the vector.
		size_t	size() const { return m_End - m_Begin; }

		// Manipulating the vector
		//! Push an item to vector
		void	push_back(constant_refernce	obj);
		//!Pop an item  from the vector
		void	pop_back();

		//! Insert an item into vector
		void	insert(iterator	position, constant_refernce	obj );
		//! Insert n copies of item into vector
		void	insert(iterator	position, size_t n, constant_refernce	obj );
		//! Insert range of items into the vector
		void	insert(iterator	position, const_iterator first, const_iterator last);

		//!
		void	erase( iterator position );
		//!
		void	erase( iterator first, iterator last );
		//! Reset the vector
		/*!
		 * Clean up the memory, used by the vector and delete all vector elements
		 */
		void	reset();
		//! Clear the vector
		/*
		 * Destroy all objects within vector without deallocating memory
		 */
		void	clear();
	private:
		size_t	m_AllocatedCount;
		T*	   m_Begin;
		T*	   m_End;

		//Have no idea, why would someone create a deep copy of an vector itself, 
		//especially considering problem of copying vector with different policies
		vector(const vector& v);
		vector& operator = (const vector& v);
	};
}

#ifndef vector_impl_h__
#include "containers/details/vector_impl.h"
#endif

#endif // vector_h__