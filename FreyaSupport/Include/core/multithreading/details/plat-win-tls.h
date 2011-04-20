/* File   : core/multithreading/details/plat-win-tls.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_PLATFORM_WIN_TLS
#define FREYA_PLATFORM_WIN_TLS

#include "core/multithreading/thread_local-interface.h"

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
			: m_index(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(DWORD))> compiletime_check;
		}

		template<typename Type>
		inline thread_local<Type>::thread_local(const Type& rval)
			: m_index(TlsAlloc())
		{
			details::size_constraints<(sizeof(Type) <= sizeof(DWORD))> compiletime_check;
			TlsSetValue(m_index, reinterpret_cast<LPVOID>(rval));
		}

		template<typename Type>
		inline thread_local<Type>::~thread_local()
		{
			TlsFree(m_index);
		}

		template<typename Type>
		inline thread_local<Type>& thread_local<Type>::operator=(const Type& rval)
		{
			TlsSetValue(m_index, reinterpret_cast<LPVOID>(rval));
			return *this;
		}

		template<typename Type>
		inline thread_local<Type>::operator Type() const
		{
			return reinterpret_cast<Type>(TlsGetValue(m_index));
		}

		template<typename Type>
		inline thread_local<Type>& thread_local<Type>::set(const Type& rval)
		{
			TlsSetValue(m_index, reinterpret_cast<LPVOID>(rval));
			return *this;
		}

		template<typename Type>
		inline Type thread_local<Type>::get() const
		{
			return reinterpret_cast<Type>(TlsGetValue(m_index));
		}
	}
}

#endif//FREYA_PLATFORM_WIN_TLS