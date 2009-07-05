/*
 * ResourceManagerDriver.h
 *
 *  Created on: 22.05.2009
 *      Author: vedenko
 */

#ifndef RESOURCEMANAGERDRIVER_H_
#define RESOURCEMANAGERDRIVER_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"
#include "resources/Resource.h"

namespace resources
{
//!This class is an interface to resource loader subsystems
/*!
 * This abstraction is an interface to resource loader subsystem.
 * All Resource loaders should be inherited from this class providing the correct functionality.
 * If loader does not support asynchronous loading, the behavior of the asynchronous method should be like the behavior of synchronous one.
 * Each resource loader system should be correctly described by the correct ID class
 */
class ResourceManagerDriver: public core::drivermodel::Driver
{
public:
	//! Check, whether resources loaded by the driver are unique in sense of ID
	/*!
	 * Checks, whether resources loaded by the driver are unique in sense of ID
	 * \return true, if resource is uniquely described by resource ID, false otherwise.
	 */
	virtual bool	unique() const = 0;
	//! Get the ID of the driver.
	/*!
	 * Returns the ID string of driver. This string is used to determine, which
	 * driver should be used to load resource, i.e. it is equal to the first part of resource ID.
	 * For example, resource ID :primitive:sphere:30:30 stands for <STRONG>primitive</STRONG> driver ID
	 */
	virtual EString id() const  = 0;
	//! Load resource synchronously
	/*!
	 * Loads the resource immediately.
	 * \param ID is an identification string of a resource, containing the driver id part
	 * \return resource descriptor.
	 * \throw ResourceException on any error occurred
	 */
	virtual Resource*	loadSynchronous(const EString& ID) = 0;
	//! Load resource asynchronously
	/*!
	 * Creates the task to load resource and returns immediately.
	 * If loader does not support asynchronous loading, the behavior of the asynchronous method should be like the behavior of synchronous one.
	 * \param ID is an identification string of a resource, containing the driver id part
	 * \return resource descriptor.
	 * \throw ResourceException on any error occurred
	 */
	virtual Resource*	loadAsynchronous(const EString& ID) = 0;
	//! Destroy resource correctly
	/*!
	 * This method is called by manager when resource is not needed anymore by system
	 * \param res is resource descriptor to delete
	 */
	virtual void 		destroy(Resource* res) = 0;
};

}

#endif /* RESOURCEMANAGERDRIVER_H_ */
