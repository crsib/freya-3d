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
#include "core/Variable.h"

namespace core
{

namespace lua
{

class LuaFunction: public EngineSubsystem
{
	friend class LuaCore;
public:
	explicit LuaFunction(const EString& name,unsigned NumArgs,unsigned NumRet);
	virtual ~LuaFunction();
	LuaFunction(const LuaFunction&);
	LuaFunction&	operator = (const LuaFunction&);

public:
	//Calling function
	const Variable& call(const Variable* vars);
	const Variable& call();//Variable is taken from previously setted list


	//operator ()
	const Variable& operator () ();
	template<typename T1>
	const Variable& operator () (const T1&);
	template<typename T1,typename T2>
	const Variable& operator () (const T1&,const T2&);
	template<typename T1,typename T2,typename T3>
	const Variable& operator () (const T1&,const T2&,const T3&);
	template<typename T1,typename T2,typename T3,typename T4>
	const Variable& operator () (const T1&,const T2&,const T3&,const T4&);
	template<typename T1,typename T2,typename T3,typename T4,typename T5>
	const Variable& operator () (const T1&,const T2&,const T3&,const T4&,const T5&);
	//Setting variables
	void setParameters(const Variable* );
	void setParameter(unsigned index,const Variable& var);

	const Variable& getRetVal(unsigned index) const;
private:
	void pushOnTop();
	void clear();

	Variable	m_Fake;
	unsigned	m_NumArgs;
	Variable*	m_Args;

	unsigned 	m_OnTop;

	unsigned	m_NumRet;
	Variable*	m_RetVals;

	EStringList	m_TockensList;
};
}
}

//================Implemetation===========================================================
namespace core
{
namespace lua
{
inline
const Variable& LuaFunction::operator () ()
{
	return call();
}

template<typename T1>
const Variable& LuaFunction::operator () (const T1& _1)
{
	if(m_NumArgs >= 1)
		m_Args[0] = _1;
	return call();
}

template<typename T1,typename T2>
const Variable& LuaFunction::operator () (const T1& _1,const T2& _2)
{
	if(m_NumArgs >= 1)
		m_Args[0] = _1;
	if(m_NumArgs >= 2)
		m_Args[1] = _2;
	return call();
}

template<typename T1,typename T2,typename T3>
const Variable& LuaFunction::operator () (const T1& _1,const T2& _2,const T3& _3)
{
	if(m_NumArgs >= 1)
		m_Args[0] = _1;
	if(m_NumArgs >= 2)
		m_Args[1] = _2;
	if(m_NumArgs >= 3)
		m_Args[2] = _3;
	return call();
}

template<typename T1,typename T2,typename T3,typename T4>
const Variable& LuaFunction::operator () (const T1& _1,const T2& _2,const T3& _3,const T4& _4)
{
	if(m_NumArgs >= 1)
		m_Args[0] = _1;
	if(m_NumArgs >= 2)
		m_Args[1] = _2;
	if(m_NumArgs >= 3)
		m_Args[2] = _3;
	if(m_NumArgs >= 4)
		m_Args[3] = _4;
	return call();
}

template<typename T1,typename T2,typename T3,typename T4,typename T5>
const Variable& LuaFunction::operator () (const T1& _1,const T2& _2,const T3& _3,const T4& _4,const T5& _5)
{
	if(m_NumArgs >= 1)
		m_Args[0] = _1;
	if(m_NumArgs >= 2)
		m_Args[1] = _2;
	if(m_NumArgs >= 3)
		m_Args[2] = _3;
	if(m_NumArgs >= 4)
		m_Args[3] = _4;
	if(m_NumArgs >= 5)
		m_Args[5] = _5;
	return call();
}
}
}


#endif /* LUAFUNCTION_H_ */
