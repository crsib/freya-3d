/*
 * EmissionObject.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef EMISSIONOBJECT_H_
#define EMISSIONOBJECT_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "renderer/DriverSubsystems/Shader.h"
//TODO: finish interface and documentation
namespace framework
{

class EmissionObject: public virtual EngineSubsystem
{
public:
	virtual ~EmissionObject() {}

	virtual bool	castsShadows();

	virtual renderer::Shader*	shader() = 0;

};

}

#endif /* EMISSIONOBJECT_H_ */
