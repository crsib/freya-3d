/*
 * MemoryHeaderList.cpp
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#include "core/memory/MemoryHeaderList.h"
#include "core/memory/MemoryHeader.h"
#include "core/memory/MemoryException.h"

#include <iostream>



namespace core
{	
namespace memory
{
#ifdef _FREYA_DEBUG_MEMORY
	extern unsigned memory_allocated;
#endif
namespace __internal
{
//Searches a block with exact pointer
MemoryHeader*   MemoryHeaderList::__findByPointer(void* p)
{
	MemoryHeader*  _start = m_First;
	while(_start != NULL)
		if(_start->pointer() != p)
			_start = _start->next();
		else
			return _start;
	return NULL;
}
//Remove the memory block from the free block list.
//Sets the magic to FREE
//List "splicing" is not done.
void MemoryHeaderList::__remove(MemoryHeader*  header)
{
	if(header->prev() )
		header->prev()->m_Next = header->next();
	else
	{
		m_First = header->next();
		if(header->next())
			m_First->m_Prev = NULL;
	}
	if(header->next() )
		header->next()->m_Prev = header->prev();
	else
	{
		m_Last = header->prev();
		if(header->prev())
			m_Last->m_Next = NULL;
	}
	header->m_Magic = MemoryHeader::ALLOCATED;
}

//Inserts a memory block inside the free blocks lists.
//Sets the magic to ALLOCATED
//Linkage of neighbors is done
MemoryHeader*		MemoryHeaderList::__insert(MemoryHeader*	header)
{
	//Ok, we need to keep the list order.
	//And we assume, that the list order is already correct
	//It is easy to find the _prev block
	//We do also assume, that the list is not yet corrupted
	MemoryHeader*	_next;
	MemoryHeader*   _prev = m_Last;

	while(_prev->pointer() >= header->pointer()) //we will iterate until _prev->next() == null or _prev->pointer() < header->pointer()
	{
		_prev = _prev->prev();
		if(_prev == NULL)
			break;
	}

	if(_prev != NULL)
	{
		_next = _prev->next();
		//Ok, first of all, let us check, whether we need to link to our right neighbor
		//*
		if((reinterpret_cast<char*>(_prev->pointer()) + _prev->size() + sizeof(MemoryHeader)) == header->pointer())//Linkage needed
		{
			_prev->m_Size += sizeof(MemoryHeader) + header->size();
			header = _prev;
		}
		else //Simply set our block as next*/
		{
			_prev->m_Next = header;
			header->m_Prev = _prev;
		}
		//And now, check our left neighbor
		//Unlike the right one, it could be null
		if(_next == NULL) // It is likely to happen more often, especially at the beginning
		{
			header->m_Next = NULL;
			m_Last = header;
		}
		else //Well, the less easy case
		{
			//we need to check, whether linkage is needed
			//*
			if((reinterpret_cast<char*>(header->pointer()) + header->size() + sizeof(MemoryHeader)) == _next->pointer())
			{
				header->m_Size += sizeof(MemoryHeader) + _next->size();
				header->m_Next = _next->next();
			}
			else //Trivial case*/
			{
				header->m_Next = _next;
				_next->m_Prev = header;
			}
		}
	}
	else //Insert in first place
	{
		header->m_Prev = NULL;
		header->m_Next = m_First;
		m_First = header;
	}

	header->m_Magic = MemoryHeader::FREE;

	return header;
}
//Searches block of enough size
MemoryHeader*	MemoryHeaderList::__findBySize(size_t desired)
{
	MemoryHeader*  _start = m_First;
	while(_start != NULL)
		if(_start->size() < desired)
			_start = _start->next();
		else
			return _start;
	return NULL;
}

void*	MemoryHeaderList::allocate(size_t size,size_t alligment)
{
	//We believe, that all blocks are already alligned
	MemoryHeader* _block = __findBySize(size);
	if(_block)
	{
		//offset, needed to calculate the least size
		size_t _offset;
		//size
		if(((sizeof(MemoryHeader) >> alligment) << alligment) != sizeof(MemoryHeader))
			_offset = (1 << alligment);
		else
			_offset = 0;
		size_t _desired = (size >> alligment) << alligment;
		if(_desired != size)
			_desired += 1 << alligment;
		_offset += sizeof(MemoryHeader);
		//Now we assume, that because of everything is correct
		if(_block->size() > (_desired + _offset)) //It is probably more logical to use 2*offset. TODO: profile this with different variants
		{
			//Slicing needed
			MemoryHeader* _new = new(reinterpret_cast<char*>(_block->pointer()) + _desired + _offset - sizeof(MemoryHeader)) MemoryHeader;
			_new->m_Size = _block->size() - _desired - _offset;
			_new->m_Prev = _block;
			_new->m_Next = _block->next();
			if(_new->m_Next == NULL)
				m_Last = _new;
			_block->m_Next = _new;
			_block->m_Size = _desired + _offset - 2*sizeof(MemoryHeader);
			__remove(_block);
#ifdef _FREYA_DEBUG_MEMORY
			memory_allocated += _block->size();
#endif
			return _block->pointer();
		}
		else	//Trivial case
		{
			__remove(_block);
#ifdef _FREYA_DEBUG_MEMORY
			memory_allocated += _block->size();
#endif
			return _block->pointer();
		}
	}
	return NULL;
}

bool	MemoryHeaderList::dispose(void* p)
{
	if(p != NULL)
	{
		MemoryHeader* _b = (reinterpret_cast<MemoryHeader*>(p) - 1);
		if(_b->check(p)&&(_b->m_Magic == MemoryHeader::ALLOCATED))
		{
#ifdef _FREYA_DEBUG_MEMORY
			memory_allocated -= _b->size();
#endif
			__insert(_b);
			return true;
		}
		else return false;
	}
	return true;
}

}
}
}
