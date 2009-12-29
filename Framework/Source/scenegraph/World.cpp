#include "scenegraph/World.h"

#include <iostream>

namespace scenegraph
{
World*			World::m_Instance = NULL;

World::World(unsigned  cell_width, unsigned  cell_height, unsigned  world_width, unsigned  world_height)
{
	std::clog << "Creating a world of size: ( " << cell_width * world_width << ", " << cell_height * world_height << " )" << std::endl;
}

void World::destroy()
{
	delete m_Instance;
	m_Instance = NULL;
}

void World::create(unsigned  cell_width, unsigned  cell_height, unsigned  world_width, unsigned  world_height)
{
	if(m_Instance == NULL)
		m_Instance = new World(cell_width,cell_height,world_width, world_height);
	else
		throw World::WorldAlreadyCreatedExecption();
}

World::~World()
{
	std::clog << "Destroying world" << std::endl;

}

}
