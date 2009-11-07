/*
 * FrameworkImpl.cpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#include "framework/Structures.h"
#include "resources/ResourceManager.h"
#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "framework/SceneNode.h"
namespace framework
{

__Resource::~__Resource()
{
	core::EngineCore::getResourceManager()->free(resource);
	resource = NULL;
	isLoaded = false;
}

__Data::~__Data()
{
	delete landscape;
	landscape = NULL;
	for(size_t i = 0; i < nodes.size(); i++ )
	{
		delete nodes[i];
	}
	nodes.clear();
}

__WorldTreeNode::__WorldTreeNode()
{
	children[0]
	         = children[1]
	                    = children[2]
	                               = children[3]
	                                          = parent = NULL;
	isLeaf = true;
	nodeID = 0;
}

__WorldTreeNode::~__WorldTreeNode()
{
	if(!isLeaf)
	{
		delete children[0];
		children[0] = NULL;
		delete children[1];
		children[1] = NULL;
		delete children[2];
		children[2] = NULL;
		delete children[3];
		children[3] = NULL;
	}
	nodeID = 0;
}

__WorldTreeNode::__WorldTreeNode(__WorldTreeNode* parent, ChildType type,unsigned n)
{
	children[0]
	         = children[1]
	                    = children[2]
	                               = children[3]
	                                          =  NULL;
	isLeaf = true;
	this->parent = parent;
	parent->isLeaf = false;
	nodeID = n;

	switch(type)
	{
		case TopLeft:
			tile.top 	= parent->tile.top;
			tile.left 	= parent->tile.left;
			tile.bottom = (parent->tile.top + parent->tile.bottom)*0.5f;
			tile.right  = (parent->tile.right + parent->tile.left)*0.5f;
			break;
		case TopRight:
			tile.top 	= parent->tile.top;
			tile.left 	= (parent->tile.right + parent->tile.left)*0.5f;
			tile.bottom = (parent->tile.top + parent->tile.bottom)*0.5f;
			tile.right  = parent->tile.right;
			break;
		case BottomLeft:
			tile.top 	= (parent->tile.top + parent->tile.bottom)*0.5f;
			tile.left 	= parent->tile.left;
			tile.bottom = parent->tile.bottom;
			tile.right  = (parent->tile.right + parent->tile.left)*0.5f;
			break;

		case BottomRight:
			tile.top 	= (parent->tile.top + parent->tile.bottom)*0.5f;
			tile.left 	= (parent->tile.right + parent->tile.left)*0.5f;
			tile.bottom = parent->tile.bottom;
			tile.right  = parent->tile.right;
			break;
	}
}

__File::~__File()
{
	if(data)
		core::memory::Free(data,core::memory::GENERIC_POOL);
	data = NULL;
	size = 0;
}

void __File::free()
{
	if(data)
		core::memory::Free(data,core::memory::GENERIC_POOL);
	data = NULL;
	size = 0;
}

}
