/*
 * LuaCore.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/lua/LuaCore.h"
#include "core/lua/lua_libraries/lua_alloc.h"
#include "core/lua/lua_libraries/lua_libs.h"
//#include "core/Lua/Packages/Binary/luabind.h"
#include "core/lua/lua_libraries/init_math.h"
#include "core/lua/lua_libraries/jit_code.h"
#include "core/lua/VariableException.h"
#include "core/lua/LuaException.h"
#include <iostream>
#include <algorithm>

#include "core/multithreading/ThreadBlocks.h"
using std::clog;
using std::endl;

TOLUA_API int luaopen_freya (lua_State* tolua_S);

namespace core
{
namespace lua
{
namespace __internal
{
core::lua::LuaFunction*		quit_callback 	= NULL;
core::lua::LuaFunction*		wheel_callback 	= NULL;
}

LuaCore::LuaCore()
{
	// TODO Auto-generated constructor stub
	clog << "Starting lua virtual machine"<< endl;
	m_VirtualMachine = lua_newstate(core::__lua_internal::lua_alloc,NULL);
	m_States.add(core::multithreading::getCurrentThreadID(),m_VirtualMachine);
	if(m_VirtualMachine == 0) //Whoa, virtual machine failed to start
	{
		clog << "Lua virtual machine failed to start" << endl;
		throw core::lua::LuaException("virtual machine failed to start");
	}
	//Now, start up libraries (without jit)
	core::__lua_internal::luaLibs_open(m_VirtualMachine) ;
	//Startup tolua
	luaopen_freya(m_VirtualMachine);
	//checkout math
	//core::__lua_internal::init_math(m_VirtualMachine);
	//Setting default values
	m_JITInstalled = m_JITStarted = 0;
}

LuaCore::~LuaCore()
{
	lua_close(m_VirtualMachine) ;
}

void LuaCore::runScript(const EString & script)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	if((luaL_loadstring(Lua, script.c_str()) || lua_pcall(Lua, 0, 0, 0)))
	{
		const char *err = lua_tostring(Lua, -1);
		clog << "Lua internal error while loading script: " << err << endl;
		lua_pop(Lua, 1);
		throw core::lua::LuaException(EString("script is malformed\nSynopsis: ") + err);
	}
}

void LuaCore::includeModule(const EString & module_name, const EString & script)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	clog << "Requiring module " << module_name << endl;
	static const char __package[] = "package";
	static const char __preload[] = "preload";
	lua_getglobal(Lua, __package);
	if(lua_istable(Lua, -1)){
		lua_pushstring(Lua, __preload);
		lua_gettable(Lua, -2);
		if(lua_istable(Lua, -1)){
			lua_pushstring(Lua, module_name.c_str());
			EString scr = "module ( ..., package.seeall )\n";
			scr += script;
			int error = luaL_loadbuffer(Lua, scr.data(), scr.length(), "");
			if(error){
				clog << "Lua error: " << lua_tostring(Lua, -1) << endl;
				lua_pop(Lua, 2);
				throw core::lua::LuaException("failed to load module code");
			}
			lua_settable(Lua, -3);
			lua_pop(Lua, 2);
			//Now load this package
			EString str = "package.loaded." + module_name + " = nil\nrequire \"" + module_name + "\"";
			luaL_dostring(Lua, str.c_str());
			clog << "Package " << module_name << " added successfully" << endl;
			return;
		}
		else{
			lua_pop(Lua, 2);
			clog << "Lua: Error - no 'package.preload' table" << endl;
			throw LuaException("package.preload table does not exists");
		}
	}
	else{
		//no package global table
		lua_pop(Lua, 1);
		clog << "Lua: Error - no global 'package' table" << endl;
		throw LuaException("package table does not exists");
	}
}

void LuaCore::startJIT(unsigned  OptLevel)
{
#ifdef LUA_JIT_AVAILABLE
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	if(m_JITInstalled)
	{
		if(m_JITStarted == 0)
		{
			luaJIT_setmode(Lua, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
			m_JITStarted = 1;
		}
	}
	else //Jit is not installed
	{
		if(__lua_internal::installJITLibs(Lua))
			throw LuaException("Failed to install jit optimizer code");
		m_JITInstalled = m_JITStarted = 1;
	}
	//Optimiztions check
	//*
	switch(OptLevel)
	{
	case	NO_OPTIMIZATION:
		runScript(
				"package.loaded[\"jit.opt\"] = nil\n"
				"package.loaded[\"jit.opt_inline\"] = nil\n"
				"package.preload[\"jit.opt\"] = nill\n"
				"package.preload[\"jit.opt_inline\"] = nill\n"
		);
		break;
	case	GENERAL_OPTIMIZATION:
		runScript(
				"package.loaded[\"jit.opt\"] = nil\n"
				"package.loaded[\"jit.opt_inline\"] = nil\n"
				"package.preload[\"jit.opt\"] = nill\n"
				"package.preload[\"jit.opt_inline\"] = nill\n"
		);
		__lua_internal::installJITOpt(Lua);
		runScript("require(\"jit.opt\").start()\n");
		break;
	case	FULL_OPTIMIZATION:
		runScript(
				"package.loaded[\"jit.opt\"] = nil\n"
				"package.loaded[\"jit.opt_inline\"] = nil\n"
				"package.preload[\"jit.opt\"] = nill\n"
				"package.preload[\"jit.opt_inline\"] = nill\n"
		);
		__lua_internal::installJITOpt(Lua);
		__lua_internal::installJITOptInline(Lua);
		runScript(
				"require(\"jit.opt\").start()\n"
				"require(\"jit.opt_inline\").start()\n"
		);
		break;
	}//*/
