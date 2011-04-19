/* File		: containers/details/vector_impl.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */
#ifndef vector_impl_h__
#define vector_impl_h__

#include "containers/policies/Policies.h"

#ifndef vector_h__
#	include "containers/vector.h"
#endif //vector_h_

#ifdef FREYA_USE_EASTL_TYPE_TRAITS
#	include "EASTL/type_traits.h"
#endif // FREYA_USE_EASTL_TYPE_TRAITS


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
			::memcpy(result, first, (last - first) * sizeof(T));
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
			T*	__vector_impl_copy_unintialized_helper( T* result, typename const_reference<T>::type obj, eastl::true_type)
		{
			::memcpy(result, &obj, sizeof(T));
			return result + 1;
		}

		template<typename T>
		inline 
			T* __vector_impl_copy_unintialized_helper(T* result, typename const_reference<T>::type obj, eastl::false_type)
		{
			::new(result) T(obj);
			return result + 1;
		}

		template<typename I, typename T>
		inline
			T*	__vector_impl_copy_helper(I* first, I* last, T* result, eastl::true_type)
		{
			::memmove(result, first, (last - first) * sizeof(T));
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
			T*	__vector_impl_copy_helper( T* result, typename const_reference<T>::type obj, eastl::true_type)
		{
			::memmove(result, &obj, sizeof(T));
			return result + 1;
		}

		template<typename T>
		inline 
			T* __vector_impl_copy_helper(T* result, typename const_reference<T>::type obj, eastl::false_type)
		{
			*result = *obj;
			return result + 1;
		}

		template<typename T>
		inline
			T*	__vector_impl_copy_unitialized_backward_helper(T* first, T* last, T* result, eastl::true_type)
		{
			::memmove(result, first, (last - first) * sizeof(T));
			return result + (last - first);
		}

		template<typename T>
		inline 
			T* __vector_impl_copy_unitialized_backward_helper(T* first, T* last, T* result, eastl::false_type)
		{
			const size_t dist = last - first;
			result += dist;
			while( last != first )
				::new(--result) T(*(--last));
			return result + dist;
		}

		template<typename T>
		inline
			T*	__vector_impl_fill_helper( T* result, typename const_reference<T>::type obj, size_t n, eastl::true_type)
		{
			for(size_t i = 0; i < n; ++i, ++result)
				*result = obj;
			return result;
		}

		template<typename T>
		inline 
			T* __vector_impl_fill_helper(T* result, typename const_reference<T>::type obj, size_t n, eastl::false_type)
		{
			for(size_t i = 0; i < n; ++i)
				::new(result++) T(obj);
			return result;
		}
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	vector<T,MAP,LP,SRP>::vector(iterator _begin, iterator _end) 
		: m_AllocatedCount(get_vector_size(_end - _begin, 0)), m_Begin(allocate(m_AllocatedCount))
	{
		m_End = details::__vector_impl_copy_unintialized_helper(_begin,_end, m_Begin,eastl::has_trivial_copy<T>());
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	vector<T,MAP, LP, SRP>::~vector() 
	{
		if( m_Begin != m_End )
			details::__vector_impl_destructor_helper(m_Begin, m_End, eastl::has_trivial_destructor<T>());
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
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator first, iterator last )
	{
		if(m_Begin == m_End || first >= m_End || first == last) // Nothing to do
			return;
		lock();
		// Correct iterators
		if(first < m_Begin)
			first = m_Begin;
		if(last > m_End)
			last = m_End;

		// Move the rest
		T* ptr;
		if(last < m_End)
			ptr = details::__vector_impl_copy_helper(last, m_End, first, east::has_trivial_assign<T>());
		else
			ptr = first;
		
		details::__vector_impl_destructor_helper(ptr, m_End, eastl::has_trivial_destructor<T>());

		m_End = ptr;

		unlock();
	} // void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator first, iterator last )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::erase( iterator position )
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
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, const_iterator first, const_iterator last )
	{
		FREYA_SUPPORT_ASSERT(last >= first, "Incorrect insertion sequence");
		size_t elem_count = last - first;

		if(elem_count == 0) //Nothing to insert?
			return; //Boil out
		lock();
		if(!m_Begin)
		{
			m_AllocatedCount = get_vector_size(elem_count, 0);
			m_Begin = allocate(m_AllocatedCount);
			m_End = details::__vector_impl_copy_unintialized_helper( first, last, m_Begin, eastl::has_trivial_copy<T>());
		}
		else if( (m_End - m_Begin) > static_cast<ptrdiff_t>(m_AllocatedCount - elem_count) )
		{
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = get_vector_size(current_size + elem_count, m_AllocatedCount);
			T*	new_memory_ptr = allocate(new_size);
			if(position <= m_Begin)
			{
				details::__vector_impl_copy_unintialized_helper( first, last, new_memory_ptr,  eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr + elem_count, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(first, last, m_End, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				T* mem = details::__vector_impl_copy_unintialized_helper(m_Begin, position, new_memory_ptr, eastl::has_trivial_copy<T>());
				mem = details::__vector_impl_copy_unintialized_helper( first, last, mem, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(position, m_End, mem, eastl::has_trivial_copy<T>());
			}
			deallocate(m_Begin);
			m_Begin = new_memory_ptr;
		}
		else
		{
			if(position <= m_Begin)
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(m_Begin, m_End, m_Begin + elem_count, eastl::has_trivial_copy<T>());
				details::__vector_impl_copy_unintialized_helper( first, last, m_Begin, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper( first, last, m_End, eastl::has_trivial_copy<T>());
			}
			else
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(position, m_End, position + elem_count, eastl::has_trivial_copy<T>());
				details::__vector_impl_copy_unintialized_helper( first, last, position, eastl::has_trivial_copy<T>());
			}
		}
		unlock();
	} //void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, const_iterator first, const_iterator last )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, size_t n, constant_refernce obj )
	{
		lock();
		if(!m_Begin)
		{
			m_AllocatedCount = get_vector_size(n, 0);
			m_Begin = allocate(m_AllocatedCount);
			m_End = details::__vector_impl_fill_helper(m_Begin, obj, n, eastl::has_trivial_copy<T>());
		}
		else if( (m_End - m_Begin) > static_cast<ptrdiff_t>(m_AllocatedCount - n) )
		{
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = get_vector_size(current_size + n, m_AllocatedCount);
			T*	new_memory_ptr = allocate(new_size);
			if(position <= m_Begin)
			{
				details::__vector_impl_fill_helper(new_memory_ptr, obj, n, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr + n, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_fill_helper(m_End, obj, n, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				T* mem = details::__vector_impl_copy_unintialized_helper(m_Begin, position, new_memory_ptr, eastl::has_trivial_copy<T>());
				mem = details::__vector_impl_fill_helper(mem, obj, n, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(position, m_End, mem, eastl::has_trivial_copy<T>());
			}
			deallocate(m_Begin);
			m_Begin = new_memory_ptr;
		}
		else
		{
			if(position <= m_Begin)
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(m_Begin, m_End, m_Begin + n, eastl::has_trivial_copy<T>());
				details::__vector_impl_fill_helper(m_Begin, obj,n, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_fill_helper(m_End, obj,n, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(position, m_End, position + n, eastl::has_trivial_copy<T>());
				details::__vector_impl_fill_helper(position, obj, n, eastl::has_trivial_copy<T>());
			}
		}
		unlock();
	} //void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, size_t n, constant_refernce obj )


	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, constant_refernce obj )
	{
		lock();
		if(!m_Begin)
		{
			m_AllocatedCount = get_vector_size(1, 0);
			m_Begin = allocate(m_AllocatedCount);
			m_End = details::__vector_impl_copy_unintialized_helper(m_Begin,obj,eastl::has_trivial_copy<T>());
		}
		else if( (m_End - m_Begin) == m_AllocatedCount )
		{
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = get_vector_size(current_size + 1, m_AllocatedCount);
			T*	new_memory_ptr = allocate(new_size);
			if(position <= m_Begin)
			{
				details::__vector_impl_copy_unintialized_helper(new_memory_ptr, obj, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr + 1, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(m_End, obj, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				T* mem = details::__vector_impl_copy_unintialized_helper(m_Begin, position, new_memory_ptr, eastl::has_trivial_copy<T>());
				mem = details::__vector_impl_copy_unintialized_helper(mem, obj, eastl::has_trivial_copy<T>());
				m_End = details::__vector_impl_copy_unintialized_helper(position, m_End, mem, eastl::has_trivial_copy<T>());
			}
			//m_End = details::__vector_copy_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
			deallocate(m_Begin);
			m_Begin = new_memory_ptr;
		}
		else
		{
			if(position <= m_Begin)
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(m_Begin, m_End, m_Begin + 1, eastl::has_trivial_copy<T>());
				details::__vector_impl_copy_unintialized_helper(m_Begin, obj, eastl::has_trivial_copy<T>());
			}
			else if(position >= m_End)
			{
				m_End = details::__vector_impl_copy_unintialized_helper(m_End, obj, eastl::has_trivial_copy<T>());
			}
			else //Worst case
			{
				m_End = details::__vector_impl_copy_unitialized_backward_helper(position, m_End, position + 1, eastl::has_trivial_copy<T>());
				details::__vector_impl_copy_unintialized_helper(position, obj, eastl::has_trivial_copy<T>());
			}
		}
		unlock();
	} // void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::insert( iterator position, constant_refernce obj )

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::pop_back()
	{
		lock();
		if(m_Begin && m_Begin < m_End)
		{
			details::__vector_impl_destructor_helper(m_End - 1, m_End, eastl::has_trivial_destructor<T>());
			--m_End;
		}
		unlock();
	}

	template
		<
		typename T,
		template<class> class MemoryAllocationPolicy,
	class LockPolicy,
	class StorageResizePolicy
		>
		void containers::vector<T, MemoryAllocationPolicy, LockPolicy, StorageResizePolicy>::push_back( constant_refernce obj )
	{
		lock();
		if(!m_Begin)
		{
			m_AllocatedCount = get_vector_size(1, 0);
			m_Begin = allocate(m_AllocatedCount);
			m_End = m_Begin;
		}
		else if( (m_End - m_Begin) == m_AllocatedCount )
		{
			//Wtf, copying...
			const size_t current_size = m_End - m_Begin;
			const size_t new_size = get_vector_size(current_size + 1, m_AllocatedCount);
			T*	new_memory_ptr = allocate(new_size);
			m_End = details::__vector_impl_copy_unintialized_helper(m_Begin, m_End, new_memory_ptr, eastl::has_trivial_copy<T>());
			deallocate(m_Begin);
			m_Begin = new_memory_ptr;
		}

		m_End = details::__vector_impl_copy_unintialized_helper(m_End, obj, eastl::has_trivial_copy<T>());

		unlock();
	}

}

#endif // vector_impl_h__