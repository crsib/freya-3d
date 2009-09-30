/*
 * Task.cpp
 *
 *  Created on: Sep 18, 2009
 *      Author: crsib
 */
#include "core/taskmanager/Task.h"

#include <iostream>

namespace core
{
namespace taskmanager
{

Task::~Task()
{
	std::cout << "Destroying task: " << reinterpret_cast<void*>(this) << std::endl;
}

Task*	Task::retain()
{
	++m_TaskCounter;
	return this;
}

void	Task::release()
{
	if(this)
	{
		if(m_TaskCounter)
			if(0 == --m_TaskCounter)
				delete this;
	}
}
	
unsigned Task::retainCount()
{
	return m_TaskCounter;
}
}
}
