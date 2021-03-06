/*
 * Resource.h
 *
 *  Created on: 20.05.2009
 *      Author: vedenko
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "core/PluginCore.h"
#include "internal.h"

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "resources/ResourceException.h"

namespace core
{
namespace multithreading
{
class Mutex;
}
}


//! This namespace contains a various routines for maintaining resource management tasks
namespace resources
{
class Resource;
class ResourceManager;
namespace __internal
{
class ResourceLibrary;
template<typename T>
resources::Resource* 	createResource(T*	res);
template<typename T>
resources::Resource* 	setResource(Resource* res,T*);
// Sets resource as ready
EXPORT void					finalizeResource(resources::Resource*);
EXPORT void					destroyResource(resources::Resource*);
}
//! This class provides a general abstraction of resource
/*!
 * This class is general abstraction of a Resource conception in Freya 3D engine.
 * This class provides functionality for checking resource status, maintaining a single copy of resource
 * and other functionality related for easy and scalable resource management
 */
class EXPORT Resource: virtual public ::EngineSubsystem
{
	friend class resources::ResourceManager;
	friend class __internal::ResourceLibrary;
	template<typename T>
	friend resources::Resource* 	resources::__internal::createResource(T*);
	template<typename T>
	friend resources::Resource* 	resources::__internal::setResource(Resource* res,T*);
	friend void						resources::__internal::destroyResource(resources::Resource*);
	friend void						resources::__internal::finalizeResource(resources::Resource*);
private://TODO: make this private
	Resource();
	virtual ~Resource();
public:
	//! Check the status of the resource
	/*!
	 * Checks the status of resource
	 * \return true if Resource is ready to be used
	 */
	virtual bool	ready();
	//! Cast operator. T MUST be a pointer
	/*!
	 * Casts Resource to specific type
	 * \tparam T is a type to cast resource to. Must be a pointer type
	 * Please note, this method will block execution of a thread and wait until the resource is ready.
	 * Use it carefully
	 * \return casted resource
	 * \throw ResourceException if cast failed
	 */
	template<typename T>
	operator T();
	//! Get the value of data. T MUST be a pointer
	/*!
	 * Retrieves specific type resource from Resource wrapper.
	 * Please note, this method will block execution of a thread and wait until the resource is ready.
	 * Use it carefully
	 * \tparam T is a type of an resource. Must be a pointer type
	 * \return enclosed resource
	 * \throw ResourceException if cast failed
	 */
	template<typename T>
	T	get();
	//!Stop the execution of cuurent thread and wait until the resource is ready
	virtual void	waitForResource();
	//!Get the ID of an resource
	virtual EString	id();
protected:
	//methods
private:
	//data
	::EngineSubsystem* 								m_Resource;
	unsigned 										m_Ready;
	EString											m_ResourceID;

};

//========= Implementation ==============================================================
template<typename T>
Resource::operator T()
{
	waitForResource();
	T op = dynamic_cast<T> (m_Resource);
	if(op != NULL)
		return op;
	else
		throw resources::ResourceException(EString("Failed to cast data to required type: res_id =  ") + m_ResourceID);
}
template<typename T>
T	Resource::get()
{
	waitForResource();
	T op = dynamic_cast<T> (m_Resource);
	if(op != NULL)
		return op;
	else
		throw resources::ResourceException(EString("Failed to cast data to required type: res_id =  ") + m_ResourceID);
}

}

#endif /* RESOURCE_H_ */
