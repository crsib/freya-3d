/*
 * lua_alloc.h
 *
 *  Created on: 22.09.2008
 *      Author: vedenko
 */

#ifndef LUA_ALLOC_H_
#define LUA_ALLOC_H_
#include <lua.hpp>
#include "core/EngineCore.h"

namespace core
{
namespace __lua_internal
{
void *lua_alloc (void *ud, void *ptr, size_t osize,size_t nsize);
}
}
#endif /* LUA_ALLOC_H_ */
