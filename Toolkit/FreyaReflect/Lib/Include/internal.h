#ifndef __INTERNAL_H
#define __INTERNAL_H

#ifdef _WIN32
#	if defined(_SHARED_BUILD) 
#		define EXPORT __declspec(dllexport)
#	else
#		define EXPORT __declspec(dllimport)
#	endif
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

#include <boost/cstdint.hpp>

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#endif
