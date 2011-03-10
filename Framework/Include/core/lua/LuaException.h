#ifndef LUAEXCEPTION_H_
#define LUAEXCEPTION_H_

#include "core/EngineException.h"

namespace core
{
namespace lua 
{

class LuaException : public EngineException
{
public:
	LuaException() : m_Msg("[LUA]: unknown Lua internal error"){}
	LuaException(const EString& msg)
	{
		m_Msg = EString("[LUA]: Lua internal error: ") + msg;
	}
	virtual ~LuaException() throw(){}

	virtual EString message() const
	{
		return m_Msg;
	}

private:
	EString m_Msg;
};

}
}

#endif /*LUAEXCEPTION_H_*/
