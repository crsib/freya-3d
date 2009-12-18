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
	m_CellWidth = cellWidth;
	m_CellHeight = cellHeight;
	m_WorldWidth = worldWidth;
	m_WorldHeight = worldHeight;
	std::clog << "Creating world of ( " << m_WorldWidth << "x" << m_WorldHeight << " ) cells. "
				"Real size is: ( " << m_WorldWidth *m_CellWidth << "x" << m_WorldHeight *m_CellHeight << " ) px."<< std::endl;

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
	m_MainCamera = NULL;
}

World::~World()
{
	delete [] m_Cells;
	for(DataNodes::iterator it = m_DataNodes.begin(); it != m_DataNodes.end(); ++it)
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

using namespace framework;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void framework::World::addShaderLibrary(ShaderLibraryPtr library)
///
/// \brief	Adds a shader library. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	library	The library. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void framework::World::addShaderLibrary(ShaderLibraryPtr library)
{
	m_ShaderLibraries[library->apiName] = library;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void framework::World::addDataNode(DataNode*node)
///
/// \brief	Adds a data node. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param [in,out]	node	If non-null, the node. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void framework::World::addDataNode(DataNode*node)
{
	m_DataNodes[node->getIdx()] = node;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	WORLD_STATUS framework::World::getStatus(void)
///
/// \brief	Gets the status. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \return	The status. 
////////////////////////////////////////////////////////////////////////////////////////////////////

World::WORLD_STATUS framework::World::getStatus(void)
{
	return World::WORLD_STATUS_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void framework::World::update(float dt)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn void update(float dt) /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	dt	The dt. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void framework::World::update(float dt)
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	BatchList& framework::World::getOpaqueSceneBatches(void)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn BatchList& getOpaqueSceneBatches() /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \return	The opaque scene batches. 
////////////////////////////////////////////////////////////////////////////////////////////////////

World::BatchList& framework::World::getOpaqueSceneBatches(void)
{
	return m_OpaqueQueue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	BatchList& framework::World::getTransparentBatches(void)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn BatchList& getTransparentBatches() /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \return	The transparent batches. 
////////////////////////////////////////////////////////////////////////////////////////////////////

World::BatchList& framework::World::getTransparentBatches(void)
{
	return m_TransparentQueue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	unsigned framework::World::visibleLightsNumber(void)
///
/// \brief	Visible lights number. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \return	. 
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned framework::World::visibleLightsNumber(void)
{
	return m_OpaqueLightQueue.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	BatchList& framework::World::getOpaqueLightBatches(unsigned for_light)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn BatchList& getOpaqueLightBatches(unsigned for_light) /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	for_light	for light. 
///
/// \return	The opaque light batches. 
////////////////////////////////////////////////////////////////////////////////////////////////////

World::BatchList& framework::World::getOpaqueLightBatches(unsigned for_light)
{
	return m_OpaqueLightQueue[for_light];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	BatchList& framework::World::getTransparentLightBatches(unsigned for_light)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn BatchList& getTransparentLightBatches(unsigned for_light) /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	for_light	for light. 
///
/// \return	The transparent light batches. 
////////////////////////////////////////////////////////////////////////////////////////////////////

World::BatchList& framework::World::getTransparentLightBatches(unsigned for_light)
{
	return m_TransparentLightQueue[for_light];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	WorldCellPtr framework::World::getCell(unsigned ix, unsigned iy)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn WorldCellPtr getCell(unsigned ix, unsigned iy) /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	ix	The ix. 
/// \param	iy	The iy. 
///
/// \return	The cell. 
////////////////////////////////////////////////////////////////////////////////////////////////////

WorldCellPtr framework::World::getCell(unsigned ix, unsigned iy)
{
	return m_Cells + ix*m_WorldHeight + iy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SceneNodePtr framework::World::getSceneNode(unsigned idx)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn SceneNodePtr getSceneNode(unsigned idx) /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \param	idx	Zero-based index of the. 
///
/// \return	The scene node. 
////////////////////////////////////////////////////////////////////////////////////////////////////

SceneNodePtr framework::World::getSceneNode(unsigned idx)
{
	return m_SceneNodes[idx];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	CameraPtr framework::World::getMainCamera(void)
///
/// \brief	///////////////////////////////////////////////////////////////////////////////////////
/// 		/////////// / \fn CameraPtr getMainCamera() /. 
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
///
/// \return	The main camera. 
////////////////////////////////////////////////////////////////////////////////////////////////////

CameraPtr framework::World::getMainCamera(void)
{
	
	return m_MainCamera;
}

