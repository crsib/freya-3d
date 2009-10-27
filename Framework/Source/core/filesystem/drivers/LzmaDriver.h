#ifndef _LZMADRIVER_H_
#define _LZMADRIVER_H_

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

#include "core/EString.h"
#include "core/EStringList.h"
#include <vector>
#include "core/memory/MemoryAllocator.h"

#include "core/filesystem/drivers/3party/7zip/7zCrc.h"
#include "core/filesystem/drivers/3party/7zip/7zIn.h"
#include "core/filesystem/drivers/3party/7zip/7zExtract.h"

#include "core/multithreading/Mutex.h"
#include "core/multithreading/Lock.h"

namespace core
{
namespace filesystem
{
namespace drivers
{
namespace ids
{
class LzmaFilesystemDriverID;
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

class LzmaDriver : public core::filesystem::FilesystemDriver
{
	friend class core::filesystem::drivers::ids::LzmaFilesystemDriverID;
	friend class core::filesystem::Filesystem;
	LzmaDriver();
	virtual ~LzmaDriver();

protected:
	virtual void setMountPoint(const EString& path);

public:
	typedef struct _CFileInStream
	{
		ISzInStream InStream;
		FILE *File;
	} CFileInStream;
	typedef struct _LZMAPair
	{
		EString 	FileName;
		unsigned 	Index;

		_LZMAPair& operator = (const _LZMAPair& op)
		{
			FileName = op.FileName;
			Index = op.Index;
			return (*this);
		}
	} LZMAPair;
	typedef std::vector<LZMAPair, core::memory::MemoryAllocator<LZMAPair> > FileList;
	typedef std::vector<LZMAPair, core::memory::MemoryAllocator<LZMAPair> >::iterator FileListIterator;


	virtual EString id() const ;

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

private:
	FileList						m_FileList;
	CFileInStream 					m_ArchiveStream;
	CArchiveDatabaseEx 				m_Db;
	UInt32 							m_BlockIndex;
	unsigned						m_Ready;
	core::multithreading::Mutex*	m_Mutex;

}; //End of LzmaDriver class

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
#endif //End of _LZMADRIVER_H_
