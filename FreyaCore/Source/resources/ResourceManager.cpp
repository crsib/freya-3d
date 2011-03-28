/*
 * ResourceManager.cpp
 *
 *  Created on: 21.05.2009
 *      Author: vedenko
 */

#include "resources/ResourceManager.h"
#include "resources/ResourceLibrary.h"
#include "resources/ResourceManagerDriver.h"
#include "core/multithreading/Mutex.h"
//Default drivers
#include "resources/drivers/std/ShaderLoaderDriver.h"
#include "resources/drivers/std/FileLoaderDriver.h"
#include "resources/drivers/std/VDataLoader.h"
#include "resources/drivers/std/TextureLoader.h"
//TODO: DBG
#include <iostream>

namespace resources
{

ResourceManager::ResourceManager()
{
	m_ResourceLibrary = new __internal::ResourceLibrary;
	//Default drivers registration
	registerDriver(new resources::drivers::__std::ShaderLoaderDriverID());
	registerDriver(new resources::drivers::__std::FileLoaderDriverID());
	registerDriver(new resources::drivers::__std::VDataLoaderDriverID());
	registerDriver(new resources::drivers::__std::TextureLoaderDriverID());
}

ResourceManager::~ResourceManager()
{
	Resource* res;
	while((res = m_ResourceLibrary->pop()) != NULL)
	{
		ResourceManagerDriver*	drv = __findDriver(res->id());
		if(drv)
			drv->destroy(res);
	}
	delete m_ResourceLibrary;
	for(__DriverLibrary::iterator it = m_Drivers.begin();it != m_Drivers.end(); ++it)
	{
		delete it->second;
	}
}

Resource*	ResourceManager::load(const EString& ID,immediately t)
{
	(void)((t));
	ResourceManagerDriver *drv = __findDriver(ID);
	if(drv)
	{
		Resource*				res;
		if(drv->unique())
		{
			if((res = m_ResourceLibrary->query(ID))!=NULL)
			{
				m_ResourceLibrary->add(ID);
				return res;
			}
			else
			{
				res = drv->loadSynchronous(ID);
				m_ResourceLibrary->add(ID,res);
				return res;
			}
		}
		else
		{
			return drv->loadSynchronous(ID);
		}
	}
	throw resources::ResourceException(EString("Failed to find driver to manage query: " + ID));
}

Resource *ResourceManager::load(const EString & ID, asynchronous t)
{
	(void)((t));
	ResourceManagerDriver *drv = __findDriver(ID);
	if(drv)
	{
		Resource*				res;
		if(drv->unique())
		{
			if((res = m_ResourceLibrary->query(ID))!= NULL)
			{
				m_ResourceLibrary->add(ID);
				return res;
			}
			else
			{
				res = drv->loadAsynchronous(ID);
				m_ResourceLibrary->add(ID,res);
				return res;
			}
		}
		else
		{
			return drv->loadAsynchronous(ID);
		}
	}
	throw resources::ResourceException(EString("Failed to find driver to manage query: " + ID));
}

void ResourceManager::free(Resource *res)
{
	ResourceManagerDriver *drv = __findDriver(res->id());
	if(drv->unique()){
		if(m_ResourceLibrary->remove(res)){
			drv->destroy(res);
		}
	}
	else{
		drv->destroy(res);
	}
}

void ResourceManager::registerDriver(core::drivermodel::DriverID *driverID)
{
	m_Drivers[driverID->id()] = static_cast<ResourceManagerDriver*>(driverID->create());
}

void ResourceManager::invalidateResources()
{
	Resource *res;
	while((res = m_ResourceLibrary->pop()) != NULL)
	{
		ResourceManagerDriver*	drv = __findDriver(res->id());
		drv->destroy(res);
		res->m_Ready = 0;
		m_ResourceCache[drv->loadAsynchronous(res->id())] = res;
	}
}

bool ResourceManager::isReady()
{
	if(m_ResourceCache.size() == 0)
		return true;
	for(ResourceCache::iterator it = m_ResourceCache.begin();it!=m_ResourceCache.end();)
	{
		Resource* res = it->first;
		if(res->m_Ready)
		{
			it->second->m_Ready = 1;
			it->second->m_Resource = res->m_Resource;
			ResourceCache::iterator temp = it;
			++it;
			m_ResourceCache.erase(temp);
			delete res;
		}
		else
			++it;
	}
	if(m_ResourceCache.size() == 0)
		return true;
	return false;
}

ResourceManagerDriver*			ResourceManager::__findDriver(const EString& ID)
{
	size_t		_1 = ID.find(':');
	size_t		_2 = ID.find(':',_1 + 1);
	EString		drvID = ID.substr(_1 + 1,_2 - _1 - 1);
	__DriverLibrary::iterator it = m_Drivers.find(drvID);
	if(it != m_Drivers.end())
		return it->second;
	return NULL;
}

}
