/*
 * ResourceManager.h
 *
 *  Created on: 21.05.2009
 *      Author: vedenko
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "core/EString.h"

#include "core/drivermodel/DriverID.h"

#include "core/memory/MemoryAllocator.h"
#include <map>

namespace core
{
class EngineCore;
}

namespace resources
{
class Resource;
class ResourceManagerDriver;

namespace __internal
{
	class ResourceLibrary;
}
//!Resource manager subsytem
/*!
 * This class provides interface to the resource management subsystem. All tasks, such as
 * creating resources and destroying them should be done using this class.
 * Basic concepts:<BR>
 * <OL>
 * <LI><STRONG>Resource</STRONG> is a container, used to store information about resource. It provides all data, needed for correct synchronization
 * of resource management subsystem. Container could be casted into specific resource type using methods, provided by Resource class </LI>
 * <LI><STRONG>Resource ID</STRONG> is an unique identifier of resource. It should be represented in following way: <CODE>:{resource loader name}[:param_1:...[param_n]]</CODE>
 * For example: <CODE>:primitive:sphere:20:30</CODE></LI>.
 * Resource manger does not provide any direct access to the filesystem. If you want to access filesystem (either from resource loader, either directly) you should use core::filesystem::Filesystem
 * functionality
 * </OL>
 */
class ResourceManager: virtual public ::EngineSubsystem
{
	friend class core::EngineCore;
private:
	ResourceManager();
	virtual ~ResourceManager();
public:
	//! This enum is used to choose the correct loading method for the resource
	enum	immediately
	{
		//! Load resource immediately
		IMMEDIATELY
	};
	//! This enum is used to choose the correct loading method for the resource
	enum	asynchronous
	{
		//! Load resource asynchronously
		ASYNCHRONOUS
	};
	//! This method is used to load resource synchronously
	/*!
	 * Loads a resource, identified by ID using driver, retrieved from ID's first part.
	 * First checks, if we really need to load the resource
	 * \param ID is an ID of a resource to be loaded
	 * \param t must be IMMEDIATELY
	 * \return a loaded resource descriptor
	 * \throw ResourceException on any error
	 */
	Resource*	load(const EString& ID,immediately t);
	//! This method is used to load resource asynchronously
	/*!
	 * Request the driver, specified by the first part of ID to load resource and returns a resource descriptor
	 * of a possibly not loaded resource.
	 * First checks, if we really need to load the resource
	 * \param ID is an ID of a resource to be loaded
	 * \param t must be ASYNCHRONOUS
	 * \return a resource descriptor
	 * \throw ResourceException on any error
	 */
	Resource*	load(const EString& ID,asynchronous t = ASYNCHRONOUS);
	//! Free a resource
	/*!
	 * Returns the resource to the resource management system. This does not actually mean the deletion of resource,
	 * it just notifies system that one of the resource copies became unneeded
	 * \param res is a resource descriptor of the resource to be freed
	 */
	void		free(Resource* res);
	//! Register resource loader driver
	/*!
	 * Registers resource loader driver in resource manager
	 * \param driverID is an identification class of the driver as described by drivermodel
	 * \throw ResourceException on any error
	 */
	void		registerDriver(core::drivermodel::DriverID* driverID);
private:
	typedef	std::map<EString,ResourceManagerDriver*,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,ResourceManagerDriver*> > >	__DriverLibrary;
	__DriverLibrary										m_Drivers;
	resources::__internal::ResourceLibrary*				m_ResourceLibrary;

	ResourceManagerDriver*			__findDriver(const EString& ID);
};

}

#endif /* RESOURCEMANAGER_H_ */
