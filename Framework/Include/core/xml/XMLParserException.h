#ifndef _XMLEXCEPTION_H_
#define _XMLEXCEPTION_H_

#include "core/EngineException.h"

namespace core
{
namespace xml
{

class XMLParserException : public ::EngineException
{
public:
	XMLParserException() : m_Msg("[XML]: unknown exception")
	{
	}
	explicit XMLParserException(const EString& msg) : m_Msg("[XML]: exception: ")
	{
		m_Msg += msg;
	}
	virtual ~XMLParserException()throw()
	{
	}

	virtual EString message() const
	{
		return m_Msg;
	}

private:
	EString m_Msg;

}; //End of XMLException class

} //End of xml namespace
} //End of core namespace
#endif //End of _XMLEXCEPTION_H_
