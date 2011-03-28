#ifndef _WINDOWMANAGERFACTORY_H_
#define _WINDOWMANAGERFACTORY_H_

#include "core/drivermodel/DriverFactory.h"
#include <map>
namespace core
{
class EngineCore;
namespace drivermodel
{
class DriverID;
class Driver;
}
}
namespace windowmanager
{

class WindowManagerFactory : public core::drivermodel::DriverFactory
{
	friend class core::EngineCore;
	WindowManagerFactory();
	virtual ~WindowManagerFactory();

public:
	virtual core::drivermodel::Driver* createDriver(const EString& name);
	virtual void					   registerDriver(core::drivermodel::DriverID* driverID);
	virtual EStringList	listDrivers() const;
private:
	std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > > m_Drivers;
}; //End of WindowManagerFactory class

} //End of windowmanager namespace

#endif //End of _WINDOWMANAGERFACTORY_H_
