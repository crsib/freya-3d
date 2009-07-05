#include "core/filesystem/drivers/LzmaDriver.h"
#include "core/filesystem/FilesystemException.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

namespace core
{
namespace filesystem
{
namespace drivers
{

namespace __lzma_local
{
#ifdef _LZMA_IN_CB

#define kBufferSize (1 << 12)
Byte g_Buffer[kBufferSize];

SZ_RESULT SzFileReadImp(void *object, void **buffer, size_t maxRequiredSize, size_t *processedSize)
{
	CFileInStream *s = (CFileInStream *)object;
	size_t processedSizeLoc;
	if (maxRequiredSize > kBufferSize)
		maxRequiredSize = kBufferSize;
	processedSizeLoc = fread(g_Buffer, 1, maxRequiredSize, s->File);
	*buffer = g_Buffer;
	if (processedSize != 0)
		*processedSize = processedSizeLoc;
	return SZ_OK;
}

#else

SZ_RESULT SzFileReadImp(void *object, void *buffer, size_t size, size_t *processedSize)
{
	LzmaDriver::CFileInStream *s = static_cast<LzmaDriver::CFileInStream *>(object);
	size_t processedSizeLoc = fread(buffer, 1, size, s->File);
	if (processedSize != 0)
		*processedSize = processedSizeLoc;
	return SZ_OK;
}

#endif

SZ_RESULT SzFileSeekImp(void *object, CFileSize pos)
{
	LzmaDriver::CFileInStream *s = static_cast<LzmaDriver::CFileInStream *>(object);
	int res = fseek(s->File, (long)pos, SEEK_SET);
	if (res == 0)
		return SZ_OK;
	return SZE_FAIL;
}

}//namespace __lzma_local
using namespace __lzma_local;
//============================== Derived constructors==============================
LzmaDriver::LzmaDriver() : m_Ready(0)
{
	InitCrcTable();
}
//==============================~Derived constructors==============================

//============================== Destructor==============================

LzmaDriver::~LzmaDriver()
{
	if(m_Ready)
	{
		fclose(m_ArchiveStream.File);
	}
}

//==============================~Destructor==============================

//============================== Method: setMountPoint==============================

inline void*	_LZMA_Alloc(size_t sz)
{
	return core::memory::Allocate(sz,2);
}

inline void		_LZMA_Free(void* p)
{
	core::memory::Free(p,2);
}

void		LzmaDriver::setMountPoint(const EString& path)
{
	m_ArchiveStream.File = fopen(path.c_str(),"rb");
	if(m_ArchiveStream.File == NULL)
	{
		throw core::filesystem::FilesystemException(EString("Failed to start lzma driver: file " +path + " not found"));
	}
	SzArDbExInit(&m_Db);
	m_ArchiveStream.InStream.Read = SzFileReadImp;
	m_ArchiveStream.InStream.Seek = SzFileSeekImp;

	ISzAlloc Alloc;
	Alloc.Alloc = _LZMA_Alloc;
	Alloc.Free  = _LZMA_Free;

	if(SzArchiveOpen(&m_ArchiveStream.InStream, &m_Db, &Alloc, &Alloc) != SZ_OK)
	{
		throw core::filesystem::FilesystemException(EString("Failed to start lzma driver: file " +path + " is not a valid lzma archive"));
	}

	CFileItem *FileItem;
	for (unsigned int i = 0; i < m_Db.Database.NumFiles; i++)
	{
		FileItem = m_Db.Database.Files + i;
		if(!FileItem->IsDirectory)
		{
			LZMAPair filed;
			filed.FileName = "/";
			filed.FileName += FileItem->Name;
			filed.Index = i;
			m_FileList.push_back(filed);
		}
	}
	m_Ready = 1;
}

//==============================~Method: setMountPoint==============================

//============================== Method: id==============================

EString		LzmaDriver::id() const
{
	return EString("lzma");
}

//==============================~Method: id==============================

//============================== Method: isWritable==============================

bool		LzmaDriver::isWritable()
{
	return false;
}

//==============================~Method: isWritable==============================

//============================== Method: list==============================

EStringList		LzmaDriver::list()
{
	if(m_Ready == 0) return EStringList();
	EStringList lst;
	for(unsigned i = 0;i < m_FileList.size();i++)
		lst.push_back(m_FileList[i].FileName);
	return lst;
}

//==============================~Method: list==============================

//============================== Method: makeDir==============================

void		LzmaDriver::makeDir(const EString& path)
{
	throw core::filesystem::FilesystemException("Attempt to modify read only part of filesystem");
}

//==============================~Method: makeDir==============================

//============================== Method: dirExists==============================

bool		LzmaDriver::dirExists(const EString& path)
{
	if(m_Ready == 0) return false;
	for(unsigned i = 0;i < m_FileList.size();i++)
		if(m_FileList[i].FileName == path)
			return true;
	return false;
}

//==============================~Method: dirExists==============================

//============================== Method: fileExists==============================

bool		LzmaDriver::fileExists(const EString& path)
{

	if(m_Ready == 0) return false;
	for(unsigned i = 0;i < m_FileList.size();i++)
	{
		if(m_FileList[i].FileName == path)
			return true;
	}
	return false;
}

//==============================~Method: fileExists==============================

//============================== Method: fileSize==============================

size_t		LzmaDriver::fileSize(const EString& path)
{
	if(m_Ready == 0)
		throw core::filesystem::FilesystemException("Lzma driver is not mounted");
	unsigned fileIndex = (unsigned)-1;
	for(unsigned i = 0;i < m_FileList.size();i++)
		if(m_FileList[i].FileName == path)
		{
			fileIndex = i;
			break;
		}
	if(fileIndex == (unsigned)-1)
		throw core::filesystem::FilesystemException(EString("File ") + path + " is not found");
	CFileItem* fileItem = m_Db.Database.Files + fileIndex;
	return fileItem->Size;
}

//==============================~Method: fileSize==============================

//============================== Method: read==============================

void*		LzmaDriver::read(const EString& path)
{
	if(m_Ready == 0)
		throw core::filesystem::FilesystemException("Lzma driver is not mounted");
	unsigned fileIndex = (unsigned)-1;
	for(unsigned i = 0;i < m_FileList.size();i++)
		if(m_FileList[i].FileName == path)
		{
			fileIndex = i;
			break;
		}
	if(fileIndex == (unsigned)-1)
		throw core::filesystem::FilesystemException(EString("File ") + path + " is not found");

	size_t 		offset;
	size_t 		outSizeProcessed;
	Byte*		outBuffer = NULL;
	size_t		outBufferSize;
	SZ_RESULT	res;
	ISzAlloc Alloc;
	Alloc.Alloc = _LZMA_Alloc;
	Alloc.Free  = _LZMA_Free;
	res = SzExtract(&m_ArchiveStream.InStream,&m_Db,fileIndex,&m_BlockIndex,
			&outBuffer,&outBufferSize,&offset,&outSizeProcessed,&Alloc,&Alloc);
	if(res != SZ_OK)
	{
		std::clog << "Internal LZMA driver error: failed to extract file" << std::endl;
		return NULL;
	}
	void* mem = _LZMA_Alloc(outSizeProcessed);
	if(mem == NULL)
	{
		std::clog << "Internal LZMA driver error: memory allocation error" << std::endl;
		return NULL;
	}
	memcpy(mem,(void*)(outBuffer + offset),outSizeProcessed);
	_LZMA_Free(outBuffer);
	return mem;
}

//==============================~Method: read==============================

//============================== Method: read==============================

void*		LzmaDriver::read(const EString& path,size_t* sz)
{
	*sz = fileSize(path);
	return read(path);
}

//==============================~Method: read==============================

//============================== Method: write==============================

void		LzmaDriver::write(const EString& path,const void* buf,size_t sz)
{
	throw core::filesystem::FilesystemException("Attempt to modify read only part of filesystem");
}

//==============================~Method: write==============================

//============================== Method: remove==============================

void		LzmaDriver::remove(const EString& path)
{
	throw core::filesystem::FilesystemException("Attempt to modify read only part of filesystem");
}

//==============================~Method: remove==============================

} //End of drivers namespace
} //End of filesystem namespace
} //End of core namespace
