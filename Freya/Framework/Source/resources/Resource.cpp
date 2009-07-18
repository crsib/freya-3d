/*
 * Resource.cpp
 *
 *  Created on: 20.05.2009
 *      Author: vedenko
 */

#include "resources/Resource.h"

#include "core/EngineCore.h"
#include "windowmanager/WindowManagerDriver.h"
#include "core/multithreading/Mutex.h"
#include "core/multithreading/ThreadBlocks.h"

namespace resources
{

namespace __internal
{

void					destroyResource(resources::Resource* res)
{
	delete res;
}

void					finalizeResource(resources::Resource* res)
{
	res->m_Ready = true;
}

}

Resource::Resource()
{
	m_Ready = 0;
	m_Resource = NULL;
}

Resource::~Resource()
{
	m_Ready = 0;
}

bool	Resource::ready()
{
	return static_cast<bool>(m_Ready);
}

void	Resource::waitForResource()
{
	while(m_Ready == 0)
	{
		core::multithreading::yield();
	}
}

EString	Resource::id()
{
	return m_ResourceID;
}

}
