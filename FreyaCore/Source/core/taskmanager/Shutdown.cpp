/*
 * Shutdown.cpp
 *
 *  Created on: 26.05.2009
 *      Author: vedenko
 */

#include "core/taskmanager/Shutdown.h"
#include "core/EngineCore.h"

namespace core
{

namespace taskmanager
{

Shutdown::Shutdown()
{
	// TODO Auto-generated constructor stub

}

Shutdown::~Shutdown()
{
	// TODO Auto-generated destructor stub
}

int Shutdown::operator ()()
{
	core::EngineCore::shutdown();
	return Task::DONE;
}

}

}
