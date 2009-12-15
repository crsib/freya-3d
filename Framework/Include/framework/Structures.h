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
#ifndef _MSC_VER
#include <stdint.h>
#else
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef  __int16 int16_t;
#endif

#include <map>
#include <vector>
#include <list>

//Math

#include "math/math.hpp"

//Memory routines
#include "internal.h"


namespace core
{
namespace memory
{
EXPORT void* Allocate(size_t,unsigned);
EXPORT void  Free(void*,unsigned);
}
}


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

class DataNode;

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
	DataNode*				node;

	unsigned				lodLevel;

	__Resource() : resourceID(""),isLoaded(false),resource(NULL),node(NULL),lodLevel(0){}
	~__Resource();
	MEMORY_FUNCTIONS
} WorldResource,*WorldResourcePtr;

typedef	struct	__Data
{
	typedef std::vector<DataNode*, core::memory::MemoryAllocator<DataNode*> > WorldDataNodes;
	WorldDataNodes			nodes;

	__Data();
	~__Data();
} WorldData;

typedef struct __Camera
{
	MEMORY_FUNCTIONS
	enum CameraType
	{
		ORTHO,
		PROJECTIVE
	};
	float   near_plane;
	float	far_plane;
	CameraType	type;

	union
	{
		struct
		{
			float		left;
			float		top;
			float		right;
			float 		bottom;
		};
		float			fow;
	};

	math::vector3d		up;
	math::vector3d		position;
	math::vector3d		direction;
	math::vector3d		left_direction;

	__Camera();
} Camera,*CameraPtr;

typedef struct __Light
{
	MEMORY_FUNCTIONS
	enum 	LightType
	{
		POINT,
		DIRECTIONAL,
		SPOT
	};

	LightType			type;
	float				radius;
	uint32_t			isShadowCaster;

	struct
	{
		float			constantAttentuation;
		float			linearAttentuation;
		float			quadraticAttentuation;
	};

	enum LightMapType
	{
		TEXTURE_2D,
		TEXTURE_CUBE,
		TEXTURE_3D
	};

	EString				lightMapId;
	renderer::Texture*	lightMap;

	__Light ();
	~__Light();
} Light, *LightPtr;

typedef struct __SceneNode
{
	MEMORY_FUNCTIONS

	typedef std::vector<__SceneNode*, core::memory::MemoryAllocator<__SceneNode*> > SceneNodes;
	enum SceneNodeType
	{
		DATA_NODE,
		LIGHTING_NODE,
		CAMERA_NODE
	};

	SceneNodeType		type;
	union
	{
		uint32_t			data_idx;
		LightPtr			light;
		CameraPtr			camera;
	};

	math::matrix4x4		world_matrix;

	SceneNodes				children;
	__SceneNode*			parent;
	struct
	{
		math::vector3d		min;
		math::vector3d		max;
	}	aabb;

} SceneNode,*SceneNodePtr;


typedef struct __WorldCell
{

	__WorldCell*		neighbours[8];

	WorldTile				tile;

	unsigned				nodeID;

	SceneNode::SceneNodes   nodes;


	enum NeighbourType
	{
		Top = 0,
				TopLeft,
				Left,
				BottomLeft,
				Bottom,
				BottomRight,
				Right,
				TopRight
	};

	__WorldCell();
	~__WorldCell();
	//void		deserialize(core::xml::DOMNode* root);
	MEMORY_FUNCTIONS

} WorldCell,*WorldCellPtr;

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
	EString						shaderID;
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

	__ShaderLibrary();
	~__ShaderLibrary();

	void						prepareShader(uint32_t id);
	bool						isShaderLoaded(uint32_t id);
	ShaderWrapperPtr			getShader(uint32_t id);

} ShaderLibrary,*ShaderLibraryPtr;

// Scene node structures

}

#endif /* STRUCTURES_H_ */
