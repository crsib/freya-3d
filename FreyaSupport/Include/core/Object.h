/* File		: core/Object.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Object_h__
#define Object_h__

#include "FreyaSupportInternal.h"

#include "core/memory/MemoryPools.h"

namespace core
{
	namespace memory
	{
		FREYA_SUPPORT_EXPORT void*	alloc(size_t size, unsigned pool = core::memory::GENERIC_POOL) throw();
		FREYA_SUPPORT_EXPORT void	dealloc(void* p, unsigned pool = core::memory::GENERIC_POOL) throw();
	} // namespace memory
} // namespace core

namespace core
{
	//! This class is a base class for all Freya 3D Engine classes, that should be allocated in the CLASS_POOL
	class Object
	{
	public:
		virtual ~Object() {}
	
		static void* operator new(size_t sz) { return memory::alloc(sz,memory::CLASS_POOL); }
		static void* operator new [] (size_t sz) { return memory::alloc(sz,memory::CLASS_POOL); }

		static void	 operator delete(void* p) { memory::dealloc(p, memory::CLASS_POOL); }
		static void  operator delete[] (void* p) { memory::dealloc(p, memory::CLASS_POOL); }
	};
} // namespace core

#endif // Object_h__