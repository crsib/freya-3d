#ifndef PLUGIN_CORE_INTERNAL_H_
#define PLUGIN_CORE_INTERNAL_H_
#include "core/PluginCore.h"
namespace core
{
	class EngineCore;
class PluginCoreInternal : public PluginCore
{
	friend class core::EngineCore;
private:
	PluginCoreInternal();
	virtual	~PluginCoreInternal();	
public:
//Window manager
	//! retrieves the current Window manager created
	/*!
	* \return currently using window manager or NULL, if no created
	*/
	virtual windowmanager::WindowManagerDriver *getWindowManager();
	//! creates a window manager
	/*!
	*  create new window manager of type {type}. This method gracefully stops all WM dependent subsystems and starts
	*  the TaskManager.
	*  \param type is an id string of window manager to be created (NOTE: window manager is implemented as Freya driver)
	*/
	virtual void createWindowManager(const EString& type);



	//! retrieves the current task manager created
	/*!
	* \return currently using task manager or NULL, if no created
	*/
	virtual core::taskmanager::TaskManager *getTaskManager();
	//! retrieves the current resource manager created
	/*!
	* \return currently using resource manager or NULL, if no created
	*/
	virtual resources::ResourceManager *getResourceManager();
	//Memory management
	//! retrieve the memory arena class instance
	/*!
	* \return pointer to memory arena class
	*/
	virtual core::memory::MemoryArena*	getMemoryArena();
	//! retrieve the filesystem class instance
	/*!
	* \return pointer to a filesystem class instance
	*/
	virtual core::filesystem::Filesystem*  getFilesystem();
	//! retrieves the current rendering driver (e.g API) created
	/*!
	* \return currently using rendering driver or NULL, if no created
	*/
	virtual renderer::RenderingAPIDriver* getRenderingDriver();
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
	virtual void	createRenderingDriver(const EString& type);
	//! creates a compatible driver
	/*!
	*  create new rendering driver supporting futures needed. The old driver used is deleted (if any)
	*  \param futures is an OR'ed list of futures to be supported
	*/
	virtual void	createRenderingDriver(unsigned	futures);
	//! checks the current engine state
	/*!
	* This function should be used to implement the applications main loop.
	* \return 1 if engine is still running, 0 otherwise
	*/
	virtual unsigned isRunning();
	//! sets the engine runstate to false
	/*!
	* This function should be used to stop Freya 3D engine execution
	*/
	virtual void	shutdown();

	//!Register window manager
	/*!
	* Register a user-written window manager
	* \param driverID is an ID of user written manager
	*/
	virtual void 		registerWindowManager(core::drivermodel::DriverID* driverID);

	//!Register rendering driver
	/*!
	* Register a user-written rendering driver
	* \param driverID is an ID of user written driver
	*/
	virtual void 		registerRenderingDriver(core::drivermodel::DriverID* driverID);

	//Multithreading part
	//! Create a thread of execution
	/*!
	 * Creates and start a thread of execution
	 * \param proc is an instance of Runnable object to use as thread method
	 * \return pointer to a newly created thread object
	 */
	virtual core::multithreading::Thread*	createThread(const core::multithreading::Runnable& proc);
	//! Destroy a thread of execution
	/*!
	 * Destroys a thread of execution. If thread is running, than it is killed gracelessly
	 * \param thrd is a pointer to a thread object to destroy
	 */
	virtual void								destroyThread(core::multithreading::Thread* thrd);
	//! Create a mutex
	 core::multithreading::Mutex*		createMutex();
	//! Destroy a mutex
	virtual void								destroyMutex(core::multithreading::Mutex*  mutex);
	//! Create a condition variable
	 core::multithreading::Condition*	createCondition();
	//! Destroy a condition variable
	virtual void								destroyCondition(core::multithreading::Condition* cond);

	virtual const char*							getApplicationName() const;
	virtual const char*							getApplicationCompany() const;
	virtual const char*							getConfigFileName() const;

};
}

#endif
