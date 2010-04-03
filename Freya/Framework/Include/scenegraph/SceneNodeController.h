/*
 * SceneNodeController.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file
 *  Created on: Dec 29, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef SCENENODECONTROLLER_H_
#define SCENENODECONTROLLER_H_

#include "core/EngineSubsystem.h"
#include "internal.h"

namespace scenegraph
{
class 	SceneNode;
class EXPORT SceneNodeController : public virtual EngineSubsystem
{
public:
	virtual ~SceneNodeController(){}

	virtual void operator () (SceneNode* node, float dt) = 0;
};
}

#endif
