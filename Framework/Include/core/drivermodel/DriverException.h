#ifndef _DRIVEREXCEPTION_H_
#define _DRIVEREXCEPTION_H_

#include "core/PluginCore.h"
#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
	extern core::PluginCore*	CoreInstance;
}
#else
namespace core
{
	extern core::PluginCore*	CoreInstance;
}
#endif

#include "core/EngineException.h"

namespace core
{
namespace drivermodel
{
//! Exception class for Freya drivers
/*!
 * It is recommended for Freya drivers to throw the successors of this class
 */
class DriverException : public ::EngineException
{
public:
	DriverException(): m_Msg("[Driver subsystem]: Unknown driver exception"){}
	DriverException(const EString& msg) : m_Msg("[Driver subsystem]: ")
	{
		m_Msg += msg;
	}
	virtual ~DriverException(){}
	//! Retrieves the exception message
	/*!
	 * Retrieves the exception message
	 * \return exception message
	 */
	virtual EString message() const
	{
		return m_Msg;
	}

private:
	EString m_Msg;
}; //End of DriverException class

} //End of drivermodel namespace
} //End of core namespace
#endif //End of _DRIVEREXCEPTION_H_
