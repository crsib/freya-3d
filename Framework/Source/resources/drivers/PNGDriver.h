// PNGDriver.h
//Created on 05.05.2010
//Authors: 
//	Sverchinskij Vitalij

#ifndef PNG_DRIVER_H_
#define PNG_DRIVER_H_

#include "resources/ResourceManagerDriver.h"
#include "core/drivermodel/DriverID.h"

namespace resources
{
	class ResourceManager;
	
	namespace drivers
	{
		class PNGDriver : public resources::ResourceManagerDriver {
			friend class PNGDriverID;
			friend class resources::ResourceManager;
			PNGDriver();
			virtual ~PNGDriver();
		public:
			virtual bool		unique() const;
			virtual EString		id() const;
			virtual Resource*	loadSynchronous(const EString& ID);
			virtual Resource*	loadAsynchronous(const EString& ID);
			virtual void 		destroy(Resource* res);
		};//class PNGDriver

		class  PNGDriverID : public core::drivermodel::DriverID
		{
		public:
			virtual core::drivermodel::Driver* create() const
			{
				return new PNGDriver;
			}
			virtual EString id() const
			{
				return "png";
			}
		};//class PNGDriverID

	}//namespace drivers
}//nampespace resources


#endif//PNG_DRIVER_H_