/* File		: containers/vector.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef vector_h__
#define vector_h__

#include "containers/policies/Policies.h"

namespace containers
{
	template
	<
		typename T,
		template<class> class MemoryAllocationPolicy = policies::memory::FreyaAllocator,
		class LockPolicy = policies::multithreading::NoLock,
		class StorageResizePolicy = policies::storage::Exponential
	>
	class vector : private MemoryAllocationPolicy<T>, private LockPolicy, private StorageResizePolicy
	{
	public:
		//! Destroy a vector
		~vector();
		//! Constructs an empty vector
		vector() : m_AllocatedCount(0),  m_Begin(NULL), m_End(NULL) {}
		//! Construct an empty vector with reserved storage
		vector(size_t reserve_count) : m_AllocatedCount(reserve_count), m_Begin(allocate(reserve_count)), m_End(m_Begin) {}

	private:
		size_t	m_AllocatedCount;
		T*	   m_Begin;
		T*	   m_End;
	};
}

#ifndef vector_impl_h__
#include "containers/details/vector_impl.h"
#endif

#endif // vector_h__