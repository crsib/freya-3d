/*
 * World.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file
 *  Created on: Dec 29, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef AABB_H_
#define AABB_H_

#include "scenegraph/Structures.h"
#include <BulletCollision/BroadphaseCollision/btDbvt.h>

namespace scenegraph
{
class AABB : public btDbvtAabbMm
{
public:
	MEMORY_FUNCTIONS

};
}


#endif
