/*
 * StaticGeometryNode.h
 *
 *  Created on: Jan 4, 2010
 *      Author: crsib
 */

#ifndef STATICGEOMETRYNODE_H_
#define STATICGEOMETRYNODE_H_

#include "scenegraph/SceneNode.h"

namespace scenegraph
{

class StaticGeometryNode : public SceneNode
{
public:
	StaticGeometryNode(unsigned id,const EString& name);
	virtual ~StaticGeometryNode( );
};

}

#endif /* STATICGEOMETRYNODE_H_ */
