/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef LOCALFILESYSTEMDRIVERID_H_
#define LOCALFILESYSTEMDRIVERID_H_

#include "core/drivermodel/DriverID.h"
#include "core/filesystem/drivers/LocalFilesystemDriver.h"
/*
 *
 */
namespace core
{

namespace filesystem
{
class FilesystemDriverFactory;
namespace drivers
{

namespace ids
{

class LocalFilesystemDriverID : public core::drivermodel::DriverID
{
public:
	LocalFilesystemDriverID()
	{
	}
	virtual ~LocalFilesystemDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new LocalFilesystemDriver();
	}

	virtual EString							id() const
	{
		return "local";
	}
};

}

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
