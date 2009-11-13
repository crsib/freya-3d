/*
 * MemoryHeader.h
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYHEADER_H_
#define MEMORYHEADER_H_

/*
 *
 */
#include <cstdlib>

namespace core
{
namespace memory
{
namespace __internal
{
class MemoryHeaderList;
class MemoryBuffer;
class MemoryHeader
{
	friend class core::memory::__internal::MemoryHeaderList;
	friend class MemoryBuffer;
private:
	MemoryHeader()
	{
		setHash(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + sizeof(MemoryHeader)));
		m_Magic = 0;
		m_Size = 0;
		m_Next = m_Prev = NULL;
	}

	~MemoryHeader()
	{
		//All memory clearing are done, when the corresponding memory is deallocated
	}

	MemoryHeader& operator = (const MemoryHeader&)
	{
		return *this;
	}

	MemoryHeader(const MemoryHeader&){}
private: //Methods section

	void 	changeState(unsigned short state)
	{
		m_Magic = state;
	}
	//calculates hash for a pointer
	void	setHash(void* p)
	{
		m_PointerHash = static_cast<unsigned short>((reinterpret_cast<unsigned long>(p)*MULTIPLIER+ADDITION) % ((2 << 16) -1));
	}

	bool	check(void* p) //Checks the pointer correctness
	{
		if(m_PointerHash == static_cast<unsigned short>((reinterpret_cast<unsigned long>(p)*MULTIPLIER+ADDITION) % ((2 << 16) -1))
				&& ((m_Magic == FREE)||(m_Magic == ALLOCATED)))
			return true;
		else
			return false;
	}

	MemoryHeader* next()
	{
		return m_Next;
	}

	MemoryHeader* prev()
	{
		return m_Prev;
	}
/*
	size_t size()
	{
		return m_Size;
	}
*/
	void set(unsigned short state, size_t size,MemoryHeader* next,MemoryHeader* prev)
	{
		m_Magic = state;
		m_Size = size;
		m_Next = next;
		m_Prev = prev;
	}

	void* operator new(size_t size,void* p) //Allocate memory in place
	{
		return p;
	}

	void*	pointer()
	{
		return reinterpret_cast<void*>(reinterpret_cast<char*>(this) + sizeof(MemoryHeader));
	}
private:
	//TODO: make this class more portable
	enum
	{
		FREE = 0xAAAA,
		ALLOCATED = 0x0555
	};
	enum
	{
		MULTIPLIER = 999983,
		ADDITION = 99991
	};

	MemoryHeader*		m_Prev;		   //Previous free block (nearest in memory space)
	unsigned short		m_PointerHash; //16 bit hash for basic correctness checking
	unsigned short		m_Magic;       //Some strange values to check whether this header points to a free block
	size_t				m_Size;		   //Size of a block
	MemoryHeader*		m_Next;		   //Next free block (nearest in memory space)
};

}
}
}
#endif /* MEMORYHEADER_H_ */

