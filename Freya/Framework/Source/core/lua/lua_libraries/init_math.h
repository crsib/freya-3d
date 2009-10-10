/*
 * init_math.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef INIT_MATH_H_
#define INIT_MATH_H_
#include <lua.hpp>
#include "core/lua/tolua++/tolua++.h"
namespace core
{
namespace __lua_internal
{
void init_math(lua_State* l);
}
}
#endif /* INIT_MATH_H_ */
