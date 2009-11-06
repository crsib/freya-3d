/*
 * ShaderException.h
 *
 *  Created on: 26.09.2008
 *      Author: vedenko
 */

#ifndef SHADEREXCEPTION_H_
#define SHADEREXCEPTION_H_

#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif
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
		m_Message = EString("[renderer]: Shader exception ocured while processing ") +
					EString((type != ShaderType::VERTEX) ? ((type == ShaderType::GEOMETRY) ? "geometry" : "fragment") : ("vertex"))  +
					EString("shader. See log for details");
		m_Type = type;
	}
	ShaderException()
	{
		m_Message = EString("[renderer]: Unknown shader exception ocured");
		m_Type = static_cast<unsigned>(-1);
	}
	virtual ~ShaderException() throw()
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
