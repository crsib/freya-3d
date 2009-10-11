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

#endif
