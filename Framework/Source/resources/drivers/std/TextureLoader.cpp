// TextureLoader.cpp
//Created on : 10.05.2010
//Authors :
//	Sverchinskij Vitalij

#include "TextureLoader.h"
#include "resources/ResourceManager.h"
#include "renderer/DriverSubsystems/Texture.h"

namespace resources {

	namespace __internal {
	
		template<>
		resources::Resource* createResource(renderer::Texture* resource)
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
		resources::Resource* setResource(Resource* res,renderer::Texture* resource)
		{
			res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
			if(res->m_Resource == NULL)
				throw resources::ResourceException ("Failed to set resource");
			return res;
		}

	}//namespace __internal

	namespace drivers {
		namespace __std {
			TextureLoader::TextureLoader() { }
			TextureLoader::~TextureLoader() { }

			void TextureLoader::destroy(Resource* res) {
			}

			Resource* TextureLoader::loadAsynchronous(const EString& ID) {
				size_t ext_spos = ID.find_last_of('.') + 1;
				if(ext_spos == ID.npos)
					throw ResourceException("File name must contain an extension.");				
				size_t ext_sz = ID.npos;								
				size_t ext_epos = ID.find(':', ext_spos);				
				if(ext_epos != ID.npos)
					ext_sz = ext_epos - ext_spos;
				EString ext(ID.substr(ext_spos, ext_sz));
				EString ret(":");
				ret.append(ext);
				ret.append(ID.substr(EString(":texture").length()));
				return core::CoreInstance->getResourceManager()->load(ret, resources::ResourceManager::ASYNCHRONOUS);
			}

			Resource* TextureLoader::loadSynchronous(const EString& ID) {
				size_t ext_spos = ID.find_last_of('.') + 1;
				if(ext_spos == ID.npos)
					throw ResourceException("File name must contain an extension.");				
				size_t ext_sz = ID.npos;								
				size_t ext_epos = ID.find(':', ext_spos);				
				if(ext_epos != ID.npos)
					ext_sz = ext_epos - ext_spos;
				EString ext(ID.substr(ext_spos, ext_sz));
				EString ret(":");
				ret.append(ext);
				ret.append(ID.substr(EString(":texture").length()));
				return core::CoreInstance->getResourceManager()->load(ret, resources::ResourceManager::IMMEDIATELY);
			}

			bool TextureLoader::unique() const {
				return true;
			}

			EString TextureLoader::id() const {
				return "texture";
			}
		}//namespace __std
	}//namespace drivers
}//namespace resources