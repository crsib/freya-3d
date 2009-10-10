#ifndef FUNCTIONEXCEPTION_H_
#define FUNCTIONEXCEPTION_H_

#include "core/lua/LuaException.h"

namespace core
{

namespace lua
{

class FunctionException : public core::lua::LuaException
{
public:
	FunctionException(const EString& name)
	{
		m_Msg = EString("Function \"") + name + EString("\" does not exists");
	}
	FunctionException(const EString& msg,const EString& err)
	{
		m_Msg = msg + EString("\nSynopsis: ") + err;
	}
	virtual ~FunctionException() {}
	virtual EString message() const
	{
		return m_Msg;
	}
private:
	EString m_Msg;
};

}

}

#endif /*FUNCTIONEXCEPTION_H_*/
