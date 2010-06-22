#include "FreyaReflect.h"
#include <exception>
#include <string>

#include <iostream>

class	ASTException : public std::exception
{
public:
	ASTException(const std::string& msg) : m_What(std::string("[ASTParser]: ") + msg) {}
	virtual  ~ASTException(){}
	virtual const char *  what() const
	{
		return m_What.c_str();
	}
private:
	std::string		m_What;
};

