#include "core/xml/xerces/FreyaFileManager.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/RuntimeException.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PanicHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "core/xml/xerces/FreyaFile.h"
#include "core/xml/XMLParserException.h"

#include "core/EngineCore.h"

namespace core
{
namespace xml
{
namespace xerces
{
//============================== Default constructor==============================

FreyaFileManager::FreyaFileManager()
{
	//TODO: Constructor stub
}

//==============================~Default constructor==============================


//============================== Method: fileOpen==============================

FileHandle		FreyaFileManager::fileOpen(const XMLCh* path, bool toWrite, MemoryManager * const manager)
{

	const char* tmpFileName = xercesc::XMLString::transcode(path, manager);
	xercesc::ArrayJanitor<char> janText((char*)tmpFileName, manager);
	return fileOpen(tmpFileName, toWrite, manager);
}

//==============================~Method: fileOpen==============================

//============================== Method: fileOpen==============================

FileHandle		FreyaFileManager::fileOpen(const char* path, bool toWrite, MemoryManager * const manager)
{
	FreyaFile* file = new FreyaFile;
	file->open(path,toWrite);
	return reinterpret_cast<void*> (file);
}

//==============================~Method: fileOpen==============================

//============================== Method: openStdIn==============================

FileHandle		FreyaFileManager::openStdIn(MemoryManager * const manager)
{
	throw core::xml::XMLParserException("XML error: no stdin");
	return 0;
}

//==============================~Method: openStdIn==============================

//============================== Method: fileClose==============================

void		FreyaFileManager::fileClose(FileHandle f, MemoryManager * const manager)
{
	reinterpret_cast<FreyaFile*>(f)->close();
	delete reinterpret_cast<FreyaFile*>(f);
}

//==============================~Method: fileClose==============================

//============================== Method: fileReset==============================

void		FreyaFileManager::fileReset(FileHandle f, MemoryManager * const manager)
{
	reinterpret_cast<FreyaFile*>(f)->reset();
}

//==============================~Method: fileReset==============================

//============================== Method: curPos==============================

XMLFilePos		FreyaFileManager::curPos(FileHandle f, MemoryManager * const manager)
{
	return reinterpret_cast<FreyaFile*>(f)->pos();
}

//==============================~Method: curPos==============================

//============================== Method: fileSize==============================

XMLFilePos		FreyaFileManager::fileSize(FileHandle f, MemoryManager * const manager)
{
	return reinterpret_cast<FreyaFile*>(f)->size();
}

//==============================~Method: fileSize==============================

//============================== Method: fileRead==============================

XMLSize_t		FreyaFileManager::fileRead(FileHandle f,XMLSize_t byteCount,XMLByte* buffer,MemoryManager * const manager)
{
	return reinterpret_cast<FreyaFile*>(f)->read(byteCount,buffer);
}

//==============================~Method: fileRead==============================

//============================== Method: fileWrite==============================

void		FreyaFileManager::fileWrite(FileHandle f, XMLSize_t byteCount, const XMLByte* buffer, MemoryManager * const manager)
{
	reinterpret_cast<FreyaFile*>(f)->write(byteCount,buffer);
}

//==============================~Method: fileWrite==============================

//============================== Method: getFullPath==============================

XMLCh*		FreyaFileManager::getFullPath(const XMLCh* const path,MemoryManager * const manager)
{
	char* newSrc = xercesc::XMLString::transcode(path, manager);
	xercesc::ArrayJanitor<char> janText(newSrc, manager);
	size_t l = ::strlen(newSrc);
	char* buf = reinterpret_cast<char*>(core::memory::Allocate(l,core::memory::XML_POOL));
	::memcpy(buf,newSrc,l);
	return xercesc::XMLString::transcode(buf,manager);
}

//==============================~Method: getFullPath==============================

//============================== Method: getCurrentDirectory==============================

XMLCh*		FreyaFileManager::getCurrentDirectory(MemoryManager * const manager)
{
	return xercesc::XMLString::transcode("/", manager);
}

//==============================~Method: getCurrentDirectory==============================

//============================== Method: isRelative==============================

bool		FreyaFileManager::isRelative(const XMLCh* const path, MemoryManager * const manager)
{
	return false;
}

//==============================~Method: isRelative==============================

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace

