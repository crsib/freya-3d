#ifndef VALUEEXCEPTION_H_
#define VALUEEXCEPTION_H_

#include "core/lua/LuaException.h"

namespace core
{
namespace lua
{

class VariableException : public core::lua::LuaException
{
public:
	VariableException(const EString& name)
	{
		m_Msg = EString("[LUA] Value \"") + name + EString("\" is of unsupported type or not found");
	}
	virtual ~VariableException() {}
	virtual EString message() const
	{
		return m_Msg;
	}
private:
	EString 	m_Msg;
};

}
}

#endif /*VALUEEXCEPTION_H_*/
