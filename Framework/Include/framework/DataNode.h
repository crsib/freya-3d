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

#include "Structures.h"


namespace framework
{
class World;
struct __Data;
class DataNode : public virtual EngineSubsystem
{
	friend class World;
	friend struct __Data;
protected:
	DataNode();
	virtual ~DataNode( );

private:

};

}

#endif /* SCENENODE_H_ */
