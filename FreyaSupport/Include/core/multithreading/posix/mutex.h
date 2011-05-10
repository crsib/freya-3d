/* File	  : core/multithreading/posix/mutex.h
 * Author : V. Sverchinsky
 * E-Mail : vitalii.sverchinsky[at]freya3d[dot]org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_POSIX_MUTEX_H
#define	FREYA_MULTITHREADING_POSIX_MUTEX_H

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/mutex.h"
#include "core/multithreading/thread_self.h"
#include "date_time/system_clock.h"

namespace core
{
    namespace multithreading
    {
        inline mutex::mutex()
        {
            (void) pthread_mutex_init(&(mutex_rep::m_mutex), NULL);
        }
        
        inline mutex::~mutex()
        {
            (void) pthread_mutex_destroy(&(mutex_rep::m_mutex));
        }
        
        inline void mutex::lock()
        {
            (void) pthread_mutex_lock(&(mutex_rep::m_mutex));
        }
        
#if defined(FREYA_DATE_TIME_HAVE_HIRES_CLOCK)        
        //:TODO: implement
#else
        inline bool mutex::lock(const date_time::system_clock::duration_t timeout)
        {
            date_time::system_clock start;
            while(true)
            {
                if(pthread_mutex_trylock(&(mutex_rep::m_mutex)) == 0)
                        return true;
                if( (date_time::system_clock::current() - start) > timeout )
                    return false;
                PAUSE;
            }
        }
#endif
        inline bool mutex::try_lock()
        {
            return (pthread_mutex_trylock(&(mutex_rep::m_mutex)) == 0);
        }
        
        inline void mutex::release()
        {
            (void) pthread_mutex_unlock(&(mutex_rep::m_mutex));
        }
    }//namespace multithreading
}//namespace core

#endif	/* MUTEX_H */

