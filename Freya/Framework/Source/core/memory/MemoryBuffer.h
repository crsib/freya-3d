/*
 * MemoryBuffer.h
 *
 *  Created on: 16.03.2009
 *      Author: vedenko
 */

#ifndef MEMORYBUFFER_H_
#define MEMORYBUFFER_H_
#include <cstdlib>
/*
 *
 */
namespace core
{
namespace memory
{
namespace __internal
{
class MemoryPool;
class MemoryHeaderList;
class __UpdatePools;
class MemoryBuffer
{
	friend class MemoryPool;
	friend class __UpdatePools;
private:
	MemoryBuffer(size_t size,size_t alligment);
	virtual ~MemoryBuffer();

	void *		allocate(size_t size);
	bool		dispose (void* p);
	//Data
	MemoryHeaderList*	m_List;
	void*				m_Memory;
	size_t				m_Alligment;
	size_t				m_Size;
};
}
}
}
#endif /* MEMORYBUFFER_H_ */
