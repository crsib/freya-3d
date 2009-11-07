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

namespace framework
{
//! Abstraction of game world
class World : public virtual EngineSubsystem
{
private:
	World( WorldTreeNodePtr root );
	virtual ~World( );
public:
	static World*		loadFromXML( const EString&	path);
	static World*		getSingleton();

	WorldTreeNodePtr	    getNode( const EString&);

private:
	WorldTreeNodePtr		m_WorldRoot;
};

}

#endif /* WORLD_H_ */
