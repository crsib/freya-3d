/* File	  : core/multithreading/details/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_DETAILS_THREAD_LOCAL_H_
#define FREYA_MULTITHREADING_DETAILS_THREAD_LOCAL_H_

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

	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_DETAILS_THREAD_LOCAL_H_