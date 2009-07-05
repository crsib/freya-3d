/*
 * RingBuffer.h
 *
 *  Created on: 02.05.2009
 *      Author: vedenko
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "core/EngineCore.h"

#include "windowmanager/WindowManagerDriver.h"
#include "windowmanager/DriverSubsystems/Multithreading/Mutex.h"
#include "windowmanager/DriverSubsystems/Multithreading/Condition.h"


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
	windowmanager::multithreading::Mutex*		m_Mutex;
	windowmanager::multithreading::Condition* m_NotFull;
	windowmanager::multithreading::Condition* m_NotEmpty;

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
	windowmanager::WindowManagerDriver*	wm = core::EngineCore::getWindowManager();
	m_Mutex = wm->createMutex();
	m_NotFull = wm->createCondidtion();
	m_NotEmpty = wm->createCondidtion();
	m_Count = m_Front = m_Rear = 0;
	//std::cout << "Created a boundede buffer of size: " << sz << " " << (void*)this << " " << (void*)m_Mutex <<std::endl;
}

//===========================================================
template <typename T,size_t sz>
RingBuffer<T,sz>::~RingBuffer()
{
	//std::cout << "Destroyed a boundede buffer of size: " << sz << " " << (void*)this << " " << (void*)m_Mutex <<std::endl;
	windowmanager::WindowManagerDriver*	wm = core::EngineCore::getWindowManager();
	wm->destroyMutex(m_Mutex);
	wm->destroyCondition(m_NotFull);
	wm->destroyCondition(m_NotEmpty);
}

//==========================================================
template <typename T, size_t sz>
T		RingBuffer<T,sz>::fetch()
{
	//std::cout << "fetch a boundede buffer of size: " << sz << " " << (void*)this << " " << (void*)m_Mutex <<std::endl;
	m_Mutex->lock();
	while(m_Count == 0)
	{
		m_NotEmpty->wait(m_Mutex);
	}
	size_t tmp = m_Front;
	m_Front = (++m_Front) % sz;
	--m_Count;
	m_Mutex->unlock();
	m_NotFull->signal();
	return m_Buffer[tmp]; //To activate RVO

}

//==========================================================
template <typename T, size_t sz>
void	RingBuffer<T,sz>::deposit(const T& val)
{
	//std::cout << "Deposit a boundede buffer of size: " << sz << " " << (void*)this << " " << (void*)m_Mutex <<std::endl;
	m_Mutex->lock();
	//std::cout << "Deposit 1 a boundede buffer of size: " << sz << " " << (void*)this << " " << (void*)m_Mutex <<std::endl;
	while(m_Count == sz)
	{
		m_NotFull->wait(m_Mutex);
	}
	m_Buffer[m_Rear] = val;
	m_Rear = (++m_Rear) % sz;
	++m_Count;
	m_Mutex->unlock();
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