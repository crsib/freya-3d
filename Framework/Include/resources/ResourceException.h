/*
 * ResourceException.h
 *
 *  Created on: 20.05.2009
 *      Author: vedenko
 */

#ifndef RESOURCEEXCEPTION_H_
#define RESOURCEEXCEPTION_H_

/*
 *
 */
#include "core/EngineException.h"

namespace resources
{
//! Exception class for resource managment subsystem
class ResourceException: public EngineException
{
public:
	ResourceException() : m_Msg("[resources]: Unknown exception")
	{

	}
	ResourceException(const EString& msg) : m_Msg("[resource]: ")
	{
		m_Msg += msg;
	}
	virtual ~ResourceException() throw()
	{
	}

	virtual EString message() const
	{
		return m_Msg;
	}

private:
	EString		m_Msg;
};

}

#endif /* RESOURCEEXCEPTION_H_ */
