/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef LZMAFILESYSTEMDRIVERID_H_
#define LZMAFILESYSTEMDRIVERID_H_

#include "core/drivermodel/DriverID.h"
#include "core/filesystem/drivers/LzmaDriver.h"
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

class LzmaFilesystemDriverID : public core::drivermodel::DriverID
{
public:
	LzmaFilesystemDriverID()
	{
	}
	virtual ~LzmaFilesystemDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new LzmaDriver();
	}

	virtual EString							id() const
	{
		return "lzma";
	}
};

}

}

}

}

#endif /* LOCALFILESYSTEMDRIVERID_H_ */
