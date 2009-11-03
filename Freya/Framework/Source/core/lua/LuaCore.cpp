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
using std::clog;
using std::endl;

TOLUA_API int luaopen_freya (lua_State* tolua_S);

namespace core
{
namespace lua
{
LuaCore::LuaCore()
{
	// TODO Auto-generated constructor stub
	clog << "Starting lua virtual machine"<< endl;
	m_VirtualMachine = lua_newstate(core::__lua_internal::lua_alloc,NULL);
	if(m_VirtualMachine == 0) //Whoa, virtual machine failed to start
	{
		clog << "Lua virtual machine failed to start" << endl;
		throw core::lua::LuaException("virtual machine failed to start");
	}
	//Now, start up libraries (without jit)
	core::__lua_internal::luaLibs_open(m_VirtualMachine);
	//Startup tolua
	::luaopen_freya(m_VirtualMachine);
	//checkout math
	//core::__lua_internal::init_math(m_VirtualMachine);

	//Setting default values
	m_JITInstalled = m_JITStarted = 0;
}

LuaCore::~LuaCore()
{
	//For some reason, when using luaJIT VM GC full cycle is absolutely ruined, trying to access high memory ranges
	//The problem is possibly because of some internal LuaJIT error (as everything is absolutely ok when  using standard Lua VM
	//(without JIT compiler)
	//On other hand, lua-jit is perfectly working as standalone (with all GC/close state functions)
	//Thus, the problem might be becuase of application is doing something wrong
	//Nevertheless, stopping GC (without letting user to start it) and leaving Lua state open
	//does not cause any memory leak because of internal allocator. So, on this stage (and, probably, even on release stage)
	//we wont use any of GC functionality neither will close the state
	//TODO: Remove this on release.
#ifndef LUA_JIT_AVAILABLE1
	lua_close(m_VirtualMachine);
#endif
}

void LuaCore::runScript(const EString& script)
{
	if((luaL_loadstring(m_VirtualMachine,script.c_str())||lua_pcall(m_VirtualMachine,0,0,0)))
	{
		const char* err =  lua_tostring(m_VirtualMachine,-1);
		clog << "Lua internal error while loading script: " << err << endl;
		lua_pop(m_VirtualMachine,1);
		throw core::lua::LuaException(EString("script is malformed\nSynopsis: ") + err);
	}
}

void LuaCore::includeModule(const EString& module_name,const EString& script)
{
	clog << "Requiring module " << module_name << endl;
	static const char __package[] = "package";
	static const char __preload[] = "preload";

	lua_getglobal(m_VirtualMachine,__package);

	if ( lua_istable(m_VirtualMachine,-1))
	{
		lua_pushstring(m_VirtualMachine,__preload);
		lua_gettable(m_VirtualMachine,-2);
		if ( lua_istable(m_VirtualMachine,-1))
		{
			lua_pushstring(m_VirtualMachine,module_name.c_str());
			EString scr = "module ( ..., package.seeall )\n";
			scr +=script;
			int error = luaL_loadbuffer(m_VirtualMachine,scr.data(),scr.length(),"");
			if ( error )
			{
				clog << "Lua error: " <<  lua_tostring(m_VirtualMachine, -1) << endl;
				lua_pop(m_VirtualMachine,2);
				throw core::lua::LuaException("failed to load module code");
			}
			lua_settable(m_VirtualMachine,-3);

			lua_pop(m_VirtualMachine,2);

			//Now load this package
			EString str = "package.loaded."+ module_name +" = nil\nrequire \"" + module_name +"\"";
			luaL_dostring(m_VirtualMachine,str.c_str());
			clog << "Package " << module_name << " added successfully" << endl;
			return;
		}
		else
		{
			lua_pop(m_VirtualMachine,2);
			clog << "Lua: Error - no 'package.preload' table" << endl;
			throw LuaException("package.preload table does not exists");
		}
	}
	else
	{
		//no package global table
		lua_pop(m_VirtualMachine,1);
		clog << "Lua: Error - no global 'package' table" << endl;
		throw LuaException("package table does not exists");
	}

}

void	LuaCore::startJIT(unsigned OptLevel)
{
#ifdef LUA_JIT_AVAILABLE
	if(m_JITInstalled)
	{
		if(m_JITStarted == 0)
		{
			luaJIT_setmode(m_VirtualMachine, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
			m_JITStarted = 1;
		}
	}
	else //Jit is not installed
	{
		//TODO: try to remove this on release
		lua_gc(m_VirtualMachine,LUA_GCSTOP,0);
		//end of TODO section
		if(__lua_internal::installJITLibs(m_VirtualMachine))
			throw LuaException();
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
		__lua_internal::installJITOpt(m_VirtualMachine);
		runScript("require(\"jit.opt\").start()\n");
		break;
	case	FULL_OPTIMIZATION:
		runScript(
				"package.loaded[\"jit.opt\"] = nil\n"
				"package.loaded[\"jit.opt_inline\"] = nil\n"
				"package.preload[\"jit.opt\"] = nill\n"
				"package.preload[\"jit.opt_inline\"] = nill\n"
		);
		__lua_internal::installJITOpt(m_VirtualMachine);
		__lua_internal::installJITOptInline(m_VirtualMachine);
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
	if(m_JITStarted)
	{
		luaJIT_setmode(m_VirtualMachine, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_OFF);
		m_JITStarted = 0;
	}
#endif
}

void LuaCore::forceGarbageCollector()
{
#ifndef LUA_JIT_AVAILABLE
	lua_gc(m_VirtualMachine,LUA_GCCOLLECT,0);
#endif
}

void LuaCore::stopGarbageCollector()
{
#ifndef LUA_JIT_AVAILABLE
	lua_gc(m_VirtualMachine,LUA_GCSTOP,0);
#endif
}

void LuaCore::restartGarbageCollector()
{
#ifndef LUA_JIT_AVAILABLE
	lua_gc(m_VirtualMachine,LUA_GCRESTART,0);
#endif
}

Variable LuaCore::getValue(const EString& name)
{
	return Variable(m_VirtualMachine,name);;
}


void LuaCore::pushValue(const Variable& var)
{
	Variable v(var);
	switch (var.getType())
	{
	case Variable::BOOLEAN:
		lua_pushboolean(m_VirtualMachine,v.m_Boolean);
		break;
	case Variable::INT:
		lua_pushinteger(m_VirtualMachine,v.m_Integer);
		break;
	case Variable::DOUBLE:
		lua_pushnumber(m_VirtualMachine,v.m_Double);
		break;
	case Variable::STRING:
		lua_pushstring(m_VirtualMachine,v.m_String->c_str());
		break;
	case Variable::VECTOR3D:
		tolua_pushusertype(m_VirtualMachine,v.m_Vector3d,(const char*)"math::vector3d");
		break;
	case Variable::QUATERNION:
		tolua_pushusertype(m_VirtualMachine,v.m_Quaternion,(const char*)"math::quaternion");
		break;
	case Variable::MATRIX3X3:
		tolua_pushusertype(m_VirtualMachine,v.m_Matrix3x3,(const char*)"math::matrix3x3");
		break;
	case Variable::MATRIX4X4:
		tolua_pushusertype(m_VirtualMachine,v.m_Matrix4x4,(const char*)"math::matrix4x4");
		break;
	}
}

void LuaCore::setValue(const EString& name,const core::Variable& var)
{
	//Retrieve table
	EStringList lst;
	EString temp = name;
	while(true)
	{
		EString::size_type pos;
		pos = temp.find_first_of(".");
		if(pos == EString::npos) //Ok, seems that we are ready
		{
			lst.push_back(temp);
			break;
		}
		lst.push_back(temp.substr(0,pos));
		temp.erase(0,pos+1);
	}
	size_t sz = lst.size();
	if(sz!= 1)
	{
		lua_getglobal(m_VirtualMachine, lst[0].c_str());
		if(!lua_istable(m_VirtualMachine,-1))
		{
			lua_pop(m_VirtualMachine,1);
			throw core::lua::VariableException(name);
		}
		for(unsigned i = 1; i < sz - 1; i++)
		{
			lua_getfield(m_VirtualMachine,-1,lst[i].c_str());
			if(!lua_istable(m_VirtualMachine,-1))
			{
				lua_pop(m_VirtualMachine,2);
				throw core::lua::VariableException(name);
			}
			lua_remove(m_VirtualMachine,-2);
		}
		//Ok, needed table is on top
		pushValue(var);
		lua_setfield(m_VirtualMachine,-2,lst[sz - 1].c_str());
		lua_pop(m_VirtualMachine,1);
	}
	else //Setting global value
	{
		pushValue(var);
		lua_setfield(m_VirtualMachine,LUA_GLOBALSINDEX,lst[0].c_str());
	}
}

LuaFunction LuaCore::getFuction(const EString& name,unsigned NumArgs,unsigned NumRet)
{
	return LuaFunction(name,NumArgs,NumRet);
}


Variable LuaCore::popValue()
{
	return Variable(m_VirtualMachine,"");
}

void	LuaCore::compileFunction(const LuaFunction& f)
{
#ifdef LUA_JIT_AVAILABLE
	const_cast<LuaFunction&>(f).pushOnTop();
	luaJIT_compile(m_VirtualMachine,0);
	const_cast<LuaFunction&>(f).clear();
#endif
}
}
}
