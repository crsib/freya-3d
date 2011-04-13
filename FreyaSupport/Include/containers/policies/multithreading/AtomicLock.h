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

			class AtomicLock
			{
			public:
				AtomicLock() : m_Lock(0) {}
				void		lock() const throw() 
				{
					while( m_Lock.bit_test_and_set(0)) ;
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