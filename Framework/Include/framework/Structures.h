/*
 * Structures.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "core/memory/MemoryAllocator.h"
#include "core/memory/MemoryArena.h"
#include "resources/Resource.h"
#include "core/EString.h"

#include "renderer/RenderingAPIDriver.h"

//STL

#include <map>
#include <vector>
#include <list>

//Math

#include "math/math.hpp"

//Memory routines
#include "internal.h"

#ifdef _FREYA_SHARED_PLUGIN
namespace core
{
namespace memory
{
extern void* (*Allocate)(size_t,unsigned);
extern void  (*Free)(void*,unsigned);
}
}
#else
namespace core
{
namespace memory
{
EXPORT void* Allocate(size_t,unsigned);
EXPORT void  Free(void*,unsigned);
}
}
#endif

#define MEMORY_FUNCTIONS \
		static void* operator new(size_t sz)\
		{\
	return core::memory::Allocate(sz,core::memory::WORLD_POOL);\
		}\
		\
		static void  operator delete(void* p)\
		{\
			core::memory::Free(p,core::memory::WORLD_POOL);\
		}\
		\
		static void* operator new[](size_t sz)\
		{\
			return core::memory::Allocate(sz,core::memory::WORLD_POOL);\
		}\
		\
		static void  operator delete[](void* p)\
		{\
			core::memory::Free(p,core::memory::WORLD_POOL);\
		}\
//End of memory routines

namespace framework
{


typedef struct __Tile
{
	float		left;
	float		top;
	float		right;
	float		bottom;

	__Tile() : left(0.0f),top(0.0f),right(0.0f),bottom(0.0f){}
	MEMORY_FUNCTIONS

} WorldTile;

class SceneNode;

typedef struct	__Resource
{
	EString			resourceID;
	union
	{
		//! true if this is a world leaf
		bool				isLoaded;
		void*				_;
	};
	resources::Resource*	resource;
	SceneNode*				node;

	unsigned				lodLevel;

	__Resource() : resourceID(""),isLoaded(false),resource(NULL),node(NULL),lodLevel(0){}
	~__Resource();
	MEMORY_FUNCTIONS
} WorldResource,*WorldResourcePtr;

typedef	struct	__Data
{
	WorldResourcePtr	landscape;
	typedef std::vector<SceneNode*, core::memory::MemoryAllocator<SceneNode*> > WorldNodes;
	WorldNodes			nodes;

	__Data() : landscape (NULL){}
	~__Data();
} WorldData;

//!World is reperesented as quad tree. This type represent an abstraction of world node
typedef struct __WorldTreeNode
{
	//! Node children
	__WorldTreeNode*		children[4];
	union
	{
		//! true if this is a world leaf
		bool				isLeaf;
		void*				_;
	};
	//Parent node. NULL, if node is a root node
	__WorldTreeNode*		parent;

	WorldTile				tile;
	WorldData				data;

	unsigned				nodeID;

	EString					nodeRes;

	enum ChildType
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	__WorldTreeNode();
	__WorldTreeNode(__WorldTreeNode* parent, ChildType type, unsigned nodeID);
	~__WorldTreeNode();
	MEMORY_FUNCTIONS

} WorldTreeNode,*WorldTreeNodePtr;

typedef struct __File
{
	void*		data;
	size_t		size;

	void free();

	__File() : data (NULL), size(0){}
	~__File();
} File,FilePtr;

}

#endif /* STRUCTURES_H_ */
