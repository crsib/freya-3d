#ifndef __FREYA_SUPPORT_INTERNAL_H__
#define __FREYA_SUPPORT_INTERNAL_H__

#ifndef FREYA_SUPPORT_EXPORT
#	ifndef _STATIC_BUILD
#		ifdef _MSC_VER
#			ifdef _FREYA_SUPPORT_SHARED_BUILD
#				define FREYA_SUPPORT_EXPORT __declspec(dllexport)
#			else
#				define FREYA_SUPPORT_EXPORT __declspec(dllimport)
#			endif
#		else
#			define FREYA_SUPPORT_EXPORT __attribute__ ((visibility("default")))
#		endif
#	else
#		define	FREYA_SUPPORT_EXPORT extern
#	endif
#endif

#endif