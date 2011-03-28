#include "windowmanager/Drivers/SDL/InputDeviceFactory.h"
#include "windowmanager/Drivers/SDL/InputDevices/ids/SDLKeyboardID.h"
#include "windowmanager/Drivers/SDL/InputDevices/ids/SDLMouseID.h"
#include "windowmanager/Drivers/SDL/InputDevices/ids/SDLMouseButtonsID.h"
#include "core/drivermodel/DriverID.h"
#include "core/drivermodel/DriverException.h"


namespace windowmanager
{
namespace input
{
namespace drivers
{
namespace sdl
{
//============================== Derived constructors==============================
InputDeviceFactory::InputDeviceFactory()
{
	registerDriver(new windowmanager::input::drivers::sdl::ids::SDLKeyboardID);
	registerDriver(new windowmanager::input::drivers::sdl::ids::SDLMouseID);
	registerDriver(new windowmanager::input::drivers::sdl::ids::SDLMouseButtonsID);
}
//==============================~Derived constructors==============================

//============================== Destructor==============================

InputDeviceFactory::~InputDeviceFactory()
{
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		delete it->second;
}

//==============================~Destructor==============================

core::drivermodel::Driver* InputDeviceFactory::createDriver(const EString& name)
{
	if(m_Drivers[name])
		return m_Drivers[name]->create();
	throw core::drivermodel::DriverException(EString("Failed to create input device driver - ") + name + ": driver not found");
}

void						InputDeviceFactory::registerDriver(core::drivermodel::DriverID*	driverID)
{
	m_Drivers[driverID->id()] = driverID;
}

EStringList	InputDeviceFactory::listDrivers() const
{
	EStringList		lst;
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::const_iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		lst.push_back(it->first);
	return lst;
}

} //End of sdl namespace
} //End of drivers namespace
} //End of input namespace
} //End of windowmanager namespace

