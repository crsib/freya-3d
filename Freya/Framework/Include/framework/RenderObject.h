/*
 * RenderObject.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef RENDEROBJECT_H_
#define RENDEROBJECT_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace framework
{
//TODO: write documentation
//! This class is a base class for any renderable object
class RenderObject: public virtual EngineSubsystem
{
public:
	virtual ~RenderObject() {}

	virtual void render() = 0;
};

}

#endif /* RENDEROBJECT_H_ */
