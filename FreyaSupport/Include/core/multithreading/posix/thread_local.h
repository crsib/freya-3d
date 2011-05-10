/* File   : core/multithreading/posix/thread_local.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_POSIX_THREAD_LOCAL_H
#define	FREYA_MULTITHREADING_POSIX_THREAD_LOCAL_H

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/thread_local.h"

namespace core
{
    namespace multithreading
    {
        template<typename Type>
        inline thread_local<Type>::thread_local()
        {
            (void) pthread_key_create(&(super()->m_key), NULL);
        }
        
        template<typename Type>
        inline thread_local<Type>::thread_local(const Type& rval)
        {
            (void) pthread_key_create(&super()->m_key, NULL);
            pthread_setspecific(super()->m_key, reinterpret_cast<void*>(rval));
        }
        
        template<typename Type>
        inline thread_local<Type>::~thread_local()
        {
            (void) pthread_key_delete(super()->m_key);
        }
        
        template<typename Type>
        inline thread_local<Type>& thread_local<Type>::operator =(const Type& rval)
        {
            (void) pthread_setspecific(super()->m_key, reinterpret_cast<void*>(rval));
            return *this;
        }
        
        template<typename Type>
        inline thread_local<Type>::operator Type() const
        {
            return reinterpret_cast<Type>(pthread_getspecific(super()->m_key));
        }
        
        template<typename Type>
        inline Type thread_local<Type>::get() const
        {
            return reinterpret_cast<Type>(pthread_getspecific(super()->m_key));
        }
        
        template<typename Type>
        inline thread_local<Type>& thread_local<Type>::set(const Type& rval)
        {
            (void) pthread_setspecific(super()->m_key, reinterpret_cast<void*>(rval));
            return *this;
        }
    }//namespace multithreading
}//namespace core

#endif	/* FREYA_MULTITHREADING_POSIX_THREAD_LOCAL_H */

