#ifndef __INTERNAL_H
#define __INTERNAL_H
#ifdef _WIN32
#	if defined(_SHARED_BUILD) || defined(_FREYA_SHARED_PLUGIN)
#		define EXPORT __declspec(dllexport)
#	else
#		define EXPORT __declspec(dllimport)
#endif
#else
#	define EXPORT __attribute__ ((visibility("default")))
#endif

//Some usefull template routines
template<int t>
class IntToType
{
	enum __int2type { VALUE = t};
};

// stdint wrap for msvc
#ifndef _MSC_VER
#include <stdint.h>
#else
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef  __int16 int16_t;
typedef  __int8	 int8_t;
typedef unsigned __int8 uint8_t;
#endif

#endif
