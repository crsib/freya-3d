/* File   : core/multithreading/posix/thread_self.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MULTITHREADING_POSIX_THREAD_SELF_H_
#define	FREYA_MULTITHREADING_POSIX_THREAD_SELF_H_

#if defined(__GNUC__) && !defined(MARMALADE_USED)
        #define PAUSE __asm__ __volatile__ ("pause");
#elif defined(MARMALADE_USED)
#	define PAUSE {}
#endif

#include "core/multithreading/details/platform.h"
#include "core/multithreading/thread_self.h"
#include "core/multithreading/thread_local.h"
#include <unistd.h>
#include <time.h>

#if defined(__MINGW__)
        #include <Windows.h>
#endif

namespace core
{
    namespace multithreading
    {
        namespace details
        {
            FREYA_SUPPORT_EXPORT extern core::multithreading::thread_local<unsigned> freya_id;
        }
        
        namespace thread_self
        {   
            inline bool yield()
            {
                return (sched_yield() == 0);
            }

            inline void sleep(const date_time::system_clock::duration_t ms)
            {
#if defined(__MINGW32__)
                (void) Sleep(ms); // in ms
#else
                // :TODO: remove magic numbers
                static const date_time::system_clock::duration_t usleep_limit = 1000;//in ms
                if(ms < usleep_limit )
                    (void) usleep(ms * 1000);
                else
                {
                    (void) ::sleep(ms / 1000); // in seconds
                    (void) usleep((ms % 1000) * 1000);
                }
#endif
            }
            
            inline unsigned get_freya_id()
            {
#ifndef MARMALADE_USED
                return static_cast<unsigned>(details::freya_id);
#else
				return 0;
#endif
            }
        }//namespace thread_self
    }//namespace multithreading
}//namespace core

#endif/*FREYA_MULTITHREADING_POSIX_THREAD_SELF_H_*/

