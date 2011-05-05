/* File		: core/RefCounted.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Core_RefCountedBase_h__
#define Core_RefCountedBase_h__

#include "atomic/atomic.h"
#include "core/Object.h"
#include "FreyaSupportInternal.h"

namespace core
{
	class FREYA_SUPPORT_EXPORT RefCountedBase : virtual public Object
	{
	public:
		virtual ~RefCountedBase() {}
		RefCountedBase() : m_RefCount(1) {}
		
		typedef atomic::atomic<uint32_t> counter_type_t;

		void	retain() { ++m_RefCount; }
		void	release() 
		{
			if(!--m_RefCount)
				delete this;
		}

		const counter_type_t&	getRetainCount() const { return m_RefCount; }

	private:
		counter_type_t                 m_RefCount;

		RefCountedBase(const RefCounted& ) {}
		RefCountedBase& operator = (const RefCounted& ) {}
	};
}

#endif // RefCounted_h__