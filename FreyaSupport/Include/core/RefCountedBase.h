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
#include "integer.h"
#include "core/smart_ptr.h"

namespace core
{
	//! This class is a default base to be used by ref counted objects
	/*!
	 * This class follows the interface, required by core::policies::ownership::Intrusive and implements base
	 * features, required by classes with intrusive reference counting.
	 * This class uses atomic operations to ensure, that the counter has the same value across the all threads.
	 * Still, release() method is probably not completely threadsafe
	 * \sa core::policies::ownership::Intrusive, core::policies::ownership::RefCounted
	 */
	class FREYA_SUPPORT_EXPORT RefCountedBase
	{
	public:
		//! Virtual destructor to ensure, that inherited class is correctly deleted 
		virtual ~RefCountedBase() {}
		//! Default constructor
		RefCountedBase() : m_RefCount(1) {}
		//! Type of the reference counter
		typedef atomic::atomic<uint32_t> counter_type_t;
		//! Increase ownership level
		void	retain() { ++m_RefCount; }
		//! Decrease ownership level and destroy the object if needed
		void	release() 
		{
			if(!--m_RefCount)
				delete this;
		}
		//! Retrieve the current ownership level
		const counter_type_t&	getRetainCount() const { return m_RefCount; }

	private:
		counter_type_t                 m_RefCount;

		RefCountedBase(const RefCountedBase& );
		RefCountedBase& operator = (const RefCountedBase& );
	};
}

#endif // RefCounted_h__