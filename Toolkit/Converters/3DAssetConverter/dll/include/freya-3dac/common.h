/* 3DAC header */

#ifndef _3DAC_COMMON_H
#define _3DAC_COMMON_H

#include <boost/shared_ptr.hpp>
#include <freya.h>
#include <scenegraph/AABB.h>
#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

namespace dac 
{
    typedef std::string String;

    typedef signed   __int8  int8;
    typedef unsigned __int8  uint8;

    typedef signed   __int16 int16;
    typedef unsigned __int16 uint16;

    typedef signed   __int32 int32;
    typedef unsigned __int32 uint32;

} // namespace dac

#ifdef freya_3dac_dll_EXPORTS
#   define _3DAC_EXPORT __declspec(dllexport)
#else
#   define _3DAC_EXPORT __declspec(dllimport)
#endif

#if defined(WIN32) && defined(_DEBUG)
#	include <crtdbg.h>
#	define DAC_DBG_BREAK _CrtDbgBreak();
#endif

#ifndef DAC_DBG_BREAK
#	define DAC_DBG_BREAK
#endif

#define DAC_ASSERT3(expr, msg, ret) { if( !(expr) ) { std::cerr << "E!   " << msg << " " << " on line " << __LINE__ << " of file `" << __FILE__ << "`!" ; DAC_DBG_BREAK; ret; } }
#define DAC_ASSERT2(expr, msg) DAC_ASSERT3(expr, msg, 0)
#define DAC_ASSERT(expr) DAC_ASSERT2(expr, #expr)
#define DAC_ERROR2(msg, ret) DAC_ASSERT3(0, msg, ret)
#define DAC_ERROR(msg) DAC_ASSERT2(0, msg)

#endif //#ifndef _3DAC_COMMON_H
