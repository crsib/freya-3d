/*
 * World.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file
 *  Created on: Dec 29, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef AABB_H_
#define AABB_H_

#include "core/EngineCore.h"
#include <BulletCollision/BroadphaseCollision/btDbvt.h>

namespace scenegraph
{
class AABB : public btDbvtAabbMm
{
public:
	static void* operator new(size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CLASS_POOL);
	}
	//!Overloaded delete operator
	static void  operator delete(void* p)
	{
		core::memory::Free(p,core::memory::CLASS_POOL);
	}
	//!Overloaded new[] operator
	static
	void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::CLASS_POOL);
	}
	//!Overloaded delete[] operator
	static
	void  operator delete[](void* p)
	{
		core::memory::Free(p,core::memory::CLASS_POOL);
	}

};
}


#endif
