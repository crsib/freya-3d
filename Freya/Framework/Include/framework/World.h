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

namespace framework
{
class SceneNode;
//! Abstraction of game world
class EXPORT World : public virtual EngineSubsystem
{
private:
	World();
	virtual ~World( );
public:
	//static World*		loadFromXML( const EString&	path);
	static void			destroy();
	static World*		getSingleton() {return m_Instance;}

	//WorldTreeNodePtr	getNode(unsigned id);

private:
	static World* 				m_Instance;

	unsigned					m_CellWidth;
	unsigned 					m_CellHeight;

	unsigned					m_WorldWidth;
	unsigned					m_WorldHeight;

	WorldCell*					m_Cells;

	typedef std::map<uint32_t,SceneNode*,std::less<uint32_t>,core::memory::MemoryAllocator<std::pair<uint32_t,SceneNode*> > > SceneNodes;
	SceneNodes					m_SceneNodes;

	ShaderLibraryPtr			m_CurrentShaderLibrary;

	typedef	std::map<EString,ShaderLibraryPtr,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,ShaderLibraryPtr > > > ShaderLibraries;
	ShaderLibraries 			m_ShaderLibraries;

};

}

#endif /* WORLD_H_ */
