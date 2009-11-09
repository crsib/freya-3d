/*
 * lua_helpers.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef LUA_HELPERS_H_
#define LUA_HELPERS_H_

#ifndef _cstring
#define _cstring char*
#endif

#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "core/lua/LuaCore.h"
#include "core/lua/LuaFunction.h"
#include "windowmanager/DriverSubsystems/InputDevices/KeyboardKeys.h"
#include "windowmanager/DriverSubsystems/InputDevices/MouseButtons.h"
#include "core/taskmanager/Task.h"
#include "windowmanager/WindowManagerDriver.h"
#include "windowmanager/Callback.h"

inline
void include(const EString& modName, const EString& path)
{
	size_t ssz;
	void* s_src = core::EngineCore::getFilesystem()->read("/Scripts/Demo.lua",&ssz);
	EString scr(reinterpret_cast<char*>(s_src),ssz);
	core::EngineCore::getLuaCore()->includeModule(modName,scr);
	core::memory::Free(s_src,core::memory::GENERIC_POOL);
}

enum	MemControl
{
	TOTAL_ALLOCATED,
	ALLOCATION_COUNT,
	DEALLOCATION_COUNT,
	ALLOCATED_FOR_BUFFERS
};

namespace core
{
namespace memory
{
	extern EXPORT unsigned memory_allocated;
	extern EXPORT unsigned allocation_count;
	extern EXPORT unsigned deallocation_count;
	extern EXPORT unsigned alloc_dealloc_dif;
	extern EXPORT unsigned allocated_for_buffers;
}
}

unsigned memoryUsage(MemControl ctrl)
{

	switch(ctrl)
	{
		case TOTAL_ALLOCATED:
			return core::memory::memory_allocated;
		case ALLOCATION_COUNT:
			return core::memory::allocation_count;
		case DEALLOCATION_COUNT:
			return core::memory::deallocation_count;
		case ALLOCATED_FOR_BUFFERS:
			return core::memory::allocated_for_buffers;
	}
	return 0;
}

const char*
keyboardKeyName(size_t i)
{
	return windowmanager::input::KeyboardKeyNames[i];
}

const char*
mouseButtonName(size_t i)
{
	return windowmanager::input::MouseButtonsNames[i];
}

namespace core
{
namespace taskmanager
{

class LuaTask : public core::taskmanager::Task
{
public:
	explicit LuaTask(const EString& metName) : m_Fn(metName,0,1)
	{
	}

	virtual
	int operator () ()
	{
		return (int)m_Fn();
	}
private:
	core::lua::LuaFunction		m_Fn;
};

}
}
namespace core
{
namespace lua
{
namespace __internal
{
extern core::lua::LuaFunction*		quit_callback;
extern core::lua::LuaFunction*		wheel_callback;

inline
void		quitCallback()
{
	if(quit_callback)
	{
		quit_callback->call();
	}
}

inline
void		wheelCallback(int hor,int vert)
{
	if(wheel_callback)
	{
		wheel_callback->setParameter(0,core::Variable((int)hor));
		wheel_callback->setParameter(1,core::Variable((int)vert));
		wheel_callback->call();
	}
}

}
}
}


inline
void	setQuitCallback(const EString& luaFn)
{
	if(core::lua::__internal::quit_callback)
		delete core::lua::__internal::quit_callback;
	core::lua::__internal::quit_callback = new core::lua::LuaFunction(luaFn,0,0);
	core::EngineCore::getWindowManager()->setQuitCallback(windowmanager::Callback(core::lua::__internal::quitCallback));
}

inline
void	setWheelCallback(const EString& luaFn)
{
	if(core::lua::__internal::wheel_callback)
		delete core::lua::__internal::wheel_callback;
	core::lua::__internal::wheel_callback = new core::lua::LuaFunction(luaFn,2,0);
	core::EngineCore::getWindowManager()->setMouseWheelCallback(windowmanager::Callback(core::lua::__internal::wheelCallback));
}

#endif /* LUA_HELPERS_H_ */
