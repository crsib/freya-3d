/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef APPHOMEFILESYSTEMDRIVERID_H_
#define APPHOMEFILESYSTEMDRIVERID_H_

#include "core/drivermodel/DriverID.h"
#include "core/filesystem/drivers/AppHomeFilesystem.h"
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

class AppHomeFilesystemDriverID : public core::drivermodel::DriverID
{
public:
	AppHomeFilesystemDriverID()
	{
	}
	virtual ~AppHomeFilesystemDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create()
	{
		return new AppHomeFilesystem();
	}

	virtual EString							id()
	{
		return "app-home";
	}
};

}

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
