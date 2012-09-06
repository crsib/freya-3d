/* File		: containers/details/vector_impl.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */
#ifndef Containers_vector_impl_h__
#define Containers_vector_impl_h__

#include <memory.h>
#include "integer.h"

#ifndef Containers_vector_h__
#	include "containers/vector.h"
#endif //vector_h_

#ifdef FREYA_USE_EASTL_TYPE_TRAITS
#	include "EASTL/type_traits.h"
#endif // FREYA_USE_EASTL_TYPE_TRAITS

#include "core/memory/MemoryDebug.h"

namespace containers
{
	namespace details
	{
		//Destructor helpers
		template<typename T>
		inline
		void	__vector_impl_destructor_helper(T* first, T* last, eastl::true_type)
		{
			//Empty
		}

		template<typename T>
		inline
		void	__vector_impl_destructor_helper(T* first, T* last, eastl::false_type)
		{
			for(;first != last; ++first)
				(*first).~T();
		}

		//Copying vector
		template<typename I, typename T>
		inline
		T*	__vector_impl_copy_unintialized_helper(I* first, I* last, T* result, eastl::true_type)
		{
			MEMCPY(result, first, (last - first) * sizeof(T));
			return result + (last - first);
		}

		template<typename I, typename T>
		inline 
		T* __vector_impl_copy_unintialized_helper(I* first, I* last, T* result, eastl::false_type)
		{
			for( ; first != last; ++first, ++result )
				::new(result) T(*first);
			return result;
		}

		template<typename T>
		inline
			T*	__vector_impl_copy_unintialized_helper( T* result, typename make_const_reference<T>::type obj, eastl::true_type)
		{
			MEMCPY(result, &obj, sizeof(T));
			return result + 1;
		}

		template<typename T>
		inline 
			T* __vector_impl_copy_unintialized_helper(T* result, typename make_const_reference<T>::type obj, eastl::false_type)
		{
			::new(result) T(obj);
			return result + 1;
		}

		template<typename I, typename T>
		inline
			T*	__vector_impl_copy_helper(I* first, I* last, T* result, eastl::true_type)
		{
			MEMMOVE(result, first, (last - first) * sizeof(T));
			return result + (last - first);
		}

		template<typename I, typename T>
		inline 
			T* __vector_impl_copy_helper(I* first, I* last, T* result, eastl::false_type)
		{
			for( ; first != last; ++first, ++result )
				*result = *first;
			return result;
		}

		template<typename T>
		inline
			T*	__vector_impl_copy_helper( T* result, typename make_const_reference<T>::type obj, eastl::true_type)
		{
			MEMMOVE(result, &obj, sizeof(T));
			return result + 1;
		}

		template<typename T>
		inline 
			T* __vector_impl_copy_helper(T* result, typename make_const_reference<T>::type obj, eastl::false_type)
		{
			*result = *obj;
			return result + 1;
		}

		template<typename I, typename T>
		inline
			T*	__vector_impl_copy_backward_helper(I* first, I* last, T* result, eastl::true_type)
		{
			MEMMOVE(result, first, (last - first) * sizeof(T));
			return result + (last - first);
		}

		template<typename I, typename T>
		inline 
			T* __vector_impl_copy_backward_helper(I* first, I* last, T* result, eastl::false_type)
		{
			const size_t dist = last - first;
			result += dist;
			while( last != first )
				*(--result) = *(--last);
			return result + dist;
		}

		template<typename T>
		inline
			T*	__vector_impl_uninitialized_fill_helper( T* result, typename make_const_reference<T>::type obj, size_t n, eastl::true_type)
		{
			for(size_t i = 0; i < n; ++i, ++result)
				*result = obj;
			return result;
		}

		template<typename T>
		inline 
			T* __vector_impl_uninitialized_fill_helper(T* result, typename make_const_reference<T>::type obj, size_t n, eastl::false_type)
		{
			for(size_t i = 0; i < n; ++i)
				::new(result++) T(obj);
			return result;
		}

