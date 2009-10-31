/*
 * ShaderLoaderDriver.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 31, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef SHADERLOADERDRIVER_H_
#define SHADERLOADERDRIVER_H_

/*
 *
 */
#include "resources/ResourceManagerDriver.h"
#include "core/drivermodel/DriverID.h"

namespace resources
{

namespace drivers
{

namespace __std
{

class ShaderLoaderDriver : public resources::ResourceManagerDriver
{
private:
	friend class ShaderLoaderDriverID;
	friend class resources::ResourceManager;
	ShaderLoaderDriver( );
	virtual ~ShaderLoaderDriver( );
public:
	virtual bool		unique() const;
	virtual EString 	id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

class  ShaderLoaderDriverID : public core::drivermodel::DriverID
{
public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new ShaderLoaderDriver;
	}
	virtual
	EString							id() const
	{
		return 	"shader";
	}
};

}

}

}

#endif /* SHADERLOADERDRIVER_H_ */
