/* File		: containers/policies/multithreading/AtomicLock.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_AtomicLock_h__
#define Containers_Policies_AtomicLock_h__

#include "integer.h"
#include "atomic/atomic.h"

namespace containers
{
	namespace policies
	{
		namespace multithreading
		{
			//! Provides a lock, based on an atomic integer
			/*!
			 * Provides a lightweight lock interface. 
			 * The major drawback of this policy is non-zero CPU utilization for the race condition occurs.
			 * Consider using this policy only if you can guarantee, that the lock period is short
			 */
			//! \ingroup grpContainers_Policies_MultiThreading
			class AtomicLock
			{
			public:
				AtomicLock() : m_Lock(0) {}
				void		lock() const throw() 
				{
					while( m_Lock.bit_test_and_set(0)) PAUSE ;
				}

				void		unlock() const throw() 
				{
					m_Lock.bit_test_and_reset(0);
				}
			private:
				mutable atomic::atomic<size_t>	m_Lock;
			};

		}
	}
}

#endif // Containers_Policies_AtomicLock_h__