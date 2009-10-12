#ifndef PLUGIN_CORE_H_
#define PLUGIN_CORE_H_

#include "core/memory/MemoryPools.h"

#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif

#include "core/EngineSubsystem.h"
#include "core/EString.h"
namespace resources
{
class ResourceManager;
}
namespace windowmanager
{
class WindowManagerFactory;
class WindowManagerDriver;
}
namespace core
{
namespace multithreading
{
class Thread;
class Mutex;
class Condition;
class ThreadID;
class Runnable;
}

namespace drivermodel
{
class DriverID;
}

namespace filesystem
{
class Filesystem;
}

namespace taskmanager
{
class TaskManager;
}
namespace memory
{
#ifndef _FREYA_SHARED_PLUGIN
void* Allocate(size_t sz,unsigned id = 0); //General in place STL allocation
#endif

#ifndef _FREYA_SHARED_PLUGIN
void  Free(void* p,unsigned id = 0);
#endif

class MemoryArena;
}

}


namespace renderer
{
class RenderingAPIFactory;
class RenderingAPIDriver;
}

namespace core
{
class EngineCore;
//!This class duplicates EngineCore functionality, but for use with plugins.
/*!
*  This class duplicates EngineCore functionality, but for use with plugins.
*  Instance of this class is created by EngineCore after startup
*/
class PluginCore : public EngineSubsystem
{
	friend class EngineCore;
protected:
	virtual	~PluginCore(){}; 	
public:
//Window manager
	//! retrieves the current Window manager created
	/*!
	* \return currently using window manager or NULL, if no created
	*/
	virtual windowmanager::WindowManagerDriver *getWindowManager() = 0;
	//! creates a window manager
	/*!
	*  create new window manager of type {type}. This method gracefully stops all WM dependent subsystems and starts
	*  the TaskManager.
	*  \param type is an id string of window manager to be created (NOTE: window manager is implemented as Freya driver)
	*/
	virtual void createWindowManager(const EString& type) = 0;



	//! retrieves the current task manager created
	/*!
	* \return currently using task manager or NULL, if no created
	*/
	virtual core::taskmanager::TaskManager *getTaskManager() = 0;
	//! retrieves the current resource manager created
	/*!
	* \return currently using resource manager or NULL, if no created
	*/
	virtual resources::ResourceManager *getResourceManager() = 0;
	//Memory management
	//! retrieve the memory arena class instance
	/*!
	* \return pointer to memory arena class
	*/
	virtual core::memory::MemoryArena*	getMemoryArena() = 0;
	//! retrieve the filesystem class instance
	/*!
	* \return pointer to a filesystem class instance
	*/
	virtual core::filesystem::Filesystem*  getFilesystem() = 0;
	//! retrieves the current rendering driver (e.g API) created
	/*!
	* \return currently using rendering driver or NULL, if no created
	*/
	virtual renderer::RenderingAPIDriver* getRenderingDriver() = 0;
	//! retrieve the LuaCore class instance
	/*!
	* \return pointer to a LuaCore class instance
	*/
	//! retrieve the XMLParser class instance
	/*!
	* \return pointer to a XMLParser class instance
	*/

	/* Settings*					getSettings()
	{
		return m_Settings;
	}*/
	//! creates a rendering driver
	/*!
	*  create new rendering driver of type {type}. The old driver used is deleted (if any)
	*  \param type is an id string of rendering driver to be created
	*/
	virtual void	createRenderingDriver(const EString& type) = 0;
	//! creates a compatible driver
	/*!
	*  create new rendering driver supporting futures needed. The old driver used is deleted (if any)
	*  \param futures is an OR'ed list of futures to be supported
	*/
	virtual void	createRenderingDriver(unsigned	futures) = 0;
	//! checks the current engine state
	/*!
	* This function should be used to implement the applications main loop.
	* \return 1 if engine is still running, 0 otherwise
	*/
	virtual unsigned isRunning() = 0;
	//! sets the engine runstate to false
	/*!
	* This function should be used to stop Freya 3D engine execution
	*/
	virtual void	shutdown() = 0;

	//!Register window manager
	/*!
	* Register a user-written window manager
	* \param driverID is an ID of user written manager
	*/
	virtual void 		registerWindowManager(core::drivermodel::DriverID* driverID) = 0;

	//!Register rendering driver
	/*!
	* Register a user-written rendering driver
	* \param driverID is an ID of user written driver
	*/
	virtual void 		registerRenderingDriver(core::drivermodel::DriverID* driverID) = 0;

	//Multithreading part
	//! Create a thread of execution
	/*!
	 * Creates and start a thread of execution
	 * \param proc is an instance of Runnable object to use as thread method
	 * \return pointer to a newly created thread object
	 */
	virtual core::multithreading::Thread*	createThread(const core::multithreading::Runnable& proc) = 0;
	//! Destroy a thread of execution
	/*!
	 * Destroys a thread of execution. If thread is running, than it is killed gracelessly
	 * \param thrd is a pointer to a thread object to destroy
	 */
	virtual void								destroyThread(core::multithreading::Thread* thrd) = 0;
	//! Create a mutex
	 core::multithreading::Mutex*		createMutex();
	//! Destroy a mutex
	virtual void								destroyMutex(core::multithreading::Mutex*  mutex) = 0;
	//! Create a condition variable
	 core::multithreading::Condition*	createCondition();
	//! Destroy a condition variable
	virtual void								destroyCondition(core::multithreading::Condition* cond) = 0;

	virtual const char*							getApplicationName() const = 0;
	virtual const char*							getApplicationCompany() const = 0;
	virtual const char*							getConfigFileName() const = 0;

};
}

#endif
