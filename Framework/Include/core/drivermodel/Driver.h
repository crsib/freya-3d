#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "core/PluginCore.h"

namespace core
{
	extern core::PluginCore*	CoreInstance;
}

#include "core/EngineSubsystem.h"
#include "core/EString.h"

namespace core
{
//!This namespace contains all data related to Freya 3D engine drivermodel
namespace drivermodel
{
//!This class is a base class for all engine drivers
/*!
 * All classes acting as drivers must be inherited from this class
 */

class Driver : virtual public ::EngineSubsystem
{
public:
	//This method returns an ID string of a driver.
	//Any class, inherited from driver must implement this method.
	//!id function
	/*!
	 * This function must be implemented by any Freya driver
	 *\return Identification string of a driver
	 */
	virtual EString id() const  = 0;


}; //End of Driver class

} //End of drivermodel namespace
} //End of core namespace
#endif //End of _DRIVER_H_
