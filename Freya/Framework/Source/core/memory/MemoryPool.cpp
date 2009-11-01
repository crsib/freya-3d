/*
 * MemoryPool.cpp
 *
 *  Created on: 24.03.2009
 *      Author: vedenko
 */

#include "core/memory/MemoryPool.h"
#include "core/memory/MemoryBuffer.h"
#include "core/memory/MemoryException.h"
#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"
#include "core/EngineCore.h"
#include "core/multithreading/ThreadBlocks.h"
#include "core/multithreading/ThreadID.h"
#include "windowmanager/WindowManagerDriver.h"

//TODO: DBG
#include <iostream>
namespace core
{

namespace memory
{

namespace __internal
{

//================ Task class ======================================
class __Result : virtual public ::EngineSubsystem
{
private:
	void* operator new(size_t sz){throw 0;}
	void* operator new[](size_t sz){throw 0;}
	void  operator delete[](void* p){}
public:
	__Result() : Buffer(NULL), Ready(0)
	{
	}
	~__Result()
	{
	}
	MemoryBuffer* Buffer;
	unsigned	  Ready;

	void* operator new(size_t sz, void* p)
	{
		return p;
	}
	void operator delete(void* p)
	{

	}
};

class __UpdatePools : public core::taskmanager::Task
{
private:
	void* operator new(size_t sz){throw 0;}
	void* operator new[](size_t sz){throw 0;}
	void  operator delete[](void* p){}
public:

	void* operator new(size_t sz, void* p)
	{
		return p;
	}
	void operator delete(void* p)
	{

	}

	__UpdatePools()
	{
		Result = new(reinterpret_cast<char*>(this) + sizeof(__UpdatePools)) __Result;
		Result->Ready = 0;
		std::cout << "Task created" << std::endl;
	}
	~__UpdatePools()
	{
		std::cout << "Task done" << std::endl;
		Result->Ready = 1;
	}
	virtual int operator() ()
	{
		std::cout << "Executing task" << std::endl;
		Result->Buffer = new MemoryBuffer(Size,Alligment);
		return core::taskmanager::Task::DONE;
	}
	__Result*			Result;
	size_t				Size;
	size_t				Alligment;
};
//==================================================================

MemoryPool::MemoryPool(size_t alloc_size,size_t alligment)
{
	m_First = new MemoryPool::MemoryBufferListItem;
	try
	{
		m_First->This = new MemoryBuffer(alloc_size,alligment);
	}
	catch(...)
	{
		throw;
	}
	m_AllocSize = alloc_size;
	m_Alligment = alligment;
	m_Last = m_First;
	m_TaskControl = reinterpret_cast<void*>(new char[sizeof(__UpdatePools)+sizeof(__Result)]);
	m_Blocked = 0;
}

MemoryPool::~MemoryPool()
{
	delete m_First;
	delete reinterpret_cast<char*>(m_TaskControl);
}

void* 	MemoryPool::allocate(size_t sz)
{
	MemoryPool::MemoryBufferListItem* _start = m_First;
	void* p;
	while((_start != NULL))
	{
		assert(_start);
		while(_start->This == NULL)//It seems that memory is allocated by another thread
			core::multithreading::pause();
		if((p = _start->This->allocate(sz)) == NULL)
			_start = _start->Next;
		else
			break;
	}
	if(_start != NULL)
		return p;
	else //We need to allocate an additional buffer
	{
		try
		{
			m_Last->Next = new MemoryPool::MemoryBufferListItem;

#ifdef _FREYA_DEBUG_MEMORY
			//	std::cout  << "[Memory]: pre-Allocating memory: inside" << std::endl;
#endif

			m_Last->Next->This = new MemoryBuffer((sz < m_AllocSize) ?  m_AllocSize : sz,m_Alligment);
			assert(m_Last->Next->This);
			m_Last = m_Last->Next;
			m_Last->Next = NULL;
			if((p = m_Last->This->allocate(sz)) != NULL)
				return p;
			else
			{
				std::cout << "[MemoryPool]: allocation failed" << std::endl;
				throw core::memory::MemoryException("[MemoryPool]: allocation failed");
			}
		}
		catch(...)
		{
			throw;
		}
	}
}

void	MemoryPool::free(void* p)
{
	MemoryPool::MemoryBufferListItem* _start = m_First;
	while((_start)&&(_start->This->dispose(p) == false))
		_start = _start->Next;
	if(_start == NULL)
	{
		std::cout << "[MemoryPool]: deallocation failed std" << std::endl;
		throw core::memory::MemoryException("[MemoryPool]: failed to deallocate memory");
	}
}

}

}

}
