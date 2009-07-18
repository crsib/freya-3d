/*
 * ResourceFactory.h
 *
 *  Created on: 07.07.2009
 *      Author: vedenko
 */

#ifndef RESOURCEFACTORY_H_
#define RESOURCEFACTORY_H_
#include "resources/Resource.h"
#include "core/multithreading/Mutex.h"
namespace resources
{
namespace __internal
{

template<typename T>
resources::Resource* 	createResource(T*	resource)
{
	resources::Resource* res = new resources::Resource;
	res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
	if(res->m_Resource == NULL)
		throw resources::ResourceException ("Failed to create resource");
	return res;
}

void					destroyResource(resources::Resource* res);
void					finalizeResource(resources::Resource*);
}
}

#endif /* RESOURCEFACTORY_H_ */
