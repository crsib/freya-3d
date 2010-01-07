/*
 * FrameworkImpl.cpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#include "scenegraph/Structures.h"
#include "resources/ResourceManager.h"
#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
//#include "scenegraph/DataNode.h"
#include <iostream>

namespace scenegraph
{

__Resource::~__Resource()
{
	core::EngineCore::getResourceManager()->free(resource);
	resource = NULL;
	isLoaded = false;
}

__Data::~__Data()
{
	for(size_t i = 0; i < nodes.size(); i++ )
	{
		//delete nodes[i];
	}
	nodes.clear();
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
