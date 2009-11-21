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
#include <iostream>

#include "XMLStaticStrings.h"

namespace framework
{

using namespace core::xml;

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

__WorldCell::__WorldCell()
{
	neighbours[0] = neighbours[1] = neighbours[2] = neighbours[3]
	                                                           = neighbours[4] = neighbours[5] = neighbours[6] = neighbours[7] = neighbours[8]= NULL;

	nodeID = 0;
}

__WorldCell::~__WorldCell()
{}

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

__ShaderLibrary::__ShaderLibrary(core::xml::DOMNode*	root)
{

	std::cout << "Deserializing shader library " << std::endl;
	DOMNamedNodeMap*  map = root->getAttributes();
	if(DOMNode* nd = map->getNamedItem(XMLS(shader_api)))
	{
		this->apiName = (char*)XMLStringWrap(nd->getNodeValue());
	}
	std::cout << "Library is for: " << apiName;

}

__ShaderLibrary::~__ShaderLibrary()
{

}

void				__ShaderLibrary::prepareShader(uint32_t id)
{

}

bool				__ShaderLibrary::isShaderLoader(uint32_t id)
{

}

ShaderWrapperPtr	__ShaderLibrary::getShader(uint32_t id)
{

}

void		__WorldCell::deserialize(core::xml::DOMNode* root)
{

}

}