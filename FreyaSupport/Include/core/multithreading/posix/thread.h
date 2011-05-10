/* File	  : core/multithreading/details/thread.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_POSIX_THREAD_H
#define	FREYA_MULTITHREADING_POSIX_THREAD_H

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/thread.h"
#include "atomic/atomic.h"
#include "core/multithreading/thread_local.h"
#include "date_time/details/system_clock.h"

namespace core
{
    namespace multithreading
    {
        /// \cond
        namespace details
        {
            FREYA_SUPPORT_EXPORT extern atomic::atomic<unsigned> __process_thread_counter;
            FREYA_SUPPORT_EXPORT extern core::multithreading::thread_local<unsigned> freya_id;
            
            template<typename T, void (T::*Func)(void)>
            void* plat_posix_thread_routine(void* args)
            {
                details::freya_id = details::__process_thread_counter++;
                T* object_ptr = reinterpret_cast<T*>(args);
                (object_ptr->*Func)();
                return NULL;
            }
        }
        /// \endcond
        
        inline thread::thread()
        {
        }
        
        inline thread::~thread()
        {
            kill();
        }
        
        template<typename T, void (T::*Func)(void)>
        thread* thread::create(T& runable)
        {
            thread* t = new thread;
            if(pthread_create(&(t->m_handle), NULL, &(details::plat_posix_thread_routine<T, Func>), reinterpret_cast<void*>(&runable)) == 0)
                return t;
            else 
            {
                delete t;
                return NULL;
            }
        }
        
        //:TODO: implement
        inline bool thread::is_active() const
        {
            return true;
        }
        
        inline bool thread::join()
        {
            return (pthread_join(thread_rep::m_handle, NULL) == 0);
        }
        
#if defined(FREYA_DATE_TIME_HAVE_HIRES_TIMER)
        //:TODO: implemet
        inline bool thread::join(const date_time::system_clock::duration_t timeout)
        {
        }
#else
        //:TODO: implemet
        inline bool thread::join(const date_time::system_clock::duration_t timeout)
        {
            return false;
        }
#endif
        
        inline void thread::kill()
        {
            (void) pthread_cancel(thread_rep::m_handle);
        }
        
        
        
    }//namespace mulltithreading
}//namespace core


#endif	/* FREYA_MULTITHREADING_POSIX_THREAD_H*/

