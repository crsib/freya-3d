/*
 * DriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef DRIVERID_H_
#define DRIVERID_H_

#include "core/PluginCore.h"
#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
	extern core::PluginCore*	CoreInstance;
}
#else
namespace core
{
	extern core::PluginCore*	CoreInstance;
}

#endif

#include "core/EngineSubsystem.h"
#include "core/EString.h"

/*
 *
 */
namespace core
{
namespace drivermodel
{
class Driver;

enum		PLUGIN_COMPONENT
{
	FILESYSTEM = 1,
	RENDERER,
	RESOURCE,
	WINDOWMANAGER,
	INPUT,
};
	
class DriverID : virtual public ::EngineSubsystem
{
public:
	virtual ~DriverID(){}
	virtual core::drivermodel::Driver*		create()const = 0;
	virtual EString							id()	const = 0;
};

}
}
#endif /* DRIVERID_H_ */
