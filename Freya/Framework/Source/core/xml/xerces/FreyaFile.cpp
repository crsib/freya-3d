#include "core/xml/xerces/FreyaFile.h"
#include "core/EngineCore.h"
#include "core/xml/XMLParserException.h"

#include "core/filesystem/Filesystem.h"

#include <iostream>
namespace core
{
namespace xml
{
namespace xerces
{
//============================== Default constructor==============================

FreyaFile::FreyaFile()
{
	//TODO: Constructor stub
}

//==============================~Default constructor==============================

//============================== Method: open==============================

/*********************************************************************
/* Opens file from freya fs and reads it to memory
*********************************************************************/

void		FreyaFile::open(const EString& path, bool toWrite)
{
	m_ForWrite = toWrite;
	m_Path = path;
	m_Pos = 0;
	if(toWrite)
	{
		m_Size = 0;
		m_Buffer = core::memory::Allocate(4096,core::memory::XML_POOL);//Preallocating 4kb
		m_Allocated = 4096;
	}
	else
	{
		m_Size = core::EngineCore::getFilesystem()->fileSize(m_Path);
		m_Buffer = core::EngineCore::getFilesystem()->read(m_Path);
	}
}

//==============================~Method: open==============================

//============================== Method: close==============================

/**********************************************************************
/* Frees memory allocated for file
**********************************************************************/

void		FreyaFile::close()
{
	if(m_ForWrite)
	{
		core::EngineCore::getFilesystem()->write(m_Path,m_Buffer,m_Size);
	}
	core::memory::Free(m_Buffer,core::memory::XML_POOL);
}

//==============================~Method: close==============================

//============================== Method: read==============================

size_t		FreyaFile::read(size_t count, void* buf)
{
	if(buf)
	{
		if((m_Pos + count) > m_Size)
		{
			count = m_Size - m_Pos;
		}
		::memcpy(buf, reinterpret_cast<char*>(m_Buffer)+m_Pos,count);
		m_Pos+=count;
		return count;
	}

	return 0;
}

//==============================~Method: read==============================

//============================== Method: write==============================

void		FreyaFile::write(size_t count, const void* p )
{
	if(!m_ForWrite) throw core::xml::XMLParserException("XML error: file was opened as read only");
	if((m_Pos + count) > m_Allocated)
	{
		size_t pa = ((count >> 12) + 1) << 12;
		void* tmp = m_Buffer = core::memory::Allocate(m_Allocated + pa,core::memory::XML_POOL);
		::memcpy(tmp,m_Buffer,m_Allocated);
		core::memory::Free(m_Buffer,core::memory::XML_POOL);
		m_Buffer = tmp;
		m_Allocated += pa;
	}
	::memcpy(reinterpret_cast<char*>(m_Buffer)+m_Pos,p,count);
	m_Pos += count;
	m_Size += count;
}

//==============================~Method: write==============================

//============================== Method: pos==============================

size_t		FreyaFile::pos()
{
	return m_Pos;
}

//==============================~Method: pos==============================

//============================== Method: size==============================

size_t		FreyaFile::size()
{
	return m_Size;
}

//==============================~Method: size==============================

//============================== Method: reset==============================

void		FreyaFile::reset()
{
	m_Pos = 0;
}

//==============================~Method: reset==============================

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace

