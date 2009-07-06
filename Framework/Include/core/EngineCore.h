/*
 * EngineCore.h
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#ifndef ENGINECORE_H_
#define ENGINECORE_H_
#include <iostream>
#include "core/EString.h"
#include "internal.h"
#include "config.h"
#include "core/multithreading/ImplementationFactory.h"

namespace resources
{
class ResourceManager;
}
namespace windowmanager
{
class WindowManagerFactory;
class WindowManagerDriver;
}
//! This namespace contains all classes related to engine core futures
namespace core
{

namespace multithreading
{
class Thread;
class Mutex;
class Condition;
class ThreadID;
class Runnable;
THREAD_IMPLEMENTATION_PREDEF;
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
//!uses memory arena to allocate a memory block
/*!
* This function allocates a memory block inside the memory arena.
* All engine allocations should happen inside memory arena using either this function, either memory arena methods
* \param sz is a size of newly created block
* \return pointer to a newly created block
*/
EXPORT void* Allocate(size_t sz,unsigned id = 0); //General in place STL allocation
//!Uses memory arena to reallocate a memory block
/*!
* This function reallocates a memory block inside the memory arena.
* All engine reallocations should happen inside memory arena using either this function, either memory arena methods
* The function can be used on, and only on memory blocks allocated inside memory arena
* \param p  is a pointer to memory block inside memory arena
* \param sz is a size of newly created block
* \return pointer to reallocated block of memory (as it possipbly could move)
*/
EXPORT void* Reallocate(void* p,size_t sz,unsigned id = 0);
//!uses memory arena to free a memory block
/*!
* This function frees a memory block inside the memory arena.
* All engine deallocations should happen inside memory arena using either this function, either memory arena methods
* The function can be used on, and only on memory blocks allocated inside memory arena
* \param p  is a pointer to memory block inside memory arena
*/
EXPORT void  Free(void* p,unsigned id = 0);

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
//! Main class of Freya 3D engine
/*!
* This class is used to create all engine subsystems
* this class is implemented as singleton. Attemt to create a second copy of this class will lead to exception
* of type EngineException to be raised. For this time the excepion message will be "Engine exception occured
*/

class EXPORT EngineCore {
public:
	EngineCore();
	virtual ~EngineCore();
	//Window manager
	//! retrieves the current Window manager created
	/*!
	* \return currently using window manager or NULL, if no created
	*/
	static windowmanager::WindowManagerDriver *getWindowManager();
	//! creates a window manager
	/*!
	*  create new window manager of type {type}. This method gracefully stops all WM dependent subsystems and starts
	*  the TaskManager.
	*  \param type is an id string of window manager to be created (NOTE: window manager is implemented as Freya driver)
	*/
	static void createWindowManager(const EString& type);



	//! retrieves the current task manager created
	/*!
	* \return currently using task manager or NULL, if no created
	*/
	static core::taskmanager::TaskManager *getTaskManager();
	//! retrieves the current resource manager created
	/*!
	* \return currently using resource manager or NULL, if no created
	*/
	static resources::ResourceManager *getResourceManager();
	//Memory management
	//! retrieve the memory arena class instance
	/*!
	* \return pointer to memory arena class
	*/
	static core::memory::MemoryArena*	getMemoryArena();
	//! retrieve the filesystem class instance
	/*!
	* \return pointer to a filesystem class instance
	*/
	static core::filesystem::Filesystem*  getFilesystem();
	//! retrieves the current rendering driver (e.g API) created
	/*!
	* \return currently using rendering driver or NULL, if no created
	*/
	static renderer::RenderingAPIDriver* getRenderingDriver();
	//! retrieve the LuaCore class instance
	/*!
	* \return pointer to a LuaCore class instance
	*/
	//! retrieve the XMLParser class instance
	/*!
	* \return pointer to a XMLParser class instance
	*/

	/*static Settings*					getSettings()
	{
		return m_Settings;
	}*/
	//! creates a rendering driver
	/*!
	*  create new rendering driver of type {type}. The old driver used is deleted (if any)
	*  \param type is an id string of rendering driver to be created
	*/
	static void	createRenderingDriver(const EString& type);
	//! creates a compatible driver
	/*!
	*  create new rendering driver supporting futures needed. The old driver used is deleted (if any)
	*  \param futures is an OR'ed list of futures to be supported
	*/
	static void	createRenderingDriver(unsigned	futures);
	//! checks the current engine state
	/*!
	* This function should be used to implement the applications main loop.
	* \return 1 if engine is still running, 0 otherwise
	*/
	static unsigned isRunning();
	//! sets the engine runstate to false
	/*!
	* This function should be used to stop Freya 3D engine execution
	*/
	static void	shutdown();
	//! retrieves the instance of EngineCore class
	/*!
	* \return pointer to instance of EngineCore class
	*/
	static EngineCore*		getInstance();
	//!Register window manager
	/*!
	* Register a user-written window manager
	* \param driverID is an ID of user written manager
	*/
	static void 		registerWindowManager(core::drivermodel::DriverID* driverID);

	//!Register rendering driver
	/*!
	* Register a user-written rendering driver
	* \param driverID is an ID of user written driver
	*/
	static void 		registerRenderingDriver(core::drivermodel::DriverID* driverID);

	//Multithreading part
	//! Create a thread of execution
	/*!
	 * Creates and start a thread of execution
	 * \param proc is an instance of Runnable object to use as thread method
	 * \return pointer to a newly created thread object
	 */
	static core::multithreading::Thread*	createThread(const core::multithreading::Runnable& proc);
	//! Destroy a thread of execution
	/*!
	 * Destroys a thread of execution. If thread is running, than it is killed gracelessly
	 * \param thrd is a pointer to a thread object to destroy
	 */
	static void								destroyThread(core::multithreading::Thread* thrd);
	//! Create a mutex
	static core::multithreading::Mutex*		createMutex();
	//! Destroy a mutex
	static void								destroyMutex(core::multithreading::Mutex*  mutex);
	//! Create a condition variable
	static core::multithreading::Condition*	createCondition();
	//! Destroy a condition variable
	static void								destroyCondition(core::multithreading::Condition* cond);
private:
	//Memory subsystem
	static core::memory::MemoryArena*					m_MemoryArena;
	//Logging subsystem
	std::ofstream*										m_LogStream;
	std::streambuf*  									m_OldLogStream;
	//Filesystem subsystem :)
	static core::filesystem::Filesystem*				m_Filesystem;
	//Window management
	static windowmanager::WindowManagerDriver*			m_WindowManager;
	//Rendering driver
	static renderer::RenderingAPIDriver*				m_RenderingDriver;
	//Lua
	//static Settings*						m_Settings;

	//Loop and app control
	static unsigned										m_Running;
	static EngineCore*									m_Instance;
	static windowmanager::WindowManagerFactory* 		m_WMFactory;
	static renderer::RenderingAPIFactory*				m_RAPIFactory;
	static core::taskmanager::TaskManager*				m_TaskManager;
	static resources::ResourceManager*					m_ResourceManager;
	static THREAD_IMPLEMENTATION			*			m_ThreadImplementation;
};

}

#endif /* ENGINECORE_H_ */
