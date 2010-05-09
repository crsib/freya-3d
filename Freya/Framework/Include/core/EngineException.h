/*
 * EngineException.h
 *
 *  Created on: 26.09.2008
 *      Author: vedenko
 */

#ifndef ENGINEEXCEPTION_H_
#define ENGINEEXCEPTION_H_

/*
 *
 */

#include "core/EString.h"
#include "core/EngineSubsystem.h"
#include "internal.h"
#include <exception>
//! Base exception class for all Freya exceptions
/*!
 * All Freya exceptions should be inherited from from this class
 */
class EXPORT EngineException : public std::exception
{
public:
	EngineException()
	{
	}
	virtual ~EngineException() throw ()
	{
	}
	//! Retrieves the exception message
	/*!
	 * Retrieves the exception message
	 * \return exception message
	 */
	virtual
	EString message() const
	{
		return "Engine exception occurred";
	}

	virtual
	const char* what  	() const throw ()
	{
		return message().c_str();
	}
};

#endif /* ENGINEEXCEPTION_H_ */
