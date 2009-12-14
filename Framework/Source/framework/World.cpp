#include "framework/World.h"

#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "resources/ResourceManager.h"

#include "resources/Resource.h"

#include <iostream>

#include <framework/SceneNode.h>

namespace framework
{

World*		World::m_Instance = NULL;


void World::destroy()
{
	delete m_Instance;
	m_Instance = 0;
}

World::World()
{

}

World::~World()
{
	delete [] m_Cells;
	for(SceneNodes::iterator it = m_SceneNodes.begin(); it != m_SceneNodes.end(); ++it)
		delete it->second;

	for(ShaderLibraries::iterator it = m_ShaderLibraries.begin(); it != m_ShaderLibraries.end(); ++it)
		delete it->second;
}

}
