/*
 * lua_alloc.cpp
 *
 *  Created on: 22.09.2008
 *      Author: vedenko
 */

#include "core/lua/lua_libraries/lua_alloc.h"
#include "core/EngineCore.h"
#include "core/memory/MemoryArena.h"
#include <cstdlib>
namespace core
{
namespace __lua_internal
{
//*
void *lua_alloc (void *ud, void *ptr, size_t osize,size_t nsize)
{
	if(nsize == 0)
	{
		EngineCore::getMemoryArena()->free(ptr,core::memory::LUA_POOL);//Act as free
		return NULL;
	}
	else
	{
		if(osize == 0)//Act as alloc
			return EngineCore::getMemoryArena()->allocate(nsize,core::memory::LUA_POOL);
		else//Act as realloc
		{
			void*	mem = EngineCore::getMemoryArena()->allocate(nsize,core::memory::LUA_POOL);
			::memcpy(mem,ptr,nsize < osize ? nsize : osize);
			EngineCore::getMemoryArena()->free(ptr,core::memory::LUA_POOL);
			return mem;
		}
	}
}
//*/
/*
void *lua_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
{

	(void)ud;  (void)osize;

	if (nsize == 0) {

		::free(ptr);

		return NULL;

	}

	else

		return ::realloc(ptr, nsize);
}
//*/
}
}
