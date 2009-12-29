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

#include <cassert>

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
		WORLD_STATUS_FRAME_READY,
		WORLD_STATUS_FRAME_PROCESSING,
		WORLD_STATUS_WAITING_FOR_RESOURCE,
		WORLD_STATUS_UPDATE_FAILED
	};

	//================ Public exception type =============================
	class Exception : public ::EngineException
	{
	public:
		virtual
		EString message() const
		{
			return "[WORLD]: Unknown exception occured";
		}

		virtual
		const char* what  	() const throw ()
		{
			return "[WORLD]: Unknown exception occured";
		}
	};

	//Public methods

	private:
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
			return "The world is not created";
		}

		virtual
		const char* what  	() const throw ()
		{
			return "The world is not created";
		}
	};
};

}

#endif /* WORLD_H_ */
