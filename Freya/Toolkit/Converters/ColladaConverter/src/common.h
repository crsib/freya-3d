/*
 * common.h
 *
 *  Created on: 18.11.2009
 *      Author: Alexander Ptakhin
 */

#ifndef COMMON_H
#define COMMON_H

#define EXPORT __declspec(dllimport)

#include <string>
#include <sstream>
#include <list>
#include <iostream>
//#include <windows.h>

#include <dae.h>
#include <dom/domConstants.h>
#include <dom/domCOLLADA.h>

typedef std::string String;

#define SAFE_DELETE(var) delete (var); (var) = 0;

#if defined(WIN32) && defined(_DEBUG)
#	include <crtdbg.h>
#	define DBG_BREAK _CrtDbgBreak();
#endif

#ifndef DBG_BREAK
#	define DBG_BREAK
#endif

#define ASSERT3(expr, msg, ret) { if( !(expr) ) { std::cerr << "E!   " << msg << " " << " on line " << __LINE__ << " of file `" << __FILE__ << "`!" ; DBG_BREAK; ret; } }
#define ASSERT2(expr, msg) ASSERT3(expr, msg, 0)
#define ASSERT(expr) ASSERT2(expr, #expr)
#define ERROR2(msg, ret) ASSERT3(0, msg, ret)
#define ERROR(msg) ASSERT2(0, msg)

// FIXME: check x86
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef int int32;
typedef short int16;
typedef char int8;

// FIXME: for other compilers
#ifndef nullptr
#	define nullptr NULL
#endif


//#include "debug.h"


#endif