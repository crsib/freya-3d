#include "core/PluginCoreInternal.h"
#include "core/EngineCore.h"
namespace core
{
PluginCoreInternal::PluginCoreInternal()
{
}

PluginCoreInternal::~PluginCoreInternal()
{
}
	
void PluginCoreInternal::createWindowManager(const EString& type)
{
	core::EngineCore::createWindowManager(type);
}

void PluginCoreInternal::createRenderingDriver(const EString& type)
{
	core::EngineCore::createRenderingDriver(type);
}

void	PluginCoreInternal::createRenderingDriver(unsigned	futures)
{
	core::EngineCore::createRenderingDriver(futures);	
}

void 		PluginCoreInternal::registerWindowManager(core::drivermodel::DriverID* driverID)
{
	core::EngineCore::registerWindowManager(driverID);
}

void 		PluginCoreInternal::registerRenderingDriver(core::drivermodel::DriverID* driverID)
{
	core::EngineCore::registerRenderingDriver(driverID);
}


windowmanager::WindowManagerDriver *PluginCoreInternal::getWindowManager()
{
	return core::EngineCore::getWindowManager();
}

core::taskmanager::TaskManager *PluginCoreInternal::getTaskManager()
{
	return core::EngineCore::getTaskManager();
}

resources::ResourceManager *PluginCoreInternal::getResourceManager()
{
	return core::EngineCore::getResourceManager();
}

core::memory::MemoryArena*	PluginCoreInternal::getMemoryArena()
{
	return core::EngineCore::getMemoryArena();
}

core::filesystem::Filesystem*  PluginCoreInternal::getFilesystem()
{
	return core::EngineCore::getFilesystem();
}

renderer::RenderingAPIDriver* PluginCoreInternal::getRenderingDriver()
{
	return core::EngineCore::getRenderingDriver();
}

unsigned PluginCoreInternal::isRunning()
{
	return core::EngineCore::isRunning();
}

void	PluginCoreInternal::shutdown()
{
	core::EngineCore::shutdown();
}

core::multithreading::Thread*		PluginCoreInternal::createThread(const core::multithreading::Runnable& proc)
{

	return core::EngineCore::createThread(proc);
}

void								PluginCoreInternal::destroyThread(core::multithreading::Thread* thrd)
{
	core::EngineCore::destroyThread(thrd);
}

core::multithreading::Mutex*		PluginCoreInternal::createMutex()
{
	return core::EngineCore::createMutex();
}

void								PluginCoreInternal::destroyMutex(core::multithreading::Mutex*  mutex)
{
	core::EngineCore::destroyMutex(mutex);
}

core::multithreading::Condition*	PluginCoreInternal::createCondition()
{
	return core::EngineCore::createCondition();
}

void								PluginCoreInternal::destroyCondition(core::multithreading::Condition* cond)
{
	core::EngineCore::destroyCondition(cond);
}
}
