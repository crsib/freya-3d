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
windowmanager::WindowManagerFactory* 	EngineCore::m_WMFactory = NULL;
renderer::RenderingAPIFactory*			 	EngineCore::m_RAPIFactory = NULL;
core::taskmanager::TaskManager*				EngineCore::m_TaskManager = NULL;
resources::ResourceManager*					EngineCore::m_ResourceManager = NULL;
unsigned									EngineCore::m_MainThreadID = 0;
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
	//start filesystem
	std::cout << "Starting filesystem subsystem" << std::endl;
	m_Filesystem  = new core::filesystem::Filesystem();


	//m_Settings  = new Settings();

	m_Running = true;
	m_Instance = this;
	m_RenderingDriver = NULL;
	m_WindowManager	  = NULL;
	std::cout << "Creating factories" << std::endl;
	m_WMFactory	=	new windowmanager::WindowManagerFactory();
	m_RAPIFactory = new renderer::RenderingAPIFactory();
}

EngineCore::~EngineCore()
{
	std::cout << "Destroying core" << std::endl;
	delete m_RenderingDriver;
	delete m_TaskManager;
	delete m_WindowManager;
	delete m_RAPIFactory;
	std::cout << "Destroying filesystem" << std::endl;
	delete m_Filesystem;
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
		m_MainThreadID = 0;
		delete m_TaskManager;
		delete m_WindowManager;
	}
	m_WindowManager = static_cast<windowmanager::WindowManagerDriver*>(m_WMFactory->createDriver(type));
	m_MainThreadID = m_WindowManager->getThreadID();
	m_TaskManager = new core::taskmanager::TaskManager;
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

unsigned		EngineCore::getCurrentThreadID()
{
	return m_WindowManager->getThreadID();
}

unsigned		EngineCore::getMainThreadID()
{
	return m_MainThreadID;
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
}