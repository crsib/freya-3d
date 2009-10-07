#include "core/filesystem/FilesystemDriverFactory.h"

//Filesystem drivers headers
/*
#include "core/filesystem/drivers/ids/LocalFilesystemDriverID.h"
#include "core/filesystem/drivers/ids/LzmaFilesystemDriverID.h"
#include "core/filesystem/drivers/ids/AppHomeFilesystemDriverID.h"
#include "core/filesystem/drivers/ids/CurrentFilesystemDriverID.h"
*/
#include "core/drivermodel/DriverException.h"
namespace core
{
namespace filesystem
{
//============================== Derived constructors==============================
FilesystemDriverFactory::FilesystemDriverFactory()
{
	//registerDriver(new core::filesystem::drivers::ids::LocalFilesystemDriverID());
	//registerDriver(new core::filesystem::drivers::ids::LzmaFilesystemDriverID());
	//registerDriver(new core::filesystem::drivers::ids::AppHomeFilesystemDriverID());
	//registerDriver(new core::filesystem::drivers::ids::CurrentFilesystemDriverID());
}
//==============================~Derived constructors==============================

//============================== Destructor==============================

FilesystemDriverFactory::~FilesystemDriverFactory()
{
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		delete it->second;
}

//==============================~Destructor==============================

//============================== Method: createDriver==============================

core::drivermodel::Driver*		FilesystemDriverFactory::createDriver(const EString& name)
{
	if(m_Drivers[name])
		return m_Drivers[name]->create();
	throw core::drivermodel::DriverException(EString("Failed to create filesystem driver - ") + name + ": driver not found");
}

//==============================~Method: createDriver==============================

void							FilesystemDriverFactory::registerDriver(core::drivermodel::DriverID* driverID)
{
	m_Drivers[driverID->id()] = driverID;
}

EStringList	FilesystemDriverFactory::listDrivers() const
{
	EStringList		lst;
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::const_iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		lst.push_back(it->first);
	return lst;
}

} //End of filesystem namespace
} //End of core namespace

