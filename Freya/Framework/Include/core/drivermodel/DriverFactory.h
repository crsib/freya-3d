#ifndef _DRIVERFACTORY_H_
#define _DRIVERFACTORY_H_

#include "core/PluginCore.h"

namespace core
{
	extern core::PluginCore*	CoreInstance;
}

#include "core/EngineSubsystem.h"
#include "core/drivermodel/Driver.h"
#include "core/drivermodel/DriverID.h"
#include "core/EStringList.h"
namespace core
{
namespace drivermodel
{
//! Abstraction for driver factory
/*!
 *  All drivers should be created through a successor class of this interface.
 *  Drivers should be chosen by the id string
 */

class DriverFactory : virtual public ::EngineSubsystem
{
public:
	//!This method will create a driver, described with ID string
	/*!
	 * \param name is an id string for the driver
	 * \return newly created driver specified by id {name} or NULL, if requested driver is not registered
	 */
	virtual Driver* createDriver(const EString& name) = 0;

	virtual void	registerDriver(core::drivermodel::DriverID* driverID) = 0;

	virtual EStringList	listDrivers() const = 0;
}; //End of DriverFactory class

} //End of drivermodel namespace
} //End of core namespace
#endif //End of _DRIVERFACTORY_H_
