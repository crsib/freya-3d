/*
 * DDSDiver.cpp
 *
 *  Created on: 18.07.2009
 *      Author: vedenko
 */
//#include "renderer/DriverSubsystems/Texture.h"
//#include "core/EngineException.h"
//#include "core/PluginCore.h"
//#include "renderer/RenderingAPIDriver.h"
//#include "core/filesystem/Filesystem.h"

#include "DDSDriver.h"
#include "DDSDriverInternal.h"

namespace resources
{
namespace drivers {

DDSDriver::DDSDriver()
{

}

DDSDriver::~DDSDriver()
{
	
}

bool	DDSDriver::unique() const
{
	return true;	
}

EString DDSDriver::id() const
{
	return "dds";
}

Resource*	DDSDriver::loadSynchronous(const EString& ID)
{
	return NULL;	
}

Resource*	DDSDriver::loadAsynchronous(const EString& ID)
{
	bool mipmaps = false;
	EString path("");
	size_t scursor = 0;
	size_t ecursor = ID.find(':', 1);
	//example ":dds:Textures/diffuse.dds:mipmaps"
	if(ID.substr(scursor, ecursor) == ":dds") {
		//waiting for path and mipmap parameters		
		scursor = ecursor + 1;
		ecursor = ID.find(':', scursor);
		if(ecursor != ID.npos) {
			//both left
			if(ID.substr(scursor, ecursor - scursor) == "mipmaps")
				mipmaps = true;
			else
				path = ID.substr(scursor, ecursor - scursor);

			scursor = ecursor + 1;
			ecursor = ID.find(':', scursor);
			//hm... what could it be?
			if(ecursor != ID.npos)
				throw(resources::ResourceException("Malformed resource ID"));
			//at this moment one of path or mipmaps was set
			if(mipmaps)
				path = ID.substr(scursor);// no way
			else // for more ensurance
				if(ID.substr(scursor) != "mipmaps")
					throw(resources::ResourceException("Malformed resource ID"));
			mipmaps = true;
		} else //it must be a path.
			path = ID.substr(scursor);
	}
	else //shit happens...
		throw resources::ResourceException("Malformed resource ID");
	using dds_driver_internal::DDSDriverAsyncLoader;
	DDSDriverAsyncLoader* loader = new DDSDriverAsyncLoader(path, mipmaps);
	core::CoreInstance->getTaskManager()->addAsynchronousTask(loader);
	return loader->getResource();
}

void DDSDriver::destroy(Resource* res)
{
	if(!res->ready())
		return;
	renderer::Texture* tex = res->get<renderer::Texture*>();
	core::CoreInstance->getRenderingDriver()->destroyTexture(tex);
	resources::__internal::destroyResource(res);
}

}// namespace drivers
}
