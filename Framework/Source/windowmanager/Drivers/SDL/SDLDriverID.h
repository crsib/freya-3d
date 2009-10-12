/*
 * LocalFilesystemDriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef SDLDRIVERID_H_
#define SDLDRIVERID_H_

#include "core/drivermodel/DriverID.h"
#include "windowmanager/Drivers/SDL/SDLManagerDriver.h"
/*
 *
 */
namespace windowmanager
{

class WindowManagerFactory;
namespace drivers
{

namespace sdl
{

class SDLDriverID : public core::drivermodel::DriverID
{
public:
	SDLDriverID()
	{
	}
	virtual ~SDLDriverID()
	{
	}

public:
	virtual core::drivermodel::Driver*		create() const
	{
		return new SDLManagerDriver();
	}

	virtual EString							id() const
	{
		return "SDL";
	}
};

}

}

}
#endif /* LOCALFILESYSTEMDRIVERID_H_ */
