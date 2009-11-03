/*
 * LuaCore.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef LUACORE_H_
#define LUACORE_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
extern "C"
{
	#include "core/lua/luajit.h"
}
#include "core/Variable.h"
#include <vector>
#include "core/memory/MemoryAllocator.h"
#include "core/lua/LuaFunction.h"
#include "core/EString.h"
namespace core
{
	class EngineCore;
namespace lua
{
class LuaCore: public EngineSubsystem
{
	friend class core::EngineCore;
	friend class LuaFunction;
protected:
	LuaCore();
	virtual ~LuaCore();
public:
	//JIT compiler
	enum JITOptimization
	{
		NO_OPTIMIZATION,
		GENERAL_OPTIMIZATION,
		FULL_OPTIMIZATION
	};

	void			startJIT(unsigned OptLevel = FULL_OPTIMIZATION);
	void			stopJIT();

	void			compileFunction(const LuaFunction& func);

	//Variables
	Variable		getValue(const EString& name);//modules are parsed correctly
	void			setValue(const EString& name,const Variable& var);


	void			pushValue(const Variable& var);
	Variable 		popValue();
	//Functions
	LuaFunction		getFuction(const EString& name,unsigned NumArgs,unsigned NumRet);
	//Now, some scripts inclusion/runnig (otherwise, what the hell this parser needed)
	void			runScript(const EString& script);
	void			includeModule(const EString& module_name,const EString& script);
	//Garbage collection
	void			forceGarbageCollector();
	void			restartGarbageCollector();
	void			stopGarbageCollector();

private:
	lua_State*			m_VirtualMachine;
public:
	lua_State*			getVM()
	{
		return m_VirtualMachine;
	}
private:
	unsigned			m_JITInstalled;
	unsigned			m_JITStarted;

	unsigned			m_OptLevel;
};

}
}
#endif /* LUACORE_H_ */
