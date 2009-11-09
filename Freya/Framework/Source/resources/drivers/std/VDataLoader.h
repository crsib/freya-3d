/*
 * VDataLoader.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 9, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef VDATALOADER_H_
#define VDATALOADER_H_

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

class VDataLoader : public resources::ResourceManagerDriver
{
	friend class VDataLoaderDriverID;
	friend class resources::ResourceManager;
private:
	VDataLoader( );
	virtual ~VDataLoader( );
public:
	virtual bool		unique() const;
	virtual EString 	id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

class  VDataLoaderDriverID : public core::drivermodel::DriverID
{
public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new VDataLoader;
	}
	virtual
	EString							id() const
	{
		return 	"vbo";
	}
};

}

}

}

#endif /* VDATALOADER_H_ */
