/*
 * SceneNode.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Dec 29, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef SCENENODE_H_
#define SCENENODE_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "internal.h"

namespace scenegraph
{

class EXPORT SceneNode : public EngineSubsystem
{
public:
	SceneNode( );
	virtual ~SceneNode( );

	//======== Public enums ================================
	enum	NODE_TYPE
	{

	};

	//======== Public functions=============================

	NODE_TYPE					type() const;
protected:
	NODE_TYPE					m_Type;
private:

};


//=============== Implementation ===========================

inline SceneNode::NODE_TYPE
SceneNode::type() const
{
	return m_Type;
}

}

#endif /* SCENENODE_H_ */
