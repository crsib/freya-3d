/* File   : core/multithreading/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_THREAD_LOCAL
#define FREYA_THREAD_LOCAL

#include "FreyaSupportInternal.h"
#include "core/multithreading/details/platform.h"

namespace core
{
	namespace multithreading
	{
		/// \brief Template class used to place data locally to thread.
		/** 
		  * \tparam Type Base type. */
		template<typename Type>
		class thread_local : private details::thread_local_rep
		{
		public:
			inline thread_local();
			inline thread_local(const Type& rval);
			inline ~thread_local();

			inline thread_local<Type>& operator=(const Type& rval);
			inline operator Type() const;

			inline thread_local<Type>& set(const Type& rval);
			inline Type get() const;
		};

		/*template<typename Type>
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
		};*/

	}//namespace multithreading
}//namespace core

#include "core/multithreading/details/thread_local.h"

#endif//FREYA_THREAD_LOCAL