#include "core/filesystem/drivers/CurrentFilesystem.h"
#include "core/filesystem/FilesystemException.h"
#include "application-settings.h"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif
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
#ifndef	__APPLE__
	m_MountPoint = fs::current_path();
#else
	//We are going to mount "Resource path"
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
	CFStringRef str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
	CFRelease(resourcesURL);
	char path[PATH_MAX];
	
	CFStringGetCString( str, path, FILENAME_MAX, kCFStringEncodingASCII );
	CFRelease(str);
	EString tmp = EString(path) + "/Contents/Resources";
	m_MountPoint = tmp.c_str();
#endif
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
