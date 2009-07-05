#ifndef _INPUTDEVICEFACTORY_H_
#define _INPUTDEVICEFACTORY_H_

#include "core/drivermodel/DriverFactory.h"
#include <map>

namespace windowmanager
{
namespace drivers
{
namespace sdl
{
class SDLManagerDriver;
}
}

namespace input
{
namespace drivers
{
namespace sdl
{

class InputDeviceFactory : public core::drivermodel::DriverFactory
{
	friend class windowmanager::drivers::sdl::SDLManagerDriver;
	InputDeviceFactory();
	virtual ~InputDeviceFactory();
public:
	virtual core::drivermodel::Driver* 	createDriver(const EString& name);
	virtual void						registerDriver(core::drivermodel::DriverID* driverID);
	virtual EStringList	listDrivers() const;
private:
	std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > > m_Drivers;
}; //End of InputDeviceFactory class

} //End of sdl namespace
} //End of drivers namespace
} //End of input namespace
} //End of windowmanager namespace

#endif //End of _INPUTDEVICEFACTORY_H_
