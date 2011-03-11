/*
 * LuaFunction.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/lua/LuaFunction.h"
#include "core/EngineCore.h"
#include "core/lua/LuaCore.h"
#include "core/Variable.h"
#include "core/lua/FunctionException.h"
#include "core/memory/MemoryAllocator.h"
#include "core/multithreading/ThreadBlocks.h"
#include <algorithm>

namespace core
{
namespace lua
{
LuaCore*		LuaFunction::m_Core = NULL;

#define GetLua m_Core->m_States[core::multithreading::getCurrentThreadID()]
LuaFunction::LuaFunction(const EString& name,unsigned NumArgs,unsigned NumRet)
{
	m_Ready = false;
	if(m_Core == NULL)
		m_Core = core::EngineCore::getLuaCore();
	lua_State* Lua = GetLua;
		std::cout << "LuaFunction::LuaFunction( " << name << ", " << NumArgs << ", " << NumRet <<  " )" << std::endl;
	//First, parse names to tockens
	EString temp = name;
	while(true)
	{
		EString::size_type pos;
		pos = temp.find_first_of(".");
		if(pos == EString::npos) //Ok, seems that we are ready
		{
			m_TockensList.push_back(temp);
			break;
		}
		m_TockensList.push_back(temp.substr(0,pos));
		temp.erase(0,pos+1);
	}
	//Ok, now we have fully parsed list
	//Check, that functions exists
	//Get our first table/function from globals top
	lua_getglobal(Lua, m_TockensList[0].c_str());
	if(lua_gettop(Lua) == 0)
	{
		//lua_pop(Lua,2);
		std::clog << "Function \"" << name << "\" is not found" << std::endl;
		throw core::lua::FunctionException(name);
	}
	for(unsigned i = 1; i < m_TockensList.size() - 1; i++)
	{
		lua_getfield(Lua,-1,m_TockensList[i].c_str());
		if(!lua_istable(Lua,-1))
		{
			lua_pop(Lua,2);
			std::clog << "Function \"" << name << "\" is not found" << std::endl;
			throw core::lua::FunctionException(name);
		}
		lua_remove(Lua,-2);
	}
	if(m_TockensList.size() != 1)
		lua_getfield(Lua,-1,m_TockensList[m_TockensList.size() - 1].c_str());
	//Our function is now on top. Check it (and throw an exception, if the value is not a function. e.g. is a nill value)
	if(!lua_isfunction(Lua,-1))
	{
		std::clog << "\"" << name << "\" is not a function" << std::endl;
		throw core::lua::FunctionException(name);
	}
	//Ok, that is a function
	//std::cout << "top value " << lua_gettop(Lua) << std::endl;
	lua_settop(Lua,0);
	//std::cout << "top value " << lua_gettop(Lua) << std::endl;
	//Reserve space for num arg and rets
	m_NumArgs = NumArgs;
	m_NumRet =  NumRet;
	if(m_NumArgs)
		m_Args = new Variable[m_NumArgs];
	else
		m_Args = NULL;

	if(m_NumRet)
		m_RetVals = new Variable[m_NumRet];
	else
		m_RetVals = NULL;
	//Our function is not on top
	m_OnTop = false;
	m_Ready = true;
	//std::cout << "Function " << name << " found " << std::endl;
}

LuaFunction::~LuaFunction()
{
	//	std::cout << "LuaFunction::~LuaFunction(const LuaFunction& f)" << std::endl;
	delete [] m_Args;
	delete [] m_RetVals;
}

LuaFunction::LuaFunction(const LuaFunction& f)
{
	//	std::cout << "LuaFunction::LuaFunction(const LuaFunction& f)" << std::endl;
	m_TockensList = f.m_TockensList;

	m_NumArgs = f.m_NumArgs;
	if(m_NumArgs)
		m_Args = new Variable[m_NumArgs];
	else
		m_Args = NULL;
	for(size_t i = 0; i < m_NumArgs; i++)
	{
		m_Args[i] = f.m_Args[i];
	}

	m_OnTop = f.m_OnTop;

	m_NumRet = f.m_NumRet;
	if(m_NumRet)
		m_RetVals = new Variable[m_NumRet];
	else
		m_RetVals = NULL;
	for(size_t i = 0; i < m_NumRet; i++)
	{
		m_RetVals[i] = f.m_RetVals[i];
	}
}

LuaFunction&	LuaFunction::operator = (const LuaFunction& f)
{
		std::cout << "LuaFunction::operator =(const LuaFunction& f)" << std::endl;
	m_TockensList = f.m_TockensList;

	m_NumArgs = f.m_NumArgs;
	delete [] m_Args;
	if(m_NumArgs)
		m_Args = new Variable[m_NumArgs];
	else
		m_Args = NULL;
	for(size_t i = 0; i < m_NumArgs; i++)
	{
		m_Args[i] = f.m_Args[i];
	}

	m_OnTop = f.m_OnTop;

	m_NumRet = f.m_NumRet;
	delete [] m_RetVals;
	if(m_NumRet)
		m_RetVals = new Variable[m_NumRet];
	else
		m_RetVals = NULL;
	for(size_t i = 0; i < m_NumRet; i++)
	{
		m_RetVals[i] = f.m_RetVals[i];
	}
	return *this;
}

void LuaFunction::setParameter(unsigned index,const Variable& var)
{
	m_Args[index] = var;
}

void LuaFunction::setParameters(const Variable*  var)
{
	for(size_t i = 0; i < m_NumArgs; i++)
	{
		m_Args[i] = var[i];
	}
}

void LuaFunction::pushOnTop()
{
	lua_State* Lua = GetLua;
	if(!m_OnTop)
	{
		while(!m_Ready)
			core::multithreading::yield();
		if(m_TockensList.size() == 0)
			std::clog << "Wrong token list" << std::endl;
		EString name = m_TockensList[m_TockensList.size() - 1];//m_TockensList.back();
		lua_getglobal(Lua, m_TockensList[0].c_str());
		//*
		if(lua_gettop(Lua) == 0)
		{
			//lua_pop(Lua,2);
			std::clog << "Function \"" << name << "\" is not found" << std::endl;
			throw core::lua::FunctionException(name);
		}
		//*
		for(unsigned i = 1; i < m_TockensList.size() - 1; i++)
		{
			lua_getfield(Lua,-1,m_TockensList[i].c_str());
			if(!lua_istable(Lua,-1))
			{
				lua_pop(Lua,2);
				std::clog << "Function \"" << name << "\" is not found" << std::endl;
				throw core::lua::FunctionException(name);
			}
			lua_remove(Lua,-2);
		}
		if(m_TockensList.size() != 1)
			lua_getfield(Lua,-1,m_TockensList[m_TockensList.size() - 1].c_str());
		//*/
		//Our function is now on top. Check it (and throw an exception, if the value is not a function. e.g. is a nill value)
		//*
		if(!lua_isfunction(Lua,-1))
		{
			std::clog << "\"" << name << "\" is not a function" << std::endl;
			throw core::lua::FunctionException(name);
		}
		//*/
		//		std::cout << "pushOnTop: top value " << lua_gettop(Lua) << std::endl;
		m_OnTop = true;
	}
}

