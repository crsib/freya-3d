/*
 * Resource.cpp
 *
 *  Created on: 20.05.2009
 *      Author: vedenko
 */

#include "resources/Resource.h"

#include "windowmanager/WindowManagerDriver.h"
#include "core/multithreading/Mutex.h"
#include "core/multithreading/ThreadBlocks.h"

#ifndef _WIN32
#include <sched.h>
#else
#include <Windows.h>
#endif

namespace resources
{
Resource::Resource()
{
	m_Ready = 0;
	m_Resource = NULL;	
}

Resource::~Resource()
{
	
}

bool	Resource::ready()
{
	return static_cast<bool>(m_Ready);
}

void	Resource::waitForResource()
{
	while(m_Ready == 0)
	{
		//core::multithreading::yield();
#ifndef _WIN32
	sched_yield();
#else
	Sleep(0);
#endif
	}
}

EString	Resource::id()
{
	return m_ResourceID;
}

}
