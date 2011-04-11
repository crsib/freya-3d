/* File		: FreyaSuportInternal.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

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

#ifndef NDEBUG
#include <assert.h>
#define FREYA_SUPPORT_ASSERT(x,msg) assert(x && msg)
#else
#define  FREYA_SUPPORT_ASSERT(x, msg) 
#endif

#endif