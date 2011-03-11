/*
 * init_math.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/lua/lua_libraries/init_math.h"

namespace core
{
namespace __lua_internal
{
void init_vector3d(lua_State* l)
{

	lua_getfield(l, LUA_GLOBALSINDEX, "math" ); //stack: math
	lua_getfield(l, -1, "vector3d"); 			//stack: math::vector3d math

	//quats
	lua_pushstring(l,".add");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_vec3dADDquat");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pushstring(l,".sub");						//stack add  math::vector3d math
	lua_getfield(l,-3,"_vec3dSUBquat");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pushstring(l,".mul");						//stack add  math::vector3d math
	lua_getfield(l,-3,"_vec3dMULquat");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);
	// +
	lua_pushstring(l,".add");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_vec3dADD");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);
	// -
	lua_pushstring(l,".sub");					//stack sub  math::vector3d math
	lua_getfield(l,-3,"_vec3dSUB");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);
	// v*v,v*f
	lua_pushstring(l,".mul");					//stack mul  math::vector3d math
	lua_getfield(l,-3,"_vec3dMUL");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);
	//v/f
	lua_pushstring(l,".div");					//stack div  math::vector3d math
	lua_getfield(l,-3,"_vec3dDIV");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	//stack:	math::vector3d math
	lua_pop(l,2);//stack: Empty
}

void init_quaternion(lua_State* l)
{
	lua_getfield(l, LUA_GLOBALSINDEX, "math" ); //stack: math
	lua_getfield(l, -1, "quaternion");

	lua_pushstring(l,".add");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_quatADD");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pushstring(l,".sub");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_quatSUB");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pushstring(l,".mul");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_quatMUL");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pushstring(l,".div");					//stack add  math::vector3d math
	lua_getfield(l,-3,"_quatDIV");				//stack: math::_ve3dADD add math::vector3d math
	lua_rawset(l,-3);

	lua_pop(l,2);//stack: Empty
}

void init_math(lua_State* l)
{
	init_vector3d(l);
	init_quaternion(l);
}
}
}
