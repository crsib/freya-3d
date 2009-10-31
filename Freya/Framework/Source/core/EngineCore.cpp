/*
 * EngineCore.cpp
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#include "core/EngineCore.h"
#include <fstream>
#include <cstdlib>

#include "application-settings.h"

#include "core/PluginCore.h"

#include "core/memory/MemoryArena.h"

#include "windowmanager/WindowManagerDriver.h"
#include "core/filesystem/FilesystemInternal.h"
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

#include "core/PluginCoreInternal.h"

#include "core/PluginLoader.h"

#include "core/lua/LuaCore.h"

#include <iostream>

#include "core/freya_buf.hpp"

#include "core/xml/XMLParser.h"

#include "CEGUI.h"
#include "freya/FreyaRenderer.h"
#include "freya/FreyaResourceProvider.h"

#include "CEGUILua.h"
//#include "CEGUIImageset.h"
//#include "CEGUIFont.h"
//#include "CEGUIScheme.h"
//#include "CEGUIWindowManager.h"
#include "CEGUIXercesParser.h"
//#include "CEGUIFalWidgetLookManager.h"

using namespace renderer;


namespace core
{
	extern core::PluginCore*	CoreInstance;
	core::PluginCore*	CoreInstance;
namespace memory {
#ifdef _FREYA_DEBUG_MEMORY
	extern unsigned memory_allocated;
	extern unsigned allocation_count;
	extern unsigned deallocation_count;
	extern unsigned alloc_dealloc_dif;
	extern unsigned allocated_for_buffers;
#endif
}
core::PluginCore*							EngineCore::m_PluginCore  = NULL;
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

THREAD_IMPLEMENTATION	*					EngineCore::m_ThreadImplementation = NULL;
	
core::PluginLoader*							EngineCore::m_PluginLoader         = NULL;
	
std::stringbuf*								EngineCore::m_LogStringBuf = NULL;

core::lua::LuaCore*							EngineCore::m_LuaCore = NULL;

core::xml::XMLParser*						EngineCore::m_XMLParser = NULL;

//Memory allocation function
namespace memory
{
extern MemoryArena		ArenaInstance;
void* Allocate(size_t n,unsigned id)
{
	return ArenaInstance.allocate(n,id);
}

void Free(void* p,unsigned id)
{
	ArenaInstance.free(p,id);
}

void* Reallocate(void* p,size_t sz,unsigned id)
{
	//return EngineCore::getMemoryArena()->reallocate(p,sz);
	return NULL;
}
}
//Constructor and destructor
EngineCore::EngineCore(int argC,char** argV,const std::string& applicationName, const std::string& applicationTeam, const std::string& configName )
{
	if(m_Instance)
		throw EngineException();
	settings::application_name 		= new char[applicationName.length()+1];
	::memcpy(settings::application_name,applicationName.c_str(),applicationName.length() + 1);
	settings::application_company 	= new char[applicationTeam.length()+1];
	::memcpy(settings::application_company,applicationTeam.c_str(),applicationTeam.length() + 1);
	settings::config_file_name		= new char[configName.length()+1];
	::memcpy(settings::config_file_name,configName.c_str(),configName.length() + 1);

	std::cout << "Starting log subsystem" << std::endl;
	std::string path(argV[0]);
	size_t slash_pos = path.find_last_of("/\\" );
	if(slash_pos == std::string::npos)
		path = std::string(settings::application_name) + ".log";
	else
	{
		path.erase(slash_pos + 1);
#ifdef __APPLE__
		slash_pos = path.find_last_of("/\\" );
		slash_pos = path.find_last_of("/\\",slash_pos - 1 );
		slash_pos = path.find_last_of("/\\",slash_pos - 1 );
		slash_pos = path.find_last_of("/\\",slash_pos - 1 );
		path.erase(slash_pos + 1);
#endif
		path += std::string(settings::application_name) + ".log";
		std::cout << path << std::endl;
	}
	m_LogStream = new std::ofstream(path.c_str());
	m_LogStringBuf = new std::stringbuf;
	m_OutBuffer = new __internal::freya_buf(std::cout.rdbuf(),m_LogStream->rdbuf(),m_LogStringBuf);
	m_OldCLogStream = std::clog.rdbuf(m_OutBuffer);
	m_OldCOutStream = std::cout.rdbuf(m_OutBuffer);
	//Start memory
	std::cout << "Initializing memory subsystem" << std::endl;
	m_MemoryArena = core::memory::MemoryArena::instance();
	m_MemoryArena->addPool(4*1024*1024,4);	//STL pool 4 mb
	m_MemoryArena->addPool(4*1024*1024,4);	//Math pool 4 mb
	m_MemoryArena->addPool(64*1024*1024,4);	//Generic pool 64 mb
	m_MemoryArena->addPool(4*1024*1024,4);	//Generic class pool 4mb
	m_MemoryArena->addPool(4*1024*1024, 4); //Lua pool 4mb
	m_MemoryArena->addPool(4*1024*1024, 4); //XML pool 4mb
	m_MemoryArena->addPool(4*1024*1024, 4); //CEGUI pool 4mb
	m_ThreadImplementation = new THREAD_IMPLEMENTATION;
	//start filesystem
	std::cout << "Starting filesystem subsystem" << std::endl;
	m_Filesystem  = new core::filesystem::FilesystemInternal();

	//m_Settings  = new Settings();

	std::cout << "Starting Lua scripting engine" << std::endl;
	m_LuaCore 			= new core::lua::LuaCore;
	std::cout << "Starting Xerces-C++" << std::endl;
	m_XMLParser 		= new core::xml::XMLParser;
	m_Running 			= true;
	m_Instance 			= this;
	m_RenderingDriver 	= NULL;
	m_WindowManager	  	= NULL;
	std::cout << "Creating task manager" << std::endl;
	m_TaskManager = new core::taskmanager::TaskManager;
	std::cout << "Creating resource manager" << std::endl;
	m_ResourceManager = new resources::ResourceManager;
	std::cout << "Creating factories" << std::endl;
	m_WMFactory	=	new windowmanager::WindowManagerFactory();
	m_RAPIFactory = new renderer::RenderingAPIFactory();
	m_PluginCore  = new core::PluginCoreInternal();
	CoreInstance  = m_PluginCore;
	m_PluginLoader = new core::PluginLoader(argC,argV);
}

EngineCore::~EngineCore()
{
	std::cout << "Destroying task manager" << std::endl;
	delete m_TaskManager;
	std::cout << "Stopping CEGUI" << std::endl;
	CEGUI::System::destroy();
	std::cout << "Stopping Xerces-C++" << std::endl;
	delete m_XMLParser;
	std::cout << "Destroying Lua engine " << std::endl;
	delete m_LuaCore;
	std::cout << "Destroying resource manager" << std::endl;
	delete m_ResourceManager;
	std::cout << "Destroying rendering driver" << std::endl;
	delete m_RenderingDriver;
	std::cout << "Destroying window manager" << std::endl;
	delete m_WindowManager;
	delete m_RAPIFactory;
	std::cout << "Destroying filesystem" << std::endl;
	delete m_Filesystem;
	std::cout << "Destroying thread subsystem" << std::endl;
	delete m_ThreadImplementation;
	delete m_PluginCore;
	delete m_PluginLoader;
	//std::cout << "Switching allocation mode" << std::endl;
	//delete m_MemoryArena;
	
#ifdef _FREYA_DEBUG_MEMORY
	std::cout << "Engine memory usage at shutdown:\n"
	<< "\tLeaked in internal manager: " << memory::memory_allocated / 1024.f << " Kb\n"
	<< "\tTotal number of allocations " << memory::allocation_count << "\n"
	<< "\tTotal number of deallocations: " << memory::deallocation_count << "\n"
	<< "\tAlloc - Dealloc: " << (int) memory::alloc_dealloc_dif << "\n"
	<< "\tSystem memory allocation for internal manager: " << memory::allocated_for_buffers / 1024.f / 1024.f << " Mb" << std::endl;
	std::cout << "Engine shutdown completed" << std::endl;
#endif
	
	std::cout << "Stopping log subsystem" << std::endl;
	std::clog.flush();
	std::cout.flush();
	std::clog.rdbuf(m_OldCLogStream);
	std::cout.rdbuf(m_OldCOutStream);
	delete m_OutBuffer;
	delete m_LogStringBuf;
	m_LogStream->flush();
	m_LogStream->close();
	std::cout << "Destroying log" << std::endl;
	delete m_LogStream;

	delete [] settings::application_name;
	delete [] settings::application_company;
	delete [] settings::config_file_name;

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
	delete m_RenderingDriver;
	m_RenderingDriver = static_cast<renderer::RenderingAPIDriver*>(m_RAPIFactory->createDriver(type));
	m_ResourceManager->invalidateResources();
}

void	EngineCore::createRenderingDriver(unsigned	futures)
{
	delete m_RenderingDriver;
	bool not_ready = true;
	EStringList	lst = m_RAPIFactory->listDrivers();
	size_t id = 0,sz = lst.size();
	if(m_WindowManager == 0)
		throw renderer::DriverException("WindowManager is not started");
	while(not_ready)
	{
		bool created = false;
		try
		{
			m_WindowManager->destroyWindow();
			created = true;
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
		if(id > sz)
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
	m_ResourceManager->invalidateResources();
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

struct __internal_runnable : public EngineSubsystem
{
	__internal_runnable(const core::multithreading::Runnable* __rn) : run(const_cast<core::multithreading::Runnable*>(__rn)){}
	int operator () ()
	{
		int retval = run->operator()();
		//std::cout << "Proxy object returned " << retval << std::endl;
		return retval;
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

core::PluginCore*					EngineCore::getPluginCore()
{
	return							m_PluginCore;	
}

EString								EngineCore::getLog()
{
	return EString(m_LogStringBuf->str().c_str());
}
core::lua::LuaCore*					EngineCore::getLuaCore()
{
	return m_LuaCore;
}

core::xml::XMLParser*				EngineCore::getXMLParser()
{
	return m_XMLParser;
}

void								EngineCore::startCEGUI()
{
	//using namespace CEGUI;
	if(!m_RenderingDriver)
		throw renderer::DriverException("No RAPI started before CEGUI");
	CEGUI::freya::FreyaRenderer*			rend = new CEGUI::freya::FreyaRenderer;
	rend->setDisplaySize(CEGUI::Size(m_WindowManager->getWindowWidth(),m_WindowManager->getWindowHeight()));
	CEGUI::freya::FreyaResourceProvider*	rp	 = new CEGUI::freya::FreyaResourceProvider;

	CEGUI::LuaScriptModule*					lm	 = &CEGUI::LuaScriptModule::create(m_LuaCore->m_VirtualMachine);

	CEGUI::System::create(*rend,rp,NULL,NULL,lm);

	rp->setResourceGroupDirectory("schemes", "/GUI/schemes/");
	rp->setResourceGroupDirectory("imagesets", "/GUI/imagesets/");
	rp->setResourceGroupDirectory("fonts", "/GUI/fonts/");
	rp->setResourceGroupDirectory("layouts", "/GUI/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "/GUI/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "/scripts/");

	rp->setResourceGroupDirectory("schemas", "/GUI/xml_schemas/");

	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	CEGUI::XercesParser::setSchemaDefaultResourceGroup("schemas");
}

CEGUI::System*					EngineCore::getCEGUISystem()
{
	return CEGUI::System::getSingletonPtr();
}

}
