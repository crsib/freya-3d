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
//XML parser
#include "core/xml/XMLParser.h"
//Lua
#include "core/lua/LuaCore.h"
#include "core/lua/LuaFunction.h"
#include "core/Variable.h"

#include "core/xml/XMLParser.h"

#include "internal.h"
namespace framework
{
//! Abstraction of game world
class EXPORT World : public virtual EngineSubsystem
{
private:
	World(core::xml::DOMNode* doc_root);
	virtual ~World( );
public:
	static World*		loadFromXML( const EString&	path);
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
};

}

#endif /* WORLD_H_ */
