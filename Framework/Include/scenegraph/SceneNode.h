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

#include "math/math.hpp"
#include <vector>
#include <map>

#include "core/memory/MemoryAllocator.h"
#include "core/EString.h"

#include "scenegraph/AABB.h"
#include "scenegraph/SceneNodeController.h"
#include "scenegraph/Structures.h"

namespace scenegraph
{

class World;

class EXPORT SceneNode : public virtual EngineSubsystem
{
	friend class World;
protected:
	SceneNode(unsigned id,const EString& name);
	virtual ~SceneNode( );
public:
	//======== Public enums ================================
	enum	NODE_TYPE
	{
		NODE_TYPE_BASE,
		NODE_TYPE_LIGHT,
		NODE_TYPE_CAMERA,
		NODE_TYPE_STATIC_GEOMETRY,
		NODE_TYPE_SKINNED_GEOMETRY,
		NODE_TYPE_BONE,

		NODE_TYPE_COUNT
	};

	enum 	DETACH_MODE
	{
		DETACH_MODE_DETACH_CHILDREN,
		DETACH_MODE_REATTACH_CHILDREN
	};

	//======== Public typedefs ============================
	typedef std::vector<SceneNode*,core::memory::MemoryAllocator<SceneNode*> > SceneNodeList;
	typedef std::multimap<unsigned,SceneNodeController*,std::less<unsigned>,core::memory::MemoryAllocator< std::pair<const unsigned,SceneNodeController*> > > SceneNodeControllerMap;
	//======== Public functions ============================

	NODE_TYPE					type() const;

	//======== Reference counting ==========================
	size_t						referenceCount() const;

	//======= Graph functions ==============================
	size_t						parentCount() const;
	SceneNode*					getParent(unsigned idx = 0);

	size_t						childrenCount() const;
	SceneNode*					getChild(unsigned idx);

	void						addChild(SceneNode* node);

	void						detach(SceneNode* parent,DETACH_MODE mode = DETACH_MODE_DETACH_CHILDREN);

	//======= Node ID ======================================
	unsigned					nodeId() const;
	EString						nodeName() const;
	EString						qualifiedName() const;
	//======= Public members ===============================
	math::vector3d				translation;
	math::quaternion			orientation;
	math::vector3d				scale;
	//======= Transformations ==============================
	math::matrix4x4				getWorldTransform(unsigned forParentIdx		  = 0) const;
	AABB						getBoundingBox(unsigned forParentTransformIdx = 0) const;
	//======= Updating/controlling/batch submission ========
	virtual void				update(float dt);

	void						attachController(unsigned priority,SceneNodeController* controller);
	void						detachController(SceneNodeController* controller);

	scenegraph::BatchList&		opaqueBatches();
	scenegraph::BatchList&		transparentBatches();

	//====== Data manipulation ============================
	virtual void				preloadData();
	bool						ready() const;

protected:
	//====== Protected functions ===========================
	void						addParent(SceneNode* node);
	void						reaattach(SceneNode* from, SceneNode* to);
	//====== Protected members =============================
	NODE_TYPE					m_Type;
	size_t						m_ReferenceCount;

	SceneNodeList				m_Parents;
	SceneNodeList				m_Children;

	unsigned 					m_NodeId;
	EString						m_NodeName;
	EString						m_FullName;

	AABB						m_BoundingBox;

	SceneNodeControllerMap		m_SceneNodeControllers;

	BatchList					m_OpaqueBatches;
	BatchList 					m_TransparentBatches;

	bool						m_NodeReadyForRendering;
private:

};


//=============== Implementation ===========================

inline SceneNode::NODE_TYPE
SceneNode::type() const
{
	return m_Type;
}

inline
size_t 						SceneNode::referenceCount() const
{
	return m_ReferenceCount;
}

inline
size_t						SceneNode::parentCount() const
{
	return m_Parents.size();
}

inline
size_t						SceneNode::childrenCount() const
{
	return m_Children.size();
}

inline
unsigned					SceneNode::nodeId() const
{
	return m_NodeId;
}

inline
EString						SceneNode::nodeName() const
{
	return m_NodeName;
}

inline
EString						SceneNode::qualifiedName() const
{
	return m_FullName;
}


inline
BatchList&					SceneNode::opaqueBatches()
{
	return m_OpaqueBatches;
}

inline
BatchList&					SceneNode::transparentBatches()
{
	return m_TransparentBatches;
}

inline
bool						SceneNode::ready() const
{
	return m_NodeReadyForRendering;
}

}

#endif /* SCENENODE_H_ */
