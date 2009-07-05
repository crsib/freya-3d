#ifndef __INTERNAL_H
#define __INTERNAL_H
#ifdef _WIN32
#define __STATIC
#	ifndef __STATIC
#		ifdef __DLL_SOURCE
#			define EXPORT __declspec(dllexport)
#		else
#			define EXPORT __declspec(dllimport)
#		endif
#	else
#		define EXPORT
#	endif
#else
#	define EXPORT 
#endif

#endif
