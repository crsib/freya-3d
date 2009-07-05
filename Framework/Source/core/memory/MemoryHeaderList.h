/*
 * MemoryHeaderList.h
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYHEADERLIST_H_
#define MEMORYHEADERLIST_H_

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
class MemoryHeader;
class MemoryHeaderList
{
	friend class MemoryBuffer;
private:
	MemoryHeaderList()
	{}
	virtual ~MemoryHeaderList()
	{}
	//Interface
	//Alligment value corresponds to the power of two value, in bytes
    void* 		allocate(size_t size,size_t alligment);
    bool		dispose(void* p);

    //Internal
    MemoryHeader*		__findBySize(size_t desired);

    MemoryHeader*		__findByPointer(void* p);

    MemoryHeader*		__insert(MemoryHeader*	header); //Inserts in the list of FREE blocks

    void					__remove(MemoryHeader*  header); //Remove from free blocks list

	void* operator new(size_t size,void* p) //Allocate memory in place
	{
		return p;
	}

//Data
	MemoryHeader*	m_First;
	MemoryHeader*	m_Last;

};

}
}
}
#endif /* MEMORYHEADERLIST_H_ */
