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
	friend class core::filesystem::FilesystemDriverFactory;
protected:
	CurrentFilesystemDriverID()
	{
	}
	virtual ~CurrentFilesystemDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new CurrentFilesystem();
	}

	virtual EString							id()
	{
		return "pwd";
	}
};

}

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
