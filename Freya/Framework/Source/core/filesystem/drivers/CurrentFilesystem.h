#ifndef _CURRENTFILESYSTEM_H_
#define _CURRENTFILESYSTEM_H_

#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif

#include "core/filesystem/drivers/LocalFilesystemDriver.h"

namespace core
{
namespace filesystem
{
namespace drivers
{
namespace ids
{
class CurrentFilesystemDriverID;
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

class CurrentFilesystem : public core::filesystem::drivers::LocalFilesystemDriver
{
	friend class core::filesystem::drivers::ids::CurrentFilesystemDriverID;
	friend class core::filesystem::Filesystem;
	CurrentFilesystem()
	{

	}
	virtual ~CurrentFilesystem();
protected:
	virtual void setMountPoint(const EString& path);

public:
	virtual EString id() const;

}; //End of AppHomeFilesystem class

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
#endif //End of _APPHOMEFILESYSTEM_H_
