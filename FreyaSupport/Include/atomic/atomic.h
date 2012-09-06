/* File		: /atomic/atomic.h
 * Author	: V. Sverchinsky
 * E-Mail	: vitalii.sverchinsky@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_ATOMIC_H_
#define FREYA_ATOMIC_H_

#include "atomic/atomic-interface.h"

#if defined(MARMALADE_USED)

#	include "atomic/details/marmalade-atomic.h"

#elif defined(__clang__) // Supported arch x86-64, ARMv7 instruction based.
	#include "atomic/details/atomic-clang.h"
#elif defined(__GNUC__) // Supported arch x86-64, ARMv7 instruction based.

#ifndef _GLIBCXX_ATOMIC_BUILTINS
//#error "It looks like your compiler does not support atomic builtins for target platform, or you have not provided -march=* option(for x86-64: i486 or newer)."
#endif

	#if ( ((__GNUC__ * 10) + __GNUC_MINOR__) >= 41 )
		//atomic builtins supported by gcc starting with 4.1.0
		#include "atomic/details/atomic-gcc-4.1.0+.h"
	#else
		//#if defined( i686 here )
			//atomic implementation for gcc older then 4.1.0 for x86 based systems.
			#include "atomic/details/atomic-gcc-x86.h"
		//#elif defined ( ARMv7 here )
		//	//atomic implementation for gcc older then 4.1.0 for ARMv7
		//	#include "atomic/details/atomic-gcc-arm.h"
		//#endif
	#endif
#elif defined(_MSC_VER) // Supported arch x86-64.
	#include "atomic/details/atomic-msvc.h"
#endif



#endif//FREYA_ATOMIC_H_
