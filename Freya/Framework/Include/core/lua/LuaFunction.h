/*
 * LuaFunction.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef LUAFUNCTION_H_
#define LUAFUNCTION_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include <lua.hpp>
#include "core/EStringList.h"
#include "core/EString.h"

namespace core
{

class Variable;
namespace lua
{

class LuaFunction: public EngineSubsystem
{
	friend class LuaCore;
protected:
	explicit LuaFunction(const EString& name,unsigned NumArgs,unsigned NumRet);
	virtual ~LuaFunction();

public:
	typedef std::vector<Variable*,core::memory::MemoryAllocator<Variable*> > VariableVector;
	//Calling function
	VariableVector call(Variable* vars);
	VariableVector call();//Variable is taken from previously setted list
	//Setting variables
	void setParameters(Variable* vars);
	void setParameter(unsigned index,const Variable& var);
private:
	void pushOnTop();
	void clear();

	unsigned	m_NumArgs;
	VariableVector	m_Args;

	unsigned 	m_OnTop;

	unsigned	m_NumRet;
	VariableVector m_RetVals;

	EStringList	m_TockensList;
};
}
}

#endif /* LUAFUNCTION_H_ */
