/*
 * MemoryBuffer.cpp
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#include "core/memory/MemoryBuffer.h"
#include "core/memory/MemoryException.h"
#include "core/memory/MemoryHeader.h"
#include "core/memory/MemoryHeaderList.h"

#include <cstdlib>


namespace core
{
namespace memory
{
namespace __internal
{
MemoryBuffer::MemoryBuffer(size_t size,size_t alligment)
{
	m_Alligment = alligment;
	//size += sizeof(MemoryHeader) + sizeof(MemoryHeaderList);
	m_Size = ((size >> alligment) << alligment); //This a purely size of buffer
	if(m_Size != size)
		m_Size += (1 << alligment); //Make it alligned
	size_t control_sz = sizeof(MemoryHeader) + sizeof(MemoryHeaderList);
	size_t offset = 0;
	if(control_sz != ((control_sz >> alligment) << alligment))
		offset = (((control_sz >> alligment) << alligment) + (1 << alligment)) - control_sz;
	m_Size += control_sz + offset;
	//Now, allocate memory block
	m_Memory = NULL;

	try
	{
		m_Memory = new char[m_Size];
	}
	catch(...)
	{
		throw core::memory::MemoryException("[MemoryBuffer]: memory allocation failed");
	}
	//Now create a header list
	//reinterpret_cast<char*>(m_Memory)

	m_List = new(reinterpret_cast<char*>(m_Memory) + offset) MemoryHeaderList;

	MemoryHeader* _start =
		m_List->m_First = m_List->m_Last =	new(reinterpret_cast<char*>(m_Memory) + sizeof(MemoryHeaderList) + offset) MemoryHeader;
	_start->m_Magic = MemoryHeader::FREE;
	_start->m_Prev = _start->m_Next = NULL;
	_start->m_Size = m_Size - (reinterpret_cast<char*>(_start->pointer()) - reinterpret_cast<char*>(m_Memory));
	//_start->m_Size

}

MemoryBuffer::~MemoryBuffer()
{
	delete[] reinterpret_cast<char*>(m_Memory);
}

void *		MemoryBuffer::allocate(size_t size)
{
	return m_List->allocate(size,m_Alligment);
}

bool		MemoryBuffer::dispose (void* p)
{
	return m_List->dispose(p);
}

}
}
}
