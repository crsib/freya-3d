#ifndef _APPHOMEFILESYSTEM_H_
#define _APPHOMEFILESYSTEM_H_


#include "core/filesystem/drivers/LocalFilesystemDriver.h"

namespace core
{
namespace filesystem
{
namespace drivers
{
namespace ids
{
class AppHomeFilesystemDriverID;
}
}
}
}

namespace core
{
namespace filesystem
{
class Filesystem;
namespace drivers
{

class AppHomeFilesystem : public core::filesystem::drivers::LocalFilesystemDriver
{
	friend class core::filesystem::drivers::ids::AppHomeFilesystemDriverID;
	friend class core::filesystem::Filesystem;
	AppHomeFilesystem()
	{

	}
	virtual ~AppHomeFilesystem();
protected:
	virtual void setMountPoint(const EString& path);

public:
	virtual EString id() const;

}; //End of AppHomeFilesystem class

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
#endif //End of _APPHOMEFILESYSTEM_H_
