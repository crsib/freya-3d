// TextureLoader.cpp
//Created on : 10.05.2010
//Authors :
//	Sverchinskij Vitalij
#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include "resources/ResourceManagerDriver.h"
#include "core/drivermodel/DriverID.h"

namespace resources {
	namespace drivers {
		namespace __std {
			
			class TextureLoaderDriverID;

			class TextureLoader : public resources::ResourceManagerDriver {
				friend class TextureLoaderDriverID;
				friend class resources::ResourceManager;
			private :
				TextureLoader();
				virtual ~TextureLoader();
			public:
				virtual bool		unique() const;
				virtual EString 	id() const;
				virtual Resource*	loadSynchronous(const EString& ID);
				virtual Resource*	loadAsynchronous(const EString& ID);
				virtual void 		destroy(Resource* res);
			};

			class TextureLoaderDriverID : public core::drivermodel::DriverID {
			public :
				virtual core::drivermodel::Driver* create() const {
					return new TextureLoader;
				}

				virtual EString id() const {
					return 	"texture";
				}
			};
		}
	}
}
#endif//TEXTURELOADER_H_