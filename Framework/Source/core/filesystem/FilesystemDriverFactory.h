#ifndef _FILESYSTEMDRIVERFACTORY_H_
#define _FILESYSTEMDRIVERFACTORY_H_

#include "core/drivermodel/DriverFactory.h"
#include "core/memory/MemoryAllocator.h"
#include <map>
namespace core
{
namespace filesystem
{
//!This class is a driver factory to create filesystem drivers
class FilesystemDriverFactory : public core::drivermodel::DriverFactory
{
	friend class Filesystem;
	friend class FilesystemInternal;
	FilesystemDriverFactory();
	virtual ~FilesystemDriverFactory();

public:
	//!This method is documented in DriverFactory class
	virtual core::drivermodel::Driver*  createDriver(const EString& name);
	virtual void						registerDriver(core::drivermodel::DriverID* driverID);
	virtual EStringList	listDrivers() const;
private:
	std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > > m_Drivers;
}; //End of FilesystemDriverFactory class

} //End of filesystem namespace
} //End of core namespace
#endif //End of _FILESYSTEMDRIVERFACTORY_H_