		template<typename T>
		inline
			T*	__vector_impl_fill_helper( T* result, typename make_const_reference<T>::type obj, size_t n)
		{
			for(size_t i = 0; i < n; ++i, ++result)
				*result = obj;
			return result;
		}
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	vector<T,MAP,LP,SRP>::vector(const_iterator _begin, const_iterator _end) 
		: m_AllocatedCount(SRP::get_vector_size(_end - _begin, 0)), m_Begin(MAP<T>::allocate(m_AllocatedCount))
	{
		m_End = details::__vector_impl_copy_unintialized_helper(_begin,_end, m_Begin,eastl::has_trivial_copy<T>());
	}

	template<typename Iter, template<class> class MAP, class LP, class SRP>
	vector<Iter,MAP, LP, SRP>::~vector() 
	{
		if( m_Begin != m_End )
			details::__vector_impl_destructor_helper(m_Begin, m_End, eastl::has_trivial_destructor<Iter>());
		// deallocate is expected to act as free
		deallocate( m_Begin );
		m_Begin = m_End = NULL;
		m_AllocatedCount = 0;
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	void vector<T,MAP, LP, SRP>::reset() 
	{
		if( m_Begin != m_End )
			details::__vector_impl_destructor_helper(m_Begin, m_End, eastl::has_trivial_destructor<T>());
		deallocate( m_Begin );
		m_Begin = m_End = NULL;
		m_AllocatedCount = 0;
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	void vector<T,MAP, LP, SRP>::clear() 
	{
		if( m_Begin != m_End )
			details::__vector_impl_destructor_helper(m_Begin, m_End, eastl::has_trivial_destructor<T>());
		m_End = m_Begin;
	}

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
		class LockPolicy,
		class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator first, iterator last )
	{
		if(m_Begin == m_End || first >= m_End || first == last) // Nothing to do
			return;
		LockPolicy::lock();
		// Correct iterators
		if(first < m_Begin)
			first = m_Begin;
		if(last > m_End)
			last = m_End;

		// Move the rest
		T* ptr;
		if(last < m_End)
			ptr = details::__vector_impl_copy_helper(last, m_End, first, eastl::has_trivial_assign<T>());
		else
			ptr = first;
		
		details::__vector_impl_destructor_helper(ptr, m_End, eastl::has_trivial_destructor<T>());

		m_End = ptr;

		LockPolicy::unlock();
	} // void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator first, iterator last )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator position )
	{
		erase(position,position + 1);
	} // void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator position )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, const_iterator first, const_iterator last )
	{
		FREYA_SUPPORT_ASSERT(last >= first, "Incorrect insertion sequence");
		size_t elem_count = last - first;

		if(elem_count == 0) //Nothing to insert?
			return; //Boil out
		LockPolicy::lock();

		if(!m_Begin) // Whoops, no memory is allocated
		{
			m_AllocatedCount = StorageResizePolicy::get_vector_size(elem_count, 0);
			m_Begin = MemoryAllocationPolicy<T>::allocate(m_AllocatedCount);
			//All the space is unitialized...
			m_End = details::__vector_impl_copy_unintialized_helper( first, last, m_Begin, eastl::has_trivial_copy<T>());
		}
		else if( (m_End - m_Begin) > static_cast<ptrdiff_t>(m_AllocatedCount - elem_count) ) //Reallocation needed
		{
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = StorageResizePolicy::get_vector_size(current_size + elem_count, m_AllocatedCount);

			T*	new_memory_ptr = MemoryAllocationPolicy<T>::allocate(new_size);
			if(position <= m_Begin) // Copy [first, last), then [m_Begin, m_End)
			{
				details::__vector_impl_copy_unintialized_helper( first, last, new_memory_ptr,  eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr + elem_count, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End) // [m_Begin, m_End) -> [first, last)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(first, last, m_End, eastl::has_trivial_copy<T>());
			}
			else //Worst case [m_Begin, postion) -> [first, last) -> [position, m_End)
			{
				T* mem = details::__vector_impl_copy_unintialized_helper(m_Begin, position, new_memory_ptr, eastl::has_trivial_copy<T>());
				mem = details::__vector_impl_copy_unintialized_helper( first, last, mem, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(position, m_End, mem, eastl::has_trivial_copy<T>());
			}
			// Clean up the mess
			details::__vector_impl_destructor_helper(m_Begin, m_Begin + current_size, eastl::has_trivial_destructor<T>());
			deallocate(m_Begin);
			m_AllocatedCount = new_size;
			m_Begin = new_memory_ptr;
		}
		else //We have enough memory
		{
			if(position >= m_End) //Copy past the end of vector, easy case (and damn fast)
			{
				m_End = details::__vector_impl_copy_unintialized_helper( first, last, m_End, eastl::has_trivial_copy<T>());
			}
			else
			{
				const size_t		tail = m_End - position;
				const ptrdiff_t		rest = m_End - (position + elem_count);
				const size_t		r_plus =  (rest > 0 ? rest : 0);
				const size_t		r_minus = (rest < 0 ? -rest : 0);
				const size_t		unit_tail_elems_copy = tail - r_plus;

				//Make the unit copy of the vector tail
				T* ptr = details::__vector_impl_copy_unintialized_helper(m_End - unit_tail_elems_copy, m_End, m_End + r_minus, eastl::has_trivial_copy<T>());
				//Make the normal copy of the vector tail (if needed)
				if(r_plus)
					details::__vector_impl_copy_backward_helper( position, position + r_plus, m_End - r_plus, eastl::has_trivial_assign<T>() );
				if(r_minus)
					details::__vector_impl_copy_unintialized_helper(last - r_minus, last, m_End, eastl::has_trivial_copy<T>());
				//Make the normal copy of required part of input range
				details::__vector_impl_copy_backward_helper(first, last - r_minus, position, eastl::has_trivial_assign<T>());

				m_End = ptr;
			}
		}
		LockPolicy::unlock();
	} //void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, const_iterator first, const_iterator last )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, size_t n, constant_reference obj )
	{
		if(n == 0)
			return;
		LockPolicy::lock();
		if(!m_Begin)
		{
			m_AllocatedCount = StorageResizePolicy::get_vector_size(n, 0);
			m_Begin = MemoryAllocationPolicy<T>::allocate(m_AllocatedCount);
			m_End = details::__vector_impl_uninitialized_fill_helper(m_Begin, obj, n, eastl::has_trivial_copy<T>());
		}
		else if( (m_End - m_Begin) > static_cast<ptrdiff_t>(m_AllocatedCount - n) )
		{
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = StorageResizePolicy::get_vector_size(current_size + n, m_AllocatedCount);
			T*	new_memory_ptr = MemoryAllocationPolicy<T>::allocate(new_size);
			if(position <= m_Begin)
			{
				details::__vector_impl_uninitialized_fill_helper(new_memory_ptr, obj, n, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr + n, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_uninitialized_fill_helper(m_End, obj, n, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				T* mem = details::__vector_impl_copy_unintialized_helper(m_Begin, position, new_memory_ptr, eastl::has_trivial_copy<T>());
				mem = details::__vector_impl_uninitialized_fill_helper(mem, obj, n, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(position, m_End, mem, eastl::has_trivial_copy<T>());
			}
			details::__vector_impl_destructor_helper(m_Begin, m_Begin + current_size, eastl::has_trivial_destructor<T>());
			deallocate(m_Begin);
			m_AllocatedCount = new_size;
			m_Begin = new_memory_ptr;
		}
		else
		{
			if(position >= m_End) //Fill past the end of vector, easy case (and damn fast)
			{
				m_End = details::__vector_impl_uninitialized_fill_helper( m_End, obj, n, eastl::has_trivial_copy<T>() );
			}
			else
			{
				const size_t		tail = m_End - position;
				const ptrdiff_t		rest = m_End - (position + n);
				const size_t		r_plus =  (rest > 0 ? rest : 0);
				const size_t		r_minus = (rest < 0 ? -rest : 0);
				const size_t		unit_tail_elems_copy = tail - r_plus;

				//Make the unit copy of the vector tail
				T* ptr = details::__vector_impl_copy_unintialized_helper(m_End - unit_tail_elems_copy, m_End, m_End + r_minus, eastl::has_trivial_copy<T>());
				//Make the normal copy of the vector tail (if needed)
				if(r_plus)
					details::__vector_impl_copy_backward_helper( position, position + r_plus, m_End - r_plus, eastl::has_trivial_assign<T>() );
				if(r_minus)
					details::__vector_impl_uninitialized_fill_helper(m_End, obj, r_minus, eastl::has_trivial_copy<T>());
				//Make the normal copy of required part of input range
				details::__vector_impl_fill_helper(position, obj, n - r_minus);

				m_End = ptr;
			}
		}
		LockPolicy::unlock();
	} //void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, size_t n, constant_refernce obj )


	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
		class LockPolicy,
		class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, constant_reference obj )
	{
		insert(position, &obj, &obj + 1);
	} // void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, constant_refernce obj )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::pop_back()
	{
		LockPolicy::lock();
		if(m_Begin && m_Begin < m_End)
		{
			details::__vector_impl_destructor_helper(m_End - 1, m_End, eastl::has_trivial_destructor<T>());
			--m_End;
		}
		LockPolicy::unlock();
	}

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
		class LockPolicy,
		class StorageResizePolicy
		>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::push_back( constant_reference obj )
	{
		LockPolicy::lock();
		if(!m_Begin)
		{
			m_AllocatedCount = StorageResizePolicy::get_vector_size(1, 0);
			m_Begin = MemoryAllocationPolicy<T>::allocate(m_AllocatedCount);
			m_End = m_Begin;
		}
		else if( (m_End - m_Begin) == static_cast<ptrdiff_t>(m_AllocatedCount) )
		{
			//Wtf, copying...
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = StorageResizePolicy::get_vector_size(current_size + 1, m_AllocatedCount);
			T*	new_memory_ptr = MemoryAllocationPolicy<T>::allocate(new_size);
			m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
			details::__vector_impl_destructor_helper(m_Begin, m_Begin + current_size, eastl::has_trivial_destructor<T>());
			MemoryAllocationPolicy<T>::deallocate(m_Begin);
			m_Begin = new_memory_ptr;
			m_AllocatedCount = new_size;
		}

		m_End = details::__vector_impl_copy_unintialized_helper(m_End, obj, eastl::has_trivial_copy<T>());

		LockPolicy::unlock();
	}

	template
	<
		typename T,
		template<class> class MemoryAllocationPolicy,
		class LockPolicy,
		class StorageResizePolicy
	>
	void vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::reserve( size_t count )
	{
		if(m_Begin == NULL) //Trivial case
		{
			m_AllocatedCount = StorageResizePolicy::get_vector_size(count, 0);
			m_Begin = m_End = MemoryAllocationPolicy<T>::allocate(m_AllocatedCount);
		}
		else if( count > m_AllocatedCount )
		{
			if(m_Begin == m_End)
			{
				m_AllocatedCount = StorageResizePolicy::get_vector_size(count, 0);
				m_End = MemoryAllocationPolicy<T>::allocate(m_AllocatedCount);
				MemoryAllocationPolicy<T>::deallocate(m_Begin);
				m_Begin = m_End;
			}
			else
			{
				const size_t current_size = m_End - m_Begin;
				const size_t new_size = StorageResizePolicy::get_vector_size(count,m_AllocatedCount);
				T* memptr = MemoryAllocationPolicy<T>::allocate(new_size);

				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, memptr,eastl::has_trivial_copy<T>());
				details::__vector_impl_destructor_helper(m_Begin, m_Begin + current_size, eastl::has_trivial_destructor<T>());
				m_AllocatedCount = count;
				m_Begin = memptr;
			}
		}
	}
}

#endif // vector_impl_h__