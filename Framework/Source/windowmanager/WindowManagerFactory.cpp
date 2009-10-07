#include "windowmanager/WindowManagerFactory.h"
//SDL
//#include "windowmanager/Drivers/SDL/SDLDriverID.h"
#include "core/drivermodel/DriverID.h"
#include "core/drivermodel/Driver.h"
#include "core/drivermodel/DriverException.h"


namespace windowmanager
{
//============================== Derived constructors==============================
WindowManagerFactory::WindowManagerFactory()
{
	//registerDriver(new windowmanager::drivers::sdl::SDLDriverID);
}
//==============================~Derived constructors==============================

//============================== Destructor==============================


WindowManagerFactory::~WindowManagerFactory()
{
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		delete it->second;
}

//==============================~Destructor==============================

//============================== Method: createDriver==============================

core::drivermodel::Driver*		WindowManagerFactory::createDriver(const EString& name)
{
	if(m_Drivers[name])
		return m_Drivers[name]->create();
	throw core::drivermodel::DriverException(EString("Failed to create window manager driver - ") + name + ": driver not found");
}

//==============================~Method: createDriver==============================

void							WindowManagerFactory::registerDriver(core::drivermodel::DriverID* driverID)
{
	m_Drivers[driverID->id()] = driverID;
}

EStringList	WindowManagerFactory::listDrivers() const
{
	EStringList		lst;
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::const_iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		lst.push_back(it->first);
	return lst;
}

} //End of windowmanager namespace


