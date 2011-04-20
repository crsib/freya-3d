/* File   : core/multithreading/thread_local-interface.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THERAD_LOCAL_INTERFACE_H
#define FREYA_THERAD_LOCAL_INTERFACE_H

#include "core/multithreading/details/thread-data.h"

namespace core
{
	namespace multithreading
	{
		template<typename Type>
		class thread_local
		{
		public:
			inline thread_local();
			inline thread_local(const Type& rval);
			inline ~thread_local();

			inline thread_local<Type>& operator=(const Type& rval);
			inline operator Type() const;

			inline thread_local<Type>& set(const Type& rval);
			inline Type get() const;
		private:
			const details::tls_index_t m_index;
		};

/*		template<typename Type>
		class thread_local<Type*>
		{
		public:
			inline thread_local(Type* ptr = NULL);
			inline ~thread_local();
			
			inline thread_local<Type*>& operator=(Type* ptr);
			inline operator Type*();
			inline operator const Type*() const;

			inline thread_local<Type*>& set(Type* ptr);
			inline Type* get();
			inline const Type* get() const;

		private:
			const details::tls_index_t m_index;
		};*/

	}//namespace multithreading
}//namespace core

#endif//FREYA_THERAD_LOCAL_INTERFACE_H