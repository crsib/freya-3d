/*
 * TGADriver.h
 *
 *  Created on: 07.07.2009
 *      Author: vedenko
 */

#ifndef TGADRIVER_H_
#define TGADRIVER_H_

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

class TGADriver;

class TGADriver : public resources::ResourceManagerDriver
{
	friend class TGADriverID;
	friend class resources::ResourceManager;
	TGADriver();
	virtual ~TGADriver();
public:
	virtual bool	unique() const;
	virtual EString id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

class  TGADriverID : public core::drivermodel::DriverID
{
public:
	virtual core::drivermodel::Driver*		create()
	{
		return new TGADriver;
	}
	virtual EString							id()
	{
		return 	"tga";
	}
};

}

}

#endif /* TGADRIVER_H_ */
