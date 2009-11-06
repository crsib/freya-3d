/*
 * SceneNode.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef SCENENODE_H_
#define SCENENODE_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace framework
{

class SceneNode : public virtual EngineSubsystem
{
public:
	SceneNode( );
	virtual ~SceneNode( );
};

}

#endif /* SCENENODE_H_ */
