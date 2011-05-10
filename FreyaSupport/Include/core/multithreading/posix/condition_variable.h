/* File   : core/multithreading/posix/condition_variable.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_CONDITION_VARIABLE_H
#define	FREYA_MULTITHREADING_CONDITION_VARIABLE_H

#include "core/multithreading/details/platform.h"
#include "core/multithreading/details/condition_variable.h"
#include "core/multithreading/details/mutex.h"

namespace core
{
    namespace multithreading
    {
        inline condition_variable::condition_variable()
        {
            (void) pthread_cond_init(&(condition_variable_rep::m_var), NULL);
        }
        
        inline condition_variable::~condition_variable()
        {
            (void) pthread_cond_destroy(&(condition_variable_rep::m_var));
        }
        
        inline void condition_variable::signal()
        {
            (void) pthread_cond_signal(&(condition_variable_rep::m_var));
        }
        
        inline void condition_variable::broadcast()
        {
            (void) pthread_cond_broadcast(&(condition_variable_rep::m_var));
        }
        
        inline void condition_variable::wait(mutex* sync)
        {
            (void) pthread_cond_wait(&(condition_variable_rep::m_var), &(reinterpret_cast<details::mutex_rep*>(sync)->m_mutex));
        }
#if defined(FREYA_DATE_TIME_HAVE_HIRES_CLOCK)
        //:TODO: implement
#else
        inline bool condition_variable::wait(mutex* sync, const date_time::system_clock::duration_t timeout)
        {
#warning "Timed wait implementation for condition variable unavailable."
        }
#endif
    }//namespace multithreading
}//namespace core

#endif/*FREYA_MULTITHREADING_CONDITION_VARIABLE_H*/

