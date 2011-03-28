/*
 * jit_code.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifdef LUA_JIT_AVAILABLE

#ifndef JIT_CODE_H_
#define JIT_CODE_H_
#include <lua.hpp>

namespace core
{
namespace __lua_internal
{
unsigned installJITLibs(lua_State *L);
unsigned installJITOpt(lua_State* L);
unsigned installJITOptInline(lua_State* L);
}
}
#endif /* JIT_CODE_H_ */
#endif
