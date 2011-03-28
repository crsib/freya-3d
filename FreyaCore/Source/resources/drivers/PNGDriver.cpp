// PNGDriver.cpp
//Created on 05.05.2010
//Authors: 
//	Sverchinskij Vitalij

#include "core/PluginCore.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"
#include "core/filesystem/Filesystem.h"
#include "core/memory/MemoryAllocator.h"
#include "resources/Resource.h"
#include "core/taskmanager/TaskManager.h"
#include "PNGDriver.h"
#include "PNGDriverASyncLoader.h"

namespace resources {
	
	namespace __internal {
		template<>
		resources::Resource* 	createResource(renderer::Texture*	resource)
		{
			resources::Resource* res = new resources::Resource;
			if(resource == NULL)
				return res;
			res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
			if(res->m_Resource == NULL)
				throw resources::ResourceException ("Failed to create resource");
			return res;
		}

		template<>
		resources::Resource*
		setResource(Resource* res,renderer::Texture*	resource)
		{
			res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
			if(res->m_Resource == NULL)
				throw resources::ResourceException ("Failed to create resource");
			return res;
		}
	}//namespace __internal

	namespace drivers {
		
		PNGDriver::PNGDriver() { }
		PNGDriver::~PNGDriver() { }

		bool PNGDriver::unique() const {
			return true;
		}

		EString PNGDriver::id() const {
			return "png";
		}

		Resource* PNGDriver::loadSynchronous(const EString& ID) {
			return NULL;
		}

		Resource* PNGDriver::loadAsynchronous(const EString& ID) {
			bool mipmaps = false;
			EString path("");
			size_t scursor = 0;
			size_t ecursor = ID.find(':', 1);
			if(ID.substr(scursor, ecursor) == ":png") {
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
			using png_driver_internal::PNGDriverASyncLoader;
			PNGDriverASyncLoader* png_loader= new PNGDriverASyncLoader(path, mipmaps);
			core::CoreInstance->getTaskManager()->addAsynchronousTask(png_loader);
			return png_loader->getResource();
		}

		void PNGDriver::destroy(Resource* res) {
			if(!res->ready())
				return;
			renderer::Texture* tex = res->get<renderer::Texture*>();
			core::CoreInstance->getRenderingDriver()->destroyTexture(tex);
			resources::__internal::destroyResource(res);
		}
	}//namespace drivers
}//namespace resources