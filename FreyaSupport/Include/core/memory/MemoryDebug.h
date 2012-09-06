/* File		: core/memory/MemoryDebug.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef MemoryDebug_h__
#define MemoryDebug_h__

#include "FreyaSupportInternal.h"
#define MEMORY_DEBUGGING_ENABLED

#if defined(NDEBUG) || (!defined(_WIN32))
#undef MEMORY_DEBUGGING_ENABLED
#endif

#ifdef MEMORY_DEBUGGING_ENABLED

extern "C"
{

	FREYA_SUPPORT_EXPORT void* memcpy_debug( void* dest, const void* source, size_t num );
	FREYA_SUPPORT_EXPORT void* memmove_debug( void * destination, const void * source, size_t num );
	FREYA_SUPPORT_EXPORT char* strcpy_debug( char * destination, const char * source );
	FREYA_SUPPORT_EXPORT char* strncpy_debug( char * destination, const char * source, size_t num );
	FREYA_SUPPORT_EXPORT void* memset_debug ( void * ptr, int value, size_t num );

}

#	define MEMSET(dest, val, count)  memset_debug(dest, val, count);
#	define MEMCPY(dest, source, count) memcpy_debug(dest, source, count);
#	define MEMMOVE(dest, source, count) memmove_debug(dest, source, count);
#	define STRCPY( dest, source ) strcpy_debug( dest, source );
#	define STRNCPY( dest, source, max_count) strncpy_debug( dest, source, max_count)
#else
#	define MEMSET(dest, val, count) memset(dest, val, count)
#	define MEMCPY(dest, source, count) memcpy(dest, source, count)
#	define MEMMOVE(dest, source, count) memmove(dest, source, count)
#	define STRCPY( dest, source ) strcpy( dest, source )
#	define STRNCPY( dest, source, max_count) strncpy( dest, source, max_count )
#endif
#endif // MemoryDebug_h__