#endif

}

void LuaCore::stopJIT()
{
#ifdef LUA_JIT_AVAILABLE
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	if(m_JITStarted)
	{
		luaJIT_setmode(Lua, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_OFF);
		m_JITStarted = 0;
	}
#endif
}

void LuaCore::forceGarbageCollector()
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	lua_gc(Lua, LUA_GCCOLLECT, 0);
}

void LuaCore::stopGarbageCollector()
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	lua_gc(Lua, LUA_GCSTOP, 0);
}

void LuaCore::restartGarbageCollector()
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	lua_gc(Lua, LUA_GCRESTART, 0);
}

Variable LuaCore::getValue(const EString & name)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	return Variable(Lua, name);
}

void LuaCore::pushValue(const Variable & var)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	Variable v(var);
	switch (var.getType()){
		case Variable::BOOLEAN:
			lua_pushboolean(Lua, v.m_Boolean);
			break;
		case Variable::INT:
			lua_pushinteger(Lua, v.m_Integer);
			break;
		case Variable::DOUBLE:
			lua_pushnumber(Lua, v.m_Double);
			break;
		case Variable::STRING:
			lua_pushstring(Lua, v.m_String->c_str());
			break;
		case Variable::VECTOR3D:
			tolua_pushusertype(Lua, v.m_Vector3d, (const char*)("math::vector3d"));
			break;
		case Variable::QUATERNION:
			tolua_pushusertype(Lua, v.m_Quaternion, (const char*)("math::quaternion"));
			break;
		case Variable::MATRIX3X3:
			tolua_pushusertype(Lua, v.m_Matrix3x3, (const char*)("math::matrix3x3"));
			break;
		case Variable::MATRIX4X4:
			tolua_pushusertype(Lua, v.m_Matrix4x4, (const char*)("math::matrix4x4"));
			break;
	}
}

void LuaCore::setValue(const EString & name, const core::Variable & var)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	//Retrieve table
	EStringList lst;
	EString temp = name;
	while(true){
		EString::size_type pos;
		pos = temp.find_first_of(".");
		if(pos == EString::npos)//Ok, seems that we are ready
		{
			lst.push_back(temp);
			break;
		}
		lst.push_back(temp.substr(0, pos));
		temp.erase(0, pos + 1);
	}

	size_t sz = lst.size();
	if(sz != 1){
		lua_getglobal(Lua, lst[0].c_str());
		if(!lua_istable(Lua, -1)){
			lua_pop(Lua, 1);
			throw core::lua::VariableException(name);
		}
		for(unsigned i = 1;i < sz - 1;i++){
			lua_getfield(Lua, -1, lst[i].c_str());
			if(!lua_istable(Lua, -1)){
				lua_pop(Lua, 2);
				throw core::lua::VariableException(name);
			}
			lua_remove(Lua, -2);
		}

		//Ok, needed table is on top
		pushValue(var);
		lua_setfield(Lua, -2, lst[sz - 1].c_str());
		lua_pop(Lua, 1);
	}
	else//Setting global value
	{
		pushValue(var);
		lua_setfield(Lua, LUA_GLOBALSINDEX, lst[0].c_str());
	}
}

LuaFunction LuaCore::getFuction(const EString & name, unsigned  NumArgs, unsigned  NumRet)
{
	return LuaFunction(name, NumArgs, NumRet);
}

Variable LuaCore::popValue()
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	return Variable(Lua, "");
}

void LuaCore::compileFunction(const LuaFunction & f)
{
#ifdef LUA_JIT_AVAILABLE
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	const_cast<LuaFunction&>(f).pushOnTop();
	luaJIT_compile(Lua,0);
	const_cast<LuaFunction&>(f).clear();
#endif

}

void core::lua::LuaCore::createLuaThread(const core::multithreading::ThreadID & thrd)
{
	lua_State* Lua = m_States[core::multithreading::getCurrentThreadID()];
	clog << "Adding new lua state" << std::endl;
	m_States.add(thrd,lua_newthread(m_VirtualMachine));
	lua_settop(Lua,0);
}
}
}
