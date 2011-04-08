#ifndef __FREYA_CORE_INTERNAL_H__
#define __FREYA_CORE_INTERNAL_H__

#ifndef FREYA_CORE_EXPORT
#	ifndef _STATIC_BUILD
#		ifdef _MSC_VER
#			ifdef _FREYA_CORE_SHARED_BUILD
#				define FREYA_CORE_EXPORT __declspec(dllexport)
#			else
#				define FREYA_CORE_EXPORT __declspec(dllimport)
#			endif
#		else
#			define FREYA_CORE_EXPORT __attribute__ ((visibility("default")))
#		endif
#	else
#		define	FREYA_CORE_EXPORT extern
#	endif
#endif

#ifndef NDEBUG
#include <assert.h>
#define FREYA_CORE_ASSERT(x,msg) assert(x && msg)
#else
#define  FREYA_CORE_ASSERT(x, msg) 
#endif

#endif