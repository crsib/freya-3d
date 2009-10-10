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

#include <algorithm>

namespace core
{
namespace lua
{
#define Lua core::EngineCore::getLuaCore()->m_VirtualMachine
LuaFunction::LuaFunction(const EString& name,unsigned NumArgs,unsigned NumRet)
{
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
	lua_pop(Lua,2);
	//Reserve space for num arg and rets
	m_NumArgs = NumArgs;
	m_NumRet =  NumRet;
	m_Args.reserve(NumArgs);
	m_RetVals.reserve(NumRet);
	//Our function is not on top
	m_OnTop = false;
}

LuaFunction::~LuaFunction()
{
	// TODO Auto-generated destructor stub
}

void LuaFunction::setParameter(unsigned index,const Variable& var)
{
	m_Args[index] = const_cast<Variable*>(&var);
}

void LuaFunction::setParameters(core::Variable* var)
{
	for(unsigned i = 0;i < m_NumArgs; i++)
	{
		m_Args[i] = const_cast<Variable*>(&var[i]);
	}
}

void LuaFunction::pushOnTop()
{
	if(!m_OnTop)
	{
		lua_getglobal(Lua, m_TockensList[0].c_str());
		std::cout << "Pushing table up: " << lua_gettop(Lua) << std::endl;
		for(unsigned i = 1; i < m_TockensList.size() - 1; i++)
		{
			lua_getfield(Lua,-1,m_TockensList[i].c_str());
			if(!lua_istable(Lua,-1))
			{
				lua_pop(Lua,2);
				std::clog << "Function is not found as lua state changed" << std::endl;
				throw lua::FunctionException("Lua state criticaly changed","something changed the stack");
			}
			lua_remove(Lua,-2);
			std::cout << "Pushing table up: " << lua_gettop(Lua) << std::endl;
		}
		std::cout << "Pushing up: " << lua_gettop(Lua) << std::endl;
		if(m_TockensList.size() != 1)
		{
			lua_getfield(Lua,-1,m_TockensList[m_TockensList.size() - 1].c_str());
			lua_remove(Lua,-2);
		}
		std::cout << "Pushed up: " << lua_gettop(Lua) << std::endl;
		m_OnTop = true;
	}
}

void LuaFunction::clear()
{
	if(m_OnTop)
	{
		lua_pop(Lua,1);
		m_OnTop = false;
	}
}

LuaFunction::VariableVector	LuaFunction::call(core::Variable* var)
{
	setParameters(var);
	return call();
}

LuaFunction::VariableVector	LuaFunction::call()
{
	pushOnTop();
	for(unsigned i = 0;i < m_NumArgs;i++)
		core::EngineCore::getLuaCore()->pushValue(*m_Args[i]);
	if(lua_pcall(Lua,m_NumArgs,m_NumRet,0))
	{
		//Error while parsing string
		const char* err = lua_tostring(Lua,-1);
		throw lua::FunctionException("Error calling a function",err);
	}
	for(unsigned i = 0;i < m_NumRet; i++)
	{
		Variable& var = core::EngineCore::getLuaCore()->popValue();
		m_RetVals.push_back(&var);
	}
	std::reverse(m_RetVals.begin(),m_RetVals.end());
	m_OnTop = false;
	return m_RetVals;
}
}
}