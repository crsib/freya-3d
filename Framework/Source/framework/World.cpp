#include "framework/World.h"

#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "resources/ResourceManager.h"

#include "resources/Resource.h"

#include <iostream>

#include <framework/DataNode.h>

namespace framework
{

World*		World::m_Instance = NULL;


void World::destroy()
{
	delete m_Instance;
	m_Instance = 0;
}

World::World(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight)
{
	std::clog << "Creating world of ( " << m_CellWidth << "x" << m_CellHeight << " ) cells. "
			"Real size is: ( " << m_WorldWidth *m_CellWidth << "x" << m_WorldHeight *m_CellHeight << " ) px."<< std::endl;
	m_CellWidth = cellWidth;
	m_CellHeight = cellHeight;
	m_WorldWidth = worldWidth;
	m_WorldHeight = worldHeight;
	m_Cells = new WorldCell[m_WorldWidth*m_WorldHeight];
	size_t centerX = -(m_WorldWidth *m_CellWidth) >> 1;
	size_t centerY = -(m_WorldHeight *m_CellHeight) >> 1;
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

	//========== Initialization =========================================================================
	m_CurrentShaderLibrary = NULL;
}

World::~World()
{
	delete [] m_Cells;
	for(SceneNodes::iterator it = m_SceneNodes.begin(); it != m_SceneNodes.end(); ++it)
		delete it->second;

	for(ShaderLibraries::iterator it = m_ShaderLibraries.begin(); it != m_ShaderLibraries.end(); ++it)
		delete it->second;
}

World*	World::create(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight)
{
	try
	{
		m_Instance = new World(cellWidth, cellHeight, worldWidth,  worldHeight);
	}
	catch(...)
	{
		throw;
	}
	return m_Instance;
}

}