void LuaFunction::clear()
{
	lua_State* Lua = GetLua;
	if(m_OnTop)
	{
		lua_pop(Lua,1);
		m_OnTop = false;
	}
}

const Variable&	LuaFunction::call(const Variable*  var)
{
	setParameters(var);
	return call();
}

const Variable&	LuaFunction::call()
{
	lua_State* Lua = GetLua;
	//	std::cout << "Calling lua fuction: ( " << m_NumArgs << ", " << m_NumRet << " )" << std::endl;
	pushOnTop();

	for(unsigned i = 0;i < m_NumArgs;i++)
		core::EngineCore::getLuaCore()->pushValue(m_Args[i]);
#if 1
	if(lua_pcall(Lua,m_NumArgs,m_NumRet,0))
	{
		//Error while parsing string
		const char* err = lua_tostring(Lua,-1);
		throw lua::FunctionException("Error calling a function",err);
	}
#else
	lua_settop(Lua,0);
#endif
	if(m_NumRet)
		for(int i = m_NumRet - 1;i >= 0; i--)
		{
		//	std::cout << "Popping var " << i << std::endl;
			m_RetVals[i] = core::EngineCore::getLuaCore()->popValue();
		//	std::cout << "Result: " << m_RetVals[i] << std::endl;
		}

	m_OnTop = false;
	//	std::cout << "top value " << lua_gettop(Lua) << std::endl;
	if(m_NumRet)
		return m_RetVals[0];
	else
		return m_Fake;
}

const Variable&
LuaFunction::getRetVal(unsigned index) const
{
	if(index < m_NumRet)
	{
		//std::cout << "Ret val " << index << " is " << m_RetVals[index] << std::endl;
		return m_RetVals[index];
	}
	else
		return m_Fake;
}

}
}
