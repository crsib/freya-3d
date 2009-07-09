/*
 * EngineCore.cpp
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#include "core/EngineCore.h"
#include <fstream>
#include <cstdlib>

#include "core/memory/MemoryArena.h"

#include "windowmanager/WindowManagerDriver.h"
#include "core/filesystem/Filesystem.h"
#include "renderer/RenderingAPIDriver.h"
#include "core/drivermodel/DriverID.h"
#include "core/taskmanager/TaskManager.h"

#include "windowmanager/WindowManagerFactory.h"
#include "renderer/RenderingAPIFactory.h"
#include "core/EngineException.h"

#include "core/taskmanager/Task.h"
#include "renderer/DriverException.h"

#include "core/multithreading/ImplementationFactory.h"
#include "core/multithreading/ThreadID.h"
#include "core/multithreading/Thread.h"
#include "core/multithreading/Condition.h"
#include "core/multithreading/Mutex.h"
#include THREAD_IMPLEMENTATION_INCLUDE

#include "resources/ResourceManager.h"

#include <iostream>

using namespace renderer;


namespace core
{


core::memory::MemoryArena*    				EngineCore::m_MemoryArena = NULL;
core::filesystem::Filesystem*				EngineCore::m_Filesystem  = NULL;
windowmanager::WindowManagerDriver*			EngineCore::m_WindowManager = NULL;
renderer::RenderingAPIDriver*				EngineCore::m_RenderingDriver = NULL;
//Settings*									EngineCore::m_Settings = NULL;

unsigned									EngineCore::m_Running = false;
EngineCore*									EngineCore::m_Instance = NULL;
windowmanager::WindowManagerFactory* 		EngineCore::m_WMFactory = NULL;
renderer::RenderingAPIFactory*			 	EngineCore::m_RAPIFactory = NULL;
core::taskmanager::TaskManager*				EngineCore::m_TaskManager = NULL;
resources::ResourceManager*					EngineCore::m_ResourceManager = NULL;

THREAD_IMPLEMENTATION	*					EngineCore::m_ThreadImplementation = 0;
//Memory allocation function
namespace memory
{
void* Allocate(size_t n,unsigned id)
{
	return EngineCore::getMemoryArena()->allocate(n,id);
}

void Free(void* p,unsigned id)
{
	EngineCore::getMemoryArena()->free(p,id);
}

void* Reallocate(void* p,size_t sz,unsigned id)
{
	//return EngineCore::getMemoryArena()->reallocate(p,sz);
	return NULL;
}
}
//Constructor and destructor
EngineCore::EngineCore()
{
	if(m_Instance)
		throw EngineException();
	if(m_MemoryArena)
		return;
	std::cout << "Starting log subsystem" << std::endl;
	//m_LogStream = new std::ofstream((char*)"freya.log");
	//m_OldLogStream = std::clog.rdbuf(m_LogStream->rdbuf());
	//Start memory
	std::cout << "Starting memory subsystem" << std::endl;
	m_MemoryArena = new core::memory::MemoryArena();
	m_MemoryArena->addPool(10*1024*1024,4);//STL pool
	m_MemoryArena->addPool(10*1024*1024,4);//Math pool
	m_MemoryArena->addPool(30*1024*1024,4);//Generic pool
	m_MemoryArena->addPool(1024*1024,4);//Generic class pool
	m_ThreadImplementation = new THREAD_IMPLEMENTATION;
	//start filesystem
	std::cout << "Starting filesystem subsystem" << std::endl;
	m_Filesystem  = new core::filesystem::Filesystem();

	//m_Settings  = new Settings();

	m_Running = true;
	m_Instance = this;
	m_RenderingDriver = NULL;
	m_WindowManager	  = NULL;
	m_TaskManager = new core::taskmanager::TaskManager;
	m_ResourceManager = new resources::ResourceManager;
	std::cout << "Creating factories" << std::endl;
	m_WMFactory	=	new windowmanager::WindowManagerFactory();
	m_RAPIFactory = new renderer::RenderingAPIFactory();
}

EngineCore::~EngineCore()
{
	std::cout << "Destroying resource manager" << std::endl;
	delete m_ResourceManager;
	std::cout << "Destroying task manager" << std::endl;
	delete m_TaskManager;
	std::cout << "Destroying rendering driver" << std::endl;
	delete m_RenderingDriver;
	std::cout << "Destroying window manager" << std::endl;
	delete m_WindowManager;
	delete m_RAPIFactory;
	std::cout << "Destroying filesystem" << std::endl;
	delete m_Filesystem;
	std::cout << "Destroying thread subsystem" << std::endl;
	delete m_ThreadImplementation;
	std::cout << "Switching allocation mode" << std::endl;
	delete m_MemoryArena;
	std::cout << "Stopping log subsystem" << std::endl;
	std::clog.flush();
	//std::clog.rdbuf(m_OldLogStream);
	//m_LogStream->flush();
	//m_LogStream->close();
	std::cout << "Destroying log" << std::endl;
	//delete m_LogStream;
	std::cout << "Engine shutdown completed" << std::endl;
}

void EngineCore::createWindowManager(const EString& type)
{
	if(m_WindowManager)
	{
		delete m_RenderingDriver;
		m_RenderingDriver = NULL;
		delete m_WindowManager;
	}
	m_WindowManager = static_cast<windowmanager::WindowManagerDriver*>(m_WMFactory->createDriver(type));
}

void EngineCore::createRenderingDriver(const EString& type)
{
	if(m_RenderingDriver)
	{
		delete m_RenderingDriver;
	}
	m_RenderingDriver = static_cast<renderer::RenderingAPIDriver*>(m_RAPIFactory->createDriver(type));
}

void	EngineCore::createRenderingDriver(unsigned	futures)
{
	if(m_RenderingDriver)
	{
		delete m_RenderingDriver;
	}
	bool not_ready = true;
	EStringList	lst = m_RAPIFactory->listDrivers();
	size_t id = 0,sz = lst.size();
	while(not_ready)
	{
		bool created = false;
		try
		{
			created = true;
			//Todo: redirect to log
			std::cout << "Trying to start " << lst[id] << " renderer " << std::endl;
			m_RenderingDriver = static_cast<renderer::RenderingAPIDriver*>(m_RAPIFactory->createDriver(lst[id]));
		}
		catch(EngineException& ex)
		{
			std::cout << ex.message() << std::endl;
			m_RenderingDriver = NULL;
			created = false;
		}
		catch(...)
		{
			std::cout << "Unknown exception" << std::endl;
			m_RenderingDriver = NULL;
			created = false;
		}
		++id;
		if(id == sz)
			throw renderer::DriverException("Failed to create renderer with requested capabilities.");
		if(!created)
			continue;
		if((m_RenderingDriver->futures() & futures) == futures)
			not_ready = false;
		else
		{
			std::cout << "Some futures requested are unsupported" << std::endl;
			delete m_RenderingDriver;
		}
	}
	std::cout << "Rendering driver started successfully" << std::endl;
}

void 		EngineCore::registerWindowManager(core::drivermodel::DriverID* driverID)
{
	m_WMFactory->registerDriver(driverID);
}

void 		EngineCore::registerRenderingDriver(core::drivermodel::DriverID* driverID)
{
	m_RAPIFactory->registerDriver(driverID);
}


windowmanager::WindowManagerDriver *EngineCore::getWindowManager()
{
	return m_WindowManager;
}

core::taskmanager::TaskManager *EngineCore::getTaskManager()
{
	return m_TaskManager;
}

resources::ResourceManager *EngineCore::getResourceManager()
{
	return m_ResourceManager;
}

core::memory::MemoryArena*	EngineCore::getMemoryArena()
{
	return m_MemoryArena;
}

core::filesystem::Filesystem*  EngineCore::getFilesystem()
{
	return m_Filesystem;
}

renderer::RenderingAPIDriver* EngineCore::getRenderingDriver()
{
	return m_RenderingDriver;
}

unsigned EngineCore::isRunning()
{
	return m_Running;
}

void	EngineCore::shutdown()
{
	m_Running = false;
}

EngineCore*		EngineCore::getInstance()
{
	return m_Instance;
}

struct __internal_runnable
{
	__internal_runnable(const core::multithreading::Runnable* __rn) : run(const_cast<core::multithreading::Runnable*>(__rn)){}
	int operator () ()
	{
		return run->operator()();
	}

	core::multithreading::Runnable* run;
};

core::multithreading::Thread*		EngineCore::createThread(const core::multithreading::Runnable& proc)
{

	return m_ThreadImplementation->createThread(__internal_runnable(&proc));
}

void								EngineCore::destroyThread(core::multithreading::Thread* thrd)
{
	m_ThreadImplementation->destroyThread(thrd);
}

core::multithreading::Mutex*		EngineCore::createMutex()
{
	return m_ThreadImplementation->createMutex();
}

void								EngineCore::destroyMutex(core::multithreading::Mutex*  mutex)
{
	m_ThreadImplementation->destroyMutex(mutex);
}

core::multithreading::Condition*	EngineCore::createCondition()
{
	return m_ThreadImplementation->createCondition();
}

void								EngineCore::destroyCondition(core::multithreading::Condition* cond)
{
	m_ThreadImplementation->destroyCondition(cond);
}

}
