/*
 * World.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef WORLD_H_
#define WORLD_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "framework/Structures.h"

//Lua
#include "core/lua/LuaCore.h"
#include "core/lua/LuaFunction.h"
#include "core/Variable.h"

#include "internal.h"

#include <vector>
#include <map>
#include "core/memory/MemoryAllocator.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \namespace	framework
///
/// \brief	This namespace provides game engine fuctionality itself.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace framework
{
class DataNode;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	World
///
/// \brief	This class provides an interface to the in game world. It provides the way for updating the world state, loading required resources,
///  managing visibility and building batches for rendering.  
///
/// \author	Dmitry Vedenko
/// \date	12/15/2009
////////////////////////////////////////////////////////////////////////////////////////////////////

class EXPORT World : public virtual EngineSubsystem
{
private:
	World(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight);
	virtual ~World( );
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static World* create(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth,
	/// 	unsigned worldHeight)
	///
	/// \brief	Creates the World object. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	cellWidth	Width of the cell. 
	/// \param	cellHeight	Height of the cell. 
	/// \param	worldWidth	Width of the world (in "cells"). 
	/// \param	worldHeight	Height of the world(in "cells"). 
	///
	/// \return	null if it fails, else. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static World*		create(unsigned cellWidth, unsigned cellHeight, unsigned worldWidth, unsigned worldHeight);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static void destroy()
	///
	/// \brief	Destroys the World object. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void			destroy();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static World* getSingleton()
	///
	/// \brief	Gets the singleton. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	null if it fails, else the singleton. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static World*		getSingleton() {return m_Instance;}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addShaderLibrary(ShaderLibraryPtr library)
	///
	/// \brief	Adds a shader library. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	library	The library. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void				addShaderLibrary(ShaderLibraryPtr library);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void addDataNode(DataNode* node)
	///
	/// \brief	Adds a data node. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param  node	Pointer to the data node. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void				addDataNode(DataNode* node);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \enum	WORLD_STATUS
	///
	/// \brief	Values that represent the current world status. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	enum				WORLD_STATUS
	{
		//! World is ready for the next frame of rendering. 
		WORLD_STATUS_READY,
		//! World is busy loading desired resources. 
		WORLD_STATUS_LOADING,
		//! Some internal error occured. This value is actually never returned, as the exception is thrown much earlier )) 
		WORLD_STATUS_ERROR
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	WORLD_STATUS getStatus()
	///
	/// \brief	Gets the status of the world. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	The current status. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	WORLD_STATUS		getStatus();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void update(float dt)
	///
	/// \brief	Updates the world. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	dt	Time passed since the last update. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void				update(float dt);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \typedef	std::vector<GeometryBatchPtr,
	/// 			core::memory::MemoryAllocator<GeometryBatchPtr> > BatchList
	///
	/// \brief	Defines an alias representing vector of batches .
	////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef 			std::vector<GeometryBatchPtr,core::memory::MemoryAllocator<GeometryBatchPtr> > BatchList;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	BatchList& getOpaqueSceneBatches()
	///
	/// \brief	Gets the opaque scene batches. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	The opaque scene batches. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BatchList&			getOpaqueSceneBatches();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	BatchList& getTransparentBatches()
	///
	/// \brief	Gets the transparent batches. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	The transparent batches. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BatchList&			getTransparentBatches();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	unsigned visibleLightsNumber()
	///
	/// \brief	Visible lights number. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	Number of visible lights with respect to main camera. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned			visibleLightsNumber();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	BatchList& getOpaqueLightBatches(unsigned for_light)
	///
	/// \brief	Gets an opaque light batches. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	for_light	for light. 
	///
	/// \return	The opaque light batches. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BatchList&			getOpaqueLightBatches(unsigned for_light);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	BatchList& getTransparentLightBatches(unsigned for_light)
	///
	/// \brief	Gets a transparent light batches. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	for_light	for light. 
	///
	/// \return	The transparent light batches. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BatchList&			getTransparentLightBatches(unsigned for_light);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	WorldCellPtr getCell(unsigned ix, unsigned iy)
	///
	/// \brief	Gets a cell. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	ix	The x coordinate of a cell. 
	/// \param	iy	The y coordinate of a cell. 
	///
	/// \return	The cell. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	WorldCellPtr		getCell(unsigned ix, unsigned iy);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	SceneNodePtr getSceneNode(unsigned idx)
	///
	/// \brief	Gets a scene node. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \param	idx	Index of the scene node. 
	///
	/// \return	The scene node. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	SceneNodePtr		getSceneNode(unsigned idx);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	CameraPtr getMainCamera()
	///
	/// \brief	Gets the main camera. 
	///
	/// \author	Dmitry Vedenko
	/// \date	12/15/2009
	///
	/// \return	The main camera. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CameraPtr			getMainCamera();



private:
	static World* 				m_Instance;

	unsigned					m_CellWidth;
	unsigned 					m_CellHeight;

	unsigned					m_WorldWidth;
	unsigned					m_WorldHeight;

	WorldCell*					m_Cells;

	typedef std::map<uint32_t,DataNode*,std::less<uint32_t>,core::memory::MemoryAllocator<std::pair<uint32_t,DataNode*> > > DataNodes;
	DataNodes					m_DataNodes;

	ShaderLibraryPtr			m_CurrentShaderLibrary;

	typedef	std::map<EString,ShaderLibraryPtr,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,ShaderLibraryPtr > > > ShaderLibraries;
	ShaderLibraries 			m_ShaderLibraries;

	BatchList					m_OpaqueQueue;
	BatchList					m_TransparentQueue;

	typedef	std::vector<BatchList, core::memory::MemoryAllocator<BatchList> > LightBatches;

	CameraPtr					m_MainCamera;

	typedef std::map<uint32_t,SceneNodePtr,std::less<uint32_t>,core::memory::MemoryAllocator<std::pair<uint32_t,SceneNodePtr> > > SceneNodes;
	SceneNodes					m_SceneNodes;


	LightBatches				m_OpaqueLightQueue;
	LightBatches				m_TransparentLightQueue;

};

}

#endif /* WORLD_H_ */
