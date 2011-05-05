/* File   : core/multithreading/win32/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_WIN32_THREAD_LOCAL_H_
#define FREYA_MULTITHREADING_WIN32_THREAD_LOCAL_H_

#include "core/multithreading/details/thread_local.h"

namespace core
{
	namespace multithreading
	{
		namespace details
		{
			template<bool>
			inline void size_constraints();

			template<>
			inline void size_constraints<true>()
			{
			}
		}

		template<typename Type>
		inline thread_local<Type>::thread_local()
			: thread_local_rep(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(thread_local_rep::tls_data_t))>();
		}

		template<typename Type>
		inline thread_local<Type>::thread_local(const Type& rval)
			: thread_local_rep(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(thread_local_rep::tls_data_t))>();
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
	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_WIN32_THREAD_LOCAL_H_