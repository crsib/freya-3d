/*
 * lua_libs.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include <lua.hpp>
extern "C" int luaopen_bit(lua_State *L);
namespace core
{
namespace __lua_internal
{
const luaL_Reg lualibs[] = {
		{"", luaopen_base},
		{LUA_LOADLIBNAME, luaopen_package},
		{LUA_TABLIBNAME, luaopen_table},
		{LUA_IOLIBNAME, luaopen_io},
		{LUA_OSLIBNAME, luaopen_os},
		{LUA_STRLIBNAME, luaopen_string},
		{LUA_MATHLIBNAME, luaopen_math},
		{"bit",			  luaopen_bit},
		{LUA_DBLIBNAME, luaopen_debug},
		{NULL, NULL}
};//TODO: remove debug modules



LUALIB_API void luaLibs_open (lua_State *L)
{
	const luaL_Reg *lib = lualibs;
	for (; lib->func; lib++)
	{
		lua_pushcfunction(L, lib->func);
		lua_pushstring(L, lib->name);
		lua_call(L, 1, 0);
	}
}


}
}

