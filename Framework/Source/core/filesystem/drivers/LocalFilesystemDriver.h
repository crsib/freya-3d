#ifndef _LOCALFILESYSTEMDRIVER_H_
#define _LOCALFILESYSTEMDRIVER_H_

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

#include "core/filesystem/FilesystemDriver.h"
#include <boost/filesystem.hpp>


namespace fs = boost::filesystem;

namespace core
{
namespace filesystem
{
namespace drivers
{
namespace ids
{
class LocalFilesystemDriverID;
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
class LocalFilesystemDriver : public core::filesystem::FilesystemDriver
{
	friend class core::filesystem::drivers::ids::LocalFilesystemDriverID;
	friend class core::filesystem::Filesystem;
protected:
	LocalFilesystemDriver()
	{

	}
	virtual ~LocalFilesystemDriver();

protected:
	virtual void setMountPoint(const EString& path);

public:
	virtual EString id() const;

	virtual bool isWritable();

	virtual EStringList list();

	virtual void makeDir(const EString& path);

	virtual bool dirExists(const EString& path);

	virtual bool fileExists(const EString& path);

	virtual size_t fileSize(const EString& path);

	virtual void* read(const EString& path);

	virtual void* read(const EString& path,size_t* sz);

	virtual void write(const EString& path,const void* buf,size_t sz);

	virtual void remove(const EString& path);
protected:
	fs::path	m_MountPoint;

}; //End of LocalFilesystemDriver class

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
#endif //End of _LOCALFILESYSTEMDRIVER_H_
