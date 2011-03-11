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

namespace scenegraph
{


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

typedef struct __File : public ::EngineSubsystem
{
	void*		data;
	size_t		size;

	void free();

	__File() : data (NULL), size(0){}
	virtual ~__File();
} File,*FilePtr;

typedef
struct 	__TextureWrapper
{
	MEMORY_FUNCTIONS
	EString								texture_resource;
	renderer::Texture*					texture;
	renderer::TextureFiltering::type	min_filter;
	renderer::TextureFiltering::type	mag_filter;
	renderer::TextureUnit::type			texture_unit;
} TextureWrapper,*TextureWrapperPtr;

typedef
struct	__GeometryBatch
{
/*	MEMORY_FUNCTIONS
	ShaderWrapperPtr*				shader; //Shader id in shader library
	uint32_t						number_of_textures;
	TextureWrapperPtr*				textures;
	uint32_t						batch_id;
	VBODataPtr						vbo;
	uint32_t						r2vb;//Pass is r2vb
	renderer::VertexBufferObject*	r2vbTarget;*/
} GeometryBatch,*GeometryBatchPtr; //This is a geometry batch

typedef std::vector<GeometryBatchPtr, core::memory::MemoryAllocator<GeometryBatchPtr> > BatchList;
}



#endif /* STRUCTURES_H_ */
