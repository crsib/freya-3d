#ifndef _FILESYSTEMEXCEPTION_H_
#define _FILESYSTEMEXCEPTION_H_

#include "core/EngineException.h"

namespace core
{
namespace filesystem
{
//!Filesystem exception class
/*!
 * Any filesystem errors should be reported using this class
 */
class FilesystemException : public ::EngineException
{
public:
	FilesystemException()
	{
		m_Msg = "Unknown filesystem exception";
	}
	explicit FilesystemException(const EString& msg )
	{
		m_Msg = msg;
	}
	virtual ~FilesystemException()
	{}
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
	EString		m_Msg;
}; //End of FilesystemException class

} //End of filesystem namespace
} //End of core namespace
#endif //End of _FILESYSTEMEXCEPTION_H_
