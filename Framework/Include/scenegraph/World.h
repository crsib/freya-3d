/*
 * World.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Dec 29, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef WORLD_H_
#define WORLD_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "scenegraph/Structures.h"
#include "core/EngineException.h"
#include "internal.h"
#include "scenegraph/SceneNode.h"
#include <cassert>
#include <map>
#include "core/memory/MemoryAllocator.h"

namespace scenegraph
{

class EXPORT World : public EngineSubsystem
{
private:
	static World*	m_Instance;
	World( unsigned cell_width, unsigned cell_height,
			unsigned world_width, unsigned world_height );
	virtual ~World( );
public:
	//=========== Singleton stuff =====================================
	static void
	create(unsigned cell_width, unsigned cell_height,
			unsigned world_width, unsigned world_height);

	static void 		destroy();

	static
	World*		getInstance()
	{
		if(m_Instance)
			return m_Instance;
		else
			throw WorldNotCreatedExecption();
	}
	//=============== Public enums ======================================
	enum WORLD_STATUS
	{
		WORLD_STATUS_NOT_LOADED,
		WORLD_STATUS_FRAME_READY,
		WORLD_STATUS_FRAME_PROCESSING,
		WORLD_STATUS_WAITING_FOR_RESOURCE,
		WORLD_STATUS_UPDATE_FAILED,
		WORLD_STATUS_UNKNOWN
	};

	//================ Public exception type =============================
	class Exception : public ::EngineException
	{
	public:
		virtual
		EString message() const
		{
			return "[WORLD]: Unknown exception occurred";
		}

		virtual
		const char* what  	() const throw ()
		{
			return "[WORLD]: Unknown exception occurred";
		}
	};
	//============== Public structures ===================================
	struct EXPORT WorldCell
	{

		WorldCell*		neighbours[8];

		WorldTile				tile;

		SceneNode::SceneNodeList   nodes;


		enum NeighbourType
		{
			Top = 0,
					TopLeft,
					Left,
					BottomLeft,
					Bottom,
					BottomRight,
					Right,
					TopRight
		};

		WorldCell();

		MEMORY_FUNCTIONS

	};
	//Public methods
	//Cell management
	//Cell for "real" world coords. Zero is at (centerX, centerY)
	WorldCell*						getCell(float x, float y);
	//Node management
	void							addNode (SceneNode* node);

	void							destroyNode(SceneNode* node);
	void							destroyNode(unsigned   id);
	void							destroyNode(const EString& name);

	SceneNode* 						getNode(unsigned id);
	SceneNode*						getNode(const EString& name);

	//Shader libraries
	void							addShaderLibrary(ShaderLibraryPtr library);

	//Status and updating
	WORLD_STATUS 					status() const;

	void							update(float dt);
	private:
	//================= Private typedefs ================================
	typedef std::map<unsigned,SceneNode*,std::less<unsigned>, core::memory::MemoryAllocator<std::pair<const unsigned,SceneNode*> > > NodesById;
	typedef std::map<EString,SceneNode*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,SceneNode*> > > NodesByName;
	typedef	std::map<EString,ShaderLibraryPtr,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,ShaderLibraryPtr > > > ShaderLibraries;
	//================ Private members =================================
	WORLD_STATUS 					m_Status;

	SceneNode::SceneNodeList		m_SceneNodes;
	NodesById						m_SceneNodesById;
	NodesByName						m_SceneNodesByName;

	WorldCell*						m_Cells;
	unsigned						m_CellWidth;
	unsigned 						m_CellHeight;

	unsigned						m_WorldWidth;
	unsigned						m_WorldHeight;
	unsigned 						m_CenterX;
	unsigned						m_CenterY;

	ShaderLibraryPtr				m_CurrentShaderLibrary;
	ShaderLibraries 				m_ShaderLibraries;
	//================= Exceptions =======================================
	class WorldAlreadyCreatedExecption : public World::Exception
	{
	public:
		virtual
		EString message() const
		{
			return "[WORLD]: The world is already created";
		}

		virtual
		const char* what  	() const throw ()
		{
			return "[WORLD]: The world is already created";
		}
	};

	class WorldNotCreatedExecption : public World::Exception
	{
	public:
		virtual
		EString message() const
		{
			return "[WORLD]: The world is not created";
		}

		virtual
		const char* what  	() const throw ()
		{
			return "[WORLD]: The world is not created";
		}
	};
};

//================== Implementation ===========================================================
inline
World::WORLD_STATUS
World::status() const
{
	return m_Status;
}

}

#endif /* WORLD_H_ */
