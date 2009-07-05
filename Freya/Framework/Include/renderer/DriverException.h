#ifndef DRIVEREXCEPTION_H_
#define DRIVEREXCEPTION_H_

#include "core/EngineException.h"
#include "core/EString.h"
namespace renderer
{
//! Rendering driver exceptions
/*!
 * All rendering driver exceptions should be inherited from this base class (or be thrown using this class)
 */
class DriverException : public EngineException
{
public:
	DriverException(const EString& msg) : m_Msg("[renderer]: ")
	{
		m_Msg += msg;
	}
	DriverException() : m_Msg("[renderer]: Unknown exception")
	{
	}
	virtual ~DriverException() {}
//! As always, this function returns exception message
	virtual EString message() const
	{
		return m_Msg;
	}

private:
	EString  m_Msg;
};

}

#endif /*DRIVEREXCEPTION_H_*/
