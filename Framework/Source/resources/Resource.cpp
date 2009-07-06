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

namespace resources
{

Resource::Resource()
{
	m_Mutex = core::EngineCore::createMutex();
	m_Ready = 0;
	m_Resource = NULL;
}

Resource::~Resource()
{
	m_Mutex->unlock();
	core::EngineCore::destroyMutex(m_Mutex);
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
		m_Mutex->lock();
		m_Mutex->unlock();
	}
}

EString	Resource::id()
{
	return m_ResourceID;
}

}
