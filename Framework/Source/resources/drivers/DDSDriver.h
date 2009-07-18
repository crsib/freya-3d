/*
 * DDSDriver.h
 *
 *  Created on: 18.07.2009
 *      Author: vedenko
 */

#ifndef DDSDRIVER_H_
#define DDSDRIVER_H_

/*
 *
 */
#include "resources/ResourceManagerDriver.h"
#include "core/drivermodel/DriverID.h"

namespace resources
{
class ResourceManager;
namespace drivers
{

class DDSDriver;

class DDSDriver : public resources::ResourceManagerDriver
{
	friend class DDSDriverID;
	friend class resources::ResourceManager;
	DDSDriver();
	virtual ~DDSDriver();
public:
	virtual bool	unique() const;
	virtual EString id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

class  DDSDriverID : public core::drivermodel::DriverID
{
public:
	virtual core::drivermodel::Driver*		create()
	{
		return new DDSDriver;
	}
	virtual EString							id()
	{
		return 	"dds";
	}
};

}

}

#endif /* DDSDRIVER_H_ */
