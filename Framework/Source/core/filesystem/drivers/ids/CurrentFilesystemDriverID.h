/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef CURRENTFILESYSTEMDRIVERID_H_
#define CURRENTFILESYSTEMDRIVERID_H_

#include "core/drivermodel/DriverID.h"
#include "core/filesystem/drivers/CurrentFilesystem.h"
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

class CurrentFilesystemDriverID : public core::drivermodel::DriverID
{
public:
	CurrentFilesystemDriverID()
	{
	}
	virtual ~CurrentFilesystemDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new CurrentFilesystem();
	}

	virtual EString							id() const
	{
		return "pwd";
	}
};

}

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
