/* File		: FreyaReflectInternal.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef __FREYA_RELFECT_INTERNAL_H__
#define __FREYA_REFLECT_INTERNAL_H__

#ifndef FREYA_REFLECT_EXPORT
#	ifndef _STATIC_BUILD
#		ifdef _MSC_VER
#			ifdef _FREYA_REFLECT_SHARED_BUILD
#				define FREYA_REFLECT_EXPORT __declspec(dllexport)
#			else
#				define FREYA_REFLECT_EXPORT __declspec(dllimport)
#			endif
#		else
#			define FREYA_REFLECT_EXPORT __attribute__ ((visibility("default")))
#		endif
#	else
#		define	FREYA_REFLECT_EXPORT extern
#	endif
#endif

#ifndef NDEBUG
#include <assert.h>
#define FREYA_REFLECT_ASSERT(x,msg) assert(x && msg)
#else
#define  FREYA_REFLECT_ASSERT(x, msg) 
#define  assert(x)  
#endif

#endif