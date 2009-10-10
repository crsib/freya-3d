/*
 * lua_libs.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef LUA_LIBS_H_
#define LUA_LIBS_H_
#include <lua.hpp>

namespace core
{
namespace __lua_internal
{
LUALIB_API void luaLibs_open (lua_State *L);
}
}
#endif /* LUA_LIBS_H_ */
