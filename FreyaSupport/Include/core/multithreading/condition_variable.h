/* File   : core/multithreading/condition_variable.h
 * Author : V. Sverchinsky
 * E-Mail : sverchinsky[at]gmail[dot]com
 *
 * This file is a part of Freya3D Engine.
 */
 
 #ifndef FREYA_MULTITHREADING_CONDITION_VARIABLE_H_
 #define FREYA_MULTITHREADING_CONDITION_VARIABLE_H_
 
#include "core/multithreading/details/condition_variable.h"

#if defined(PLATFORM_WIN_THREADS)
	#include "core/multithreading/win32/condition_variable.h"
#elif defined(PLATFORM_POSIX_THREADS)
        #include "core/multithreading/posix/condition_variable.h"
#endif
 
 #endif//FREYA_MULTITHREADING_CONDITION_VARIABLE_H_