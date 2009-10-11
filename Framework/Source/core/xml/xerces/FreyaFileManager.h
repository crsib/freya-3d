#ifndef _FREYAFILEMANAGER_H_
#define _FREYAFILEMANAGER_H_

#include <xercesc/util/XMLFileMgr.hpp>
#include <xercesc/Framework/MemoryManager.hpp>
namespace core
{
namespace xml
{
class XMLParser;
namespace xerces
{
using xercesc::MemoryManager;
using xercesc::FileHandle;
class FreyaFileManager : public xercesc::XMLFileMgr
{
	friend class core::xml::XMLParser;
protected:
	FreyaFileManager();
public:
	virtual FileHandle fileOpen(const XMLCh* path, bool toWrite, MemoryManager * const manager);

	virtual FileHandle fileOpen(const char* path, bool toWrite, MemoryManager * const manager);

	virtual FileHandle openStdIn(MemoryManager * const manager);

	virtual void fileClose(FileHandle f, MemoryManager * const manager);

	virtual void fileReset(FileHandle f, MemoryManager * const manager);

	virtual XMLFilePos curPos(FileHandle f, MemoryManager * const manager);

	virtual XMLFilePos fileSize(FileHandle f, MemoryManager * const manager);

	virtual XMLSize_t fileRead(FileHandle f,XMLSize_t byteCount,XMLByte* buffer,MemoryManager * const manager);

	virtual void fileWrite(FileHandle f, XMLSize_t byteCount, const XMLByte* buffer, MemoryManager * const manager);

	virtual XMLCh* getFullPath(const XMLCh* const srcPath,MemoryManager * const manager);

	virtual XMLCh* getCurrentDirectory(MemoryManager * const  manager);

	virtual bool isRelative(const XMLCh* const path, MemoryManager * const manager);


}; //End of FreyaFileManager class

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace
#endif //End of _FREYAFILEMANAGER_H_
