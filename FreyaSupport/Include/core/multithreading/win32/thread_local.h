/* File   : core/multithreading/win32/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_PLATFORM_WIN_TLS
#define FREYA_PLATFORM_WIN_TLS

#include "core/multithreading/thread_local.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			template<bool Cmp>
			class size_constraints
			{
			public:
				inline size_constraints();
			};

			template<>
			inline size_constraints<true>::size_constraints()
			{
			}
		}

		template<typename Type>
		inline thread_local<Type>::thread_local()
			: thread_local_rep(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(thread_local_rep::tls_data_t))> compiletime_check;
		}

		template<typename Type>
		inline thread_local<Type>::thread_local(const Type& rval)
			: thread_local_rep(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(thread_local_rep::tls_data_t))> compiletime_check;
			TlsSetValue(thread_local_rep::m_tls_index, reinterpret_cast<LPVOID>(rval));
		}

		template<typename Type>
		inline thread_local<Type>::~thread_local()
		{
			TlsFree(thread_local_rep::m_tls_index);
		}

		template<typename Type>
		inline thread_local<Type>& thread_local<Type>::operator=(const Type& rval)
		{
			TlsSetValue(thread_local_rep::m_tls_index, reinterpret_cast<LPVOID>(rval));
			return *this;
		}

		template<typename Type>
		inline thread_local<Type>::operator Type() const
		{
			return reinterpret_cast<Type>(TlsGetValue(thread_local_rep::m_tls_index));
		}

		template<typename Type>
		inline thread_local<Type>& thread_local<Type>::set(const Type& rval)
		{
			TlsSetValue(thread_local_rep::m_tls_index, reinterpret_cast<LPVOID>(rval));
			return *this;
		}

		template<typename Type>
		inline Type thread_local<Type>::get() const
		{
			return reinterpret_cast<Type>(TlsGetValue(thread_local_rep::m_tls_index));
		}
	}
}

#endif//FREYA_PLATFORM_WIN_TLS