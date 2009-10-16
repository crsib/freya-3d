/*
 * SimulationObject.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef SIMULATIONOBJECT_H_
#define SIMULATIONOBJECT_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
//TODO: finish interface and documentation
namespace framework
{

class SimulationObject: public EngineSubsystem
{
public:
	virtual ~SimulationObject() {}

	virtual void 	setAnimation(int animType) = 0;

	virtual void	update(float ms) = 0;

	virtual math::vector3d	position() = 0;
	virtual math::btQuaternion orientation() = 0;
	virtual int				animType();
};

}

#endif /* SIMULATIONOBJECT_H_ */
