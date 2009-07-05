/*
 * ShaderException.h
 *
 *  Created on: 26.09.2008
 *      Author: vedenko
 */

#ifndef SHADEREXCEPTION_H_
#define SHADEREXCEPTION_H_

/*
 *
 */
#include "core/EngineException.h"
#include "renderer/3DConstants.h"
namespace renderer
{
//! Shader exceptions
/*!
 * All shader exceptions should be inherited from this base class (or be thrown using this class)
 */
class ShaderException: public EngineException
{
public:
	//! Generate message by shader type (described by ShaderType)
	ShaderException(unsigned type)
	{
		m_Message = EString("Shader exception ocured while processing ") +
					EString((type != ShaderType::VERTEX) ? ((type == ShaderType::GEOMETRY) ? "geometry" : "fragment") : ("vertex"))  +
					EString("shader");
		m_Type = type;
	}
	ShaderException()
	{
		m_Message = EString("Shader exception ocured");
		m_Type = static_cast<unsigned>(-1);
	}
	virtual ~ShaderException()
	{
	}
	//! As always, this function returns exception message
	virtual EString message() const
	{
		return m_Message;
	}

	unsigned getShaderType() const
	{
		return m_Type;
	}
private:
	EString		m_Message;
	unsigned    m_Type;
};

}

#endif /* SHADEREXCEPTION_H_ */
