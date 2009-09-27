/*
 * RingBuffer.h
 *
 *  Created on: 02.05.2009
 *      Author: vedenko
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "core/EngineCore.h"

#include "core/multithreading/Mutex.h"
#include "core/multithreading/Condition.h"
#include "core/multithreading/Lock.h"
#include "core/multithreading/ThreadBlocks.h"

namespace core
{
//! This namespace contains various abstractions, useful for multi-threaded programming and threads synchronization
namespace multithreading
{
//! This class is an abstraction of the ring buffer synchronization concept.
/*!
 * This class provides an abstract interface to the ring buffer synchronization primitive
 * \tparam T is a type of an object to be queued.
 * \tparam sz is a size of a buffer
 */
template <typename T,size_t sz>
class RingBuffer : virtual public ::EngineSubsystem
{
public:
	RingBuffer();
	virtual ~RingBuffer();

	//! Retrieve a value from the buffer
	/*!
	 * Retrieves the next queued value from the buffer, if any available. Otherwise, awaits
	 * until the buffer is filled at least with one element
	 * \return next queued value.
	 */
	T		fetch();
	//! Add an element to the buffer
	/*!
	 * Adds an element to the buffer, if there is any free space left. Otherwise, awaits until the buffer
	 * will contain enough space
	 */
	void	deposit(const T& data);
	//! Retrieve the state of buffer
	/*!
	 * Checks the buffer state
	 * \return true if buffer is empty, false otherwise
	 */
	bool	empty();
	//! Retrieve the state of buffer
	/*!
	 * Checks the buffer state
	 * \return true if buffer is full, false otherwise
	 */
	bool	full();
	//! Retrieve the current buffers size
	/*!
	 * Retrieves the current size of buffer
	 * \return size of buffer
	 */
	size_t	count();
	//==========================================================
	//==== Private sections ====================================
	//==========================================================
private:
	core::multithreading::Mutex*					m_Mutex;
	core::multithreading::Condition* 				m_NotFull;
	core::multithreading::Condition* 				m_NotEmpty;

	size_t											m_Front;
	size_t											m_Rear;
	size_t											m_Count;

	T												m_Buffer[sz];
};

//
//=== Implementation ========================================

//===========================================================
template <typename T,size_t sz>
RingBuffer<T,sz>::RingBuffer()
{
	m_NotFull = core::EngineCore::createCondition();
	m_NotEmpty = core::EngineCore::createCondition();
	m_Mutex = core::EngineCore::createMutex();
	m_Count = m_Front = m_Rear = 0;
}

//===========================================================
template <typename T,size_t sz>
RingBuffer<T,sz>::~RingBuffer()
{
	core::EngineCore::destroyCondition(m_NotFull);
	core::EngineCore::destroyCondition(m_NotEmpty);
	m_Mutex->lock();
	m_Mutex->unlock();
	core::EngineCore::destroyMutex(m_Mutex);

}

//==========================================================
template <typename T, size_t sz>
T		RingBuffer<T,sz>::fetch()
{
	size_t tmp;
	synchronize(m_Mutex)
	{
		while(m_Count == 0)
		{
			m_NotEmpty->wait(m_Mutex);
			//core::multithreading::yield();
		}
		tmp = m_Front;
		m_Front = (++m_Front) % sz;
		--m_Count;
	}

	m_NotFull->signal();
	return m_Buffer[tmp]; //To activate RVO
}

//==========================================================
template <typename T, size_t sz>
void	RingBuffer<T,sz>::deposit(const T& val)
{
	synchronize(m_Mutex)
	{
		while(m_Count == sz)
		{
			m_NotFull->wait(m_Mutex);
		}
		m_Buffer[m_Rear] = val;
		m_Rear = (++m_Rear) % sz;
		++m_Count;
	}
	m_NotEmpty->signal();
}

//==========================================================
template <typename T, size_t sz>
bool	RingBuffer<T,sz>::empty()
{
	return (m_Count == 0);
}

//==========================================================
template <typename T, size_t sz>
bool	RingBuffer<T,sz>::full()
{
	return (m_Count == sz);
}

//==========================================================
template <typename T, size_t sz>
size_t	RingBuffer<T,sz>::count()
{
	return m_Count;
}

}
}

#endif /* RINGBUFFER_H_ */
