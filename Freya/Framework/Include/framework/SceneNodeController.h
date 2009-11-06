/*
 * SceneNodeController.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef SCENENODECONTROLLER_H_
#define SCENENODECONTROLLER_H_

/*
 *
 */
#include "core/EngineSubsystem.h"

namespace framework
{

class SceneNodeController : public virtual EngineSubsystem
{
public:
	SceneNodeController( );
	virtual ~SceneNodeController( );
};

}

#endif /* SCENENODECONTROLLER_H_ */
