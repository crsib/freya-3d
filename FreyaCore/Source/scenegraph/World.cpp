#include "scenegraph/World.h"

#include <iostream>
#include <algorithm>
#include "math/math.hpp"

namespace scenegraph
{
World*			World::m_Instance = NULL;

World::WorldCell::WorldCell()
{
	neighbours[0] = neighbours[1] =
			neighbours[2] = neighbours[3] =
					neighbours[4] = neighbours[5] =
							neighbours[6] = neighbours[7]
							                           = NULL;
}

World::World(unsigned  cell_width, unsigned  cell_height, unsigned  world_width, unsigned  world_height)
{
	std::clog << "Creating a world of size: ( " << cell_width * world_width << ", " << cell_height * world_height << " )" << std::endl;

	m_Cells = new WorldCell[m_WorldWidth*m_WorldHeight];
	size_t centerX = -(m_WorldWidth *m_CellWidth) >> 1;
	size_t centerY = -(m_WorldHeight *m_CellHeight) >> 1;
	m_CenterX = centerX;
	m_CenterY = centerY;
	for(size_t i = 0; i < m_WorldWidth; i++)
	{
		for(size_t j = 0; j < m_WorldHeight; j++)
		{
			WorldCell* cell 	= m_Cells + i*m_WorldHeight + j;
			cell->tile.left 	= centerX + i*m_CellWidth;
			cell->tile.right	= centerX + (i+1)*m_CellWidth;
			cell->tile.top		= centerY + j*m_CellHeight;
			cell->tile.bottom	= centerY + (j+1)*m_CellWidth;
			if((i > 0 && i < (m_WorldWidth - 1))&& j > 0 && j < (m_WorldHeight - 1))
			{
				cell->neighbours[WorldCell::Top] = m_Cells + i*m_WorldHeight + (j - 1);
				cell->neighbours[WorldCell::TopLeft] = m_Cells + (i - 1)*m_WorldHeight + (j - 1);
				cell->neighbours[WorldCell::Left] = m_Cells + (i - 1)*m_WorldHeight + j;
				cell->neighbours[WorldCell::BottomLeft] = m_Cells + (i - 1)*m_WorldHeight + (j + 1);
				cell->neighbours[WorldCell::Bottom] = m_Cells + i*m_WorldHeight + (j + 1);
				cell->neighbours[WorldCell::BottomRight] = m_Cells + (i + 1)*m_WorldHeight + (j + 1);
				cell->neighbours[WorldCell::Right] = m_Cells + (i + 1)*m_WorldHeight + j;
				cell->neighbours[WorldCell::TopRight] = m_Cells + (i + 1)*m_WorldHeight + (j - 1);
			}
			else
			{
				if(i == 0)
				{
					if(1 == m_WorldWidth ) //m_WorldWidth == 1
					{
						if(j > 0) //connect to top
						{
							cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
						}
						if((j + 1) < m_WorldHeight) // connect bottom
						{
							cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
						}
					}
					else
					{
						cell->neighbours[WorldCell::Right] = m_Cells + (i + 1)*m_WorldHeight + j;
						if(j > 0) //connect to top
						{
							cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
							cell->neighbours[WorldCell::TopRight] = m_Cells + (i + 1)*m_WorldHeight + j - 1;
						}
						if((j + 1) < m_WorldHeight) // connect bottom
						{
							cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
							cell->neighbours[WorldCell::BottomRight] = m_Cells + (i + 1)*m_WorldHeight + j + 1;
						}
					}
				}
				else
				{
					cell->neighbours[WorldCell::Left] = m_Cells + (i - 1)*m_WorldHeight + j;
					if(j > 0) //connect to top
					{
						cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
						cell->neighbours[WorldCell::TopLeft] = m_Cells + (i - 1)*m_WorldHeight + j - 1;
					}
					if((j + 1) < m_WorldHeight) // connect bottom
					{
						cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
						cell->neighbours[WorldCell::BottomLeft] = m_Cells + (i - 1)*m_WorldHeight + j + 1;
					}
				}
			}
		}//for cycle
	}//for cycle
	m_CurrentShaderLibrary = NULL;
	m_Status = WORLD_STATUS_NOT_LOADED;
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
	for(size_t i = 0; i < m_SceneNodes.size(); i ++ )
	{
		delete m_SceneNodes[i];
	}
	for(ShaderLibraries::iterator it = m_ShaderLibraries.begin(); it != m_ShaderLibraries.end(); ++it)
		delete it->second;
}


void		World::addNode (SceneNode* node)
{
	m_SceneNodes.push_back(node);
	m_SceneNodesById[node->nodeId()] = node;
	m_SceneNodesByName[node->nodeName()] = node;
	//TODO: Connect scene node to a cell
}

void		World::destroyNode(SceneNode* node)
{
	if(node)
	{
		m_SceneNodes.erase(std::find(m_SceneNodes.begin(),m_SceneNodes.end(),node));
		m_SceneNodesById.erase(node->nodeId());
		m_SceneNodesByName.erase(node->nodeName());
		delete node;
	}
	else
	{
		std::clog << "Attempt to delete NULL node" << std::endl;
	}
}

void		World::destroyNode(unsigned   id)
{
	destroyNode(m_SceneNodesById[id]);
}

void		World::destroyNode(const EString& name)
{
	destroyNode(m_SceneNodesByName[name]);
}

SceneNode*  World::getNode(unsigned id)
{
	return m_SceneNodesById[id];
}

SceneNode*	World::getNode(const EString& name)
{
	return m_SceneNodesByName[name];
}

World::WorldCell* 	World::getCell(float x, float y)
{
	float realX = x + m_CenterX;
	float realY = y + m_CenterY;
	realX /= m_CellWidth;
	realY /= m_CellHeight;
	return m_Cells + static_cast<size_t>(math::floor(realX))*m_WorldHeight + static_cast<size_t>(math::floor(realY));
}

void		World::addShaderLibrary(ShaderLibrary*  library)
{
	m_ShaderLibraries[library->apiName()] = library;
}


//====================================Update method===========================================
void		World::update(float dt)
{

}

}
