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
#include <stdint.h>

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

typedef struct __File : public ::EngineSubsystem
{
	void*		data;
	size_t		size;

	void free();

	__File() : data (NULL), size(0){}
	virtual ~__File();
} File,*FilePtr;

typedef
struct __VBO_BatchHeader : public ::EngineSubsystem
{
	 uint32_t						assembly_type;
	 uint16_t   					index_count;
	 uint16_t						buffer_offset;
	 renderer::VertexElement*		layout;
	 __VBO_BatchHeader() : assembly_type(0),index_count(0),buffer_offset(0),layout(NULL){}
} VBO_BatchHeader,*VBO_BatchHeaderPtr;

typedef
struct __VBOData : public ::EngineSubsystem
{
	uint32_t						num_batches;
	VBO_BatchHeaderPtr				batches;
	uint16_t						number_of_indicies;
	renderer::VertexBufferObject*	indicies;
	uint32_t						size_of_vertex_data;
	renderer::VertexBufferObject*	vertex_data;
	__VBOData() : num_batches(0),batches(NULL),number_of_indicies(0),indicies(NULL),size_of_vertex_data(0), vertex_data(NULL){}
} VBOData,*VBODataPtr;

typedef
struct	__GeometryBatch : public ::EngineSubsystem
{
	uint32_t						shader_id; //Shader id in shader library
	uint32_t						number_of_textures;
	renderer::Texture**				textures;
	uint32_t						batch_id;
	VBODataPtr						vbo;
	uint32_t						r2vb;//Pass is r2vb
	renderer::VertexBufferObject*	r2vbTarget;
} GeometryBatch,*GeometryBatchPtr; //This is a geometry batch

enum SHADER_BIND_TYPE
{
	INT,
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4,
	MAT3x3,
	MAT4x4,
	SAMPLER,
	VIEW,
	WORLD,
	PROJECTION
};

typedef
struct __ShaderBinding : public ::EngineSubsystem
{
	uint32_t	type;
	EString		name;
	union
	{
		int32_t			INT;
		float			FLOAT;
		float			FLOAT2[2];
		float			FLOAT3[3];
		float			FLOAT4[4];
		float			MAT3x3[9];
		float			MAT4x4[16];
		uint32_t		SAMPLER;
	};
} ShaderBinding,*ShaderBindingPtr;

typedef struct __ShaderWrapper : public ::EngineSubsystem
{
	renderer::Shader*			shader;
	uint16_t					num_uniform_bindings;
	uint16_t					num_attribute_bindings;
	ShaderBindingPtr			uniform_bindings;
	ShaderBindingPtr			attribute_bindings;
} ShaderWrapper,*ShaderWrapperPtr;

typedef
struct	__ShaderLibrary : public ::EngineSubsystem
{
	uint32_t					num_shaders;
	ShaderWrapperPtr			shaders;
	EString						apiName;
} ShaderLibrary,*ShaderLibraryPtr;

}

#endif /* STRUCTURES_H_ */
