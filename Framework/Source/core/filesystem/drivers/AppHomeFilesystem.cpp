#include "core/filesystem/drivers/AppHomeFilesystem.h"
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

AppHomeFilesystem::~AppHomeFilesystem()
{
	//Destructor stub
}

//==============================~Destructor==============================

void		AppHomeFilesystem::setMountPoint(const EString& o)
{
	EString path;
	if (getenv("HOME"))
		path =  EString(getenv("HOME"));
	else if (getenv("USER"))
		path =  EString("/home/") + EString(getenv("USER"));
	else if (getenv("USERNAME"))
		path =  EString("/home/") + EString(getenv("USERNAME"));
#ifdef __WIN32
	else if (getenv("HOMEDRIVE") || getenv("HOMEPATH"))
		path =  EString(getenv("HOMEDRIVE")) + EString(getenv("HOMEPATH"));
	else path = "C:\\";
#endif
	path += "/" +EString(settings::application_company) + "/" + EString(settings::application_name);

	m_MountPoint = fs::system_complete(fs::path(path.c_str()));
	if(!fs::exists(m_MountPoint))
	{
		fs::create_directories(m_MountPoint);
	}
	if(!fs::is_directory(m_MountPoint))
		throw core::filesystem::FilesystemException(EString("Local filesystem driver error: Failed to mount driver as the mount point ") + path + (" is a not a directory"));
	//throw core::filesystem::FilesystemException("Done");
}

//==============================~Method: setMountPoint==============================

//============================== Method: id==============================

EString		AppHomeFilesystem::id() const
{
	return EString("app-home");
}

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace

