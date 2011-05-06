/* File		: core/policies/ownership/RefCounted.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef SmartPtr_RefCounted_h__
#define SmartPtr_RefCounted_h__

#include "core/memory/MemoryArena.h"
#include "atomic/atomic.h"
#include "FreyaSupportInternal.h"

namespace core
{
	namespace policies
	{
		namespace ownership
		{
			//! Policy, implementing non intrusive reference counted owner ship
			/*!
			 * This policy implements non intrusive reference counting. 
			 * This policy is thread safe in the sense, that the value of the counter 
			 * will always be the same accross all threads. Still, release method is not 
			 * completely thread safe
			 * \ingroup SmartPointers_Policies_Ownership
			 */
			template<class P>
			class RefCounted
			{
				template<class U>
				friend class RefCounted;

			public:
				//! Default constructor
				/*!
				 * Create a reference counter in core::memory::STL_POOL and initialize it to 1
				 */
				RefCounted() : m_RefCount( new( core::memory::alloc(sizeof(atomic::atomic<uint32_t>),core::memory::STL_POOL)) atomic::atomic<uint32_t> ) 
				{ *m_RefCount = 1; }
				//! Copy constructor
				RefCounted(const RefCounted& rhs) : m_RefCount(rhs.m_RefCount) {}
				//! Copy constructor
				template<class U>
				RefCounted(const RefCounted<U>& rhs) : m_RefCount(rhs.m_RefCount) {}
				//! Swap policies
				void	swap(RefCounted& rhs)
				{
					atomic::atomic<uint32_t>* temp = rhs.m_RefCount;
					rhs.m_RefCount = m_RefCount;
					m_RefCount = temp;
				}

			protected:
				//! Increase ownership level
				P       clone(const P& val)
				{
					++*m_RefCount;
					return val;
				}
				//! Decrease ownership level
				bool    release(const P&)
				{
					if(!--*m_RefCount)
					{
						core::memory::dealloc(m_RefCount, core::memory::STL_POOL);
						m_RefCount = NULL;
						return true;
					}
					return false;
				}
				//! This policy does not follow destructive copy semantics
				enum { DestructiveCopy = false };
			private:
				atomic::atomic<uint32_t>*	m_RefCount;
			};

		}
	}
}

#endif // RefCounted_h__