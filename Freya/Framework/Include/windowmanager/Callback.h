#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "core/EngineSubsystem.h"
//#include "core/Variable.h"

/*
 * This class decribes an abstraction of callback mechanism
 * It is added because of two problems:
 * 1. Template function cannot be virtual in C++
 * 2. Lua does not support typecasting
 *
 * To override this, the folowing class is used to register callback for a message
 *
 * This class can also be used for "user" message callback.
 * Class provides calling of function with two argument from both c++/lua
 * Class also contains two constructors
 */

namespace windowmanager
{
class Callback : virtual public ::EngineSubsystem
{
private:
	Callback()
	{
		m_Cpp_Function = 0;
	}
public:
	virtual ~Callback() {}
	Callback(void (* f)())
	{
		m_Cpp_Function = reinterpret_cast<void*>(f);
	}
#ifdef VARIADIC_AVAILABLE
	template<typename... T1>
	Callback(void (* func_addr)(T1...))
	{
		m_Cpp_Function = reinterpret_cast<void*>(func_addr);
		m_Lua_Function = NULL;
	}

	template<typename... T> void call(const T&... vals)
	{
		if(m_Cpp_Function) //c++ function
		{
			void (*f)(const T&...) = reinterpret_cast<void (*)(const T&...)>(m_Cpp_Function);
			f(vals...);
		}
	}
#else

	template<typename T1, typename T2>
	Callback(void (* func_addr)(T1,T2))
	{
		m_Cpp_Function = reinterpret_cast<void*>(func_addr);
	}

	template<typename T1, typename T2, typename T3>
	Callback(void (* func_addr)(T1,T2,T3))
	{
		m_Cpp_Function = reinterpret_cast<void*>(func_addr);
	}

	template<typename T1, typename T2, typename T3,typename T4>
	Callback(void (* func_addr)(T1,T2,T3,T4))
	{
		m_Cpp_Function = reinterpret_cast<void*>(func_addr);
	}

	template<typename T1, typename T2, typename T3,typename T4,typename T5>
	Callback(void (* func_addr)(T1,T2,T3,T4,T5))
	{
		m_Cpp_Function = reinterpret_cast<void*>(func_addr);
	}

	void call()
	{
		if(m_Cpp_Function) //c++ function
		{
			void (*f)() = reinterpret_cast<void (*)()>(m_Cpp_Function);
			f();
		}
	}

	template<typename T1>
	void call(const T1& p1)
	{
		if(m_Cpp_Function) //c++ function
		{
			void (*f)(const T1& p1) = reinterpret_cast<void (*)(const T1& p1)>(m_Cpp_Function);
			f(p1);
		}
	}

	template<typename T1,typename T2>
	void call(const T1& p1,const T2& p2)
	{
		if(m_Cpp_Function) //c++ function
		{
			void (*f)(const T1& p1,const T2& p2) = reinterpret_cast<void (*)(const T1& p1,const T2& p2)>(m_Cpp_Function);
			f(p1,p2);
		}
	}

#endif

	Callback& operator = (const Callback& callback)
	{
		m_Cpp_Function = callback.m_Cpp_Function;
		return *this;
	}

	Callback(const Callback& callback)
	{
		m_Cpp_Function = callback.m_Cpp_Function;
	}
private:
	void*			m_Cpp_Function;
	unsigned		n_Pars;
};

}
#endif /*CALLBACK_H_*/
