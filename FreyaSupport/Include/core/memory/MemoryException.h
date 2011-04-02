/*
 * MemoryException.h
 *
 *  Created on: 24.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYEXCEPTION_H_
#define MEMORYEXCEPTION_H_

/*
 *
 */


#include "core/EngineException.h"
namespace core
{

namespace memory
{
class MemoryException : public EngineException
{
public:
	MemoryException(const EString& mesg = "Memory exception") : m_Msg(EString("[Memory]: ") + mesg)
	{
	}
	virtual ~MemoryException() throw()
	{
	}

	virtual EString		message() const
	{
		return m_Msg;
	}
private:
	EString		m_Msg;
};

}

}

#endif /* MEMORYEXCEPTION_H_ */
