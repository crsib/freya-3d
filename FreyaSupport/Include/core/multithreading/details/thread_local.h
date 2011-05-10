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
		/// \brief Template class used to place data locally to the thread.
		/** Types which size exceeds size of pointer on the current platform,
		  * could not be used as base types. Also instances of base type
		  * must be copyable.
		  * \tparam Type Base type.*/
		template<typename Type>
		class thread_local : private details::thread_local_rep
		{
			/// \brief Copying is forbidden.
			thread_local(const thread_local<Type>&);
			/// \brief Copying is forbidden.
			thread_local<Type>& operator=(const thread_local<Type>&);
		public:
			/// \brief Default constructor.
			inline thread_local();
			
			/// \brief Create instance, initialize with provided value.
			/** \param rval Instance of base type.*/
			inline thread_local(const Type& rval);
			
			/// \brief Default destructor.
			inline ~thread_local();

			/// \brief Assignment operator.
			/** \param rval Instance of base type which should be used as source.
			  * \return Self.*/
			inline thread_local<Type>& operator=(const Type& rval);

			/// \brief Implicit cast to base type.
			inline operator Type() const;

			/// \brief Same as assignment operator.
			inline thread_local<Type>& set(const Type& rval);

			/// \brief Same as implicit cast to base type.
			inline Type get() const;
                private:
                    FREYA_SUPPORT_FORCE_INLINE details::thread_local_rep* super()
                    {
                        return static_cast<details::thread_local_rep*>(this);
                    }
                    
                    FREYA_SUPPORT_FORCE_INLINE const details::thread_local_rep* super() const
                    {
                        return static_cast<const details::thread_local_rep*>(this);
                    }
		};

	}//namespace multithreading
}//namespace core

#endif//FREYA_MULTITHREADING_DETAILS_THREAD_LOCAL_H_