#ifndef _WMEXCEPTION_H_
#define _WMEXCEPTION_H_

#include "core/EngineException.h"
#include "internal.h"

namespace windowmanager
{

class EXPORT WMException : public ::EngineException
{
public:
	WMException();
	WMException(const EString& s)
	{
		m_Msg = s;
	}
	virtual ~WMException();

	virtual EString message() const;
private:
	EString m_Msg;

}; //End of WMException class

} //End of windowmanager namespace

#endif //End of _WMEXCEPTION_H_
