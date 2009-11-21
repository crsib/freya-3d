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

#include "core/xml/XMLParser.h"

namespace framework
{
class World;
struct __Data;
class SceneNode : public virtual EngineSubsystem
{
	friend class World;
	friend struct __Data;
protected:
	SceneNode( core::xml::DOMNode*	root);
	virtual ~SceneNode( );

private:

};

}

#endif /* SCENENODE_H_ */
