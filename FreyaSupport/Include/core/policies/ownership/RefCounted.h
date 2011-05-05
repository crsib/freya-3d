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
			//! Policy, defining non intrusive reference counted ownnership
			template<class P>
			class RefCounted
			{
				template<class U>
				friend class RefCounted;

			public:
				RefCounted() : m_RefCount( new( core::memory::alloc(sizeof(atomic::atomic<uint32_t>),core::memory::STL_POOL)) atomic::atomic<uint32_t> ) 
				{ *m_RefCount = 1; }
				RefCounted(const RefCounted& rhs) : m_RefCount(rhs.m_RefCount) {}
				template<class U>
				RefCounted(const RefCounted<U>& rhs) : m_RefCount(rhs.m_RefCount) {}

				void	swap(RefCounted& rhs)
				{
					atomic::atomic<uint32_t>* temp = rhs.m_RefCount;
					rhs.m_RefCount = m_RefCount;
					m_RefCount = temp;
				}

			protected:

				P       clone(const P& val)
				{
					++*m_RefCount;
					return val;
				}

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
				
				enum { DestructiveCopy = false };
			private:
				atomic::atomic<uint32_t>*	m_RefCount;
			};

		}
	}
}

#endif // RefCounted_h__