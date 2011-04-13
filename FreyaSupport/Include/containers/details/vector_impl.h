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
	}

	template<typename T, template<class> class MAP, class LP, class SRP>
	vector<T,MAP, LP, SRP>::~vector() 
	{
		if( m_Begin != m_End )
			details::__vector_impl_destructor_helper(m_Begin, m_End, eastl::has_trivial_destructor<T>());
		deallocate( m_Begin );
	}


}

#endif // vector_impl_h__