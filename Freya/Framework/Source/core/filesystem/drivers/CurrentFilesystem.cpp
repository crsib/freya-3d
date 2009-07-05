#include "core/filesystem/drivers/CurrentFilesystem.h"
#include "core/filesystem/FilesystemException.h"
#include "application-settings.h"

#include <iostream>
namespace core
{
namespace filesystem
{
namespace drivers
{
//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

CurrentFilesystem::~CurrentFilesystem()
{
	//Destructor stub
}

//==============================~Destructor==============================

void		CurrentFilesystem::setMountPoint(const EString& o)
{
	m_MountPoint = fs::current_path();
}

//==============================~Method: setMountPoint==============================

//============================== Method: id==============================

EString		CurrentFilesystem::id() const
{
	return EString("pwd");
}

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
