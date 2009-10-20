#ifndef MATHSUBSYSTEM_H_
#define MATHSUBSYSTEM_H_

#include <cstdlib>
#include "internal.h"
#include "core/memory/MemoryPools.h"
#ifdef _FREYA_SHARED_PLUGIN

namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#else
namespace core
{
namespace memory
{
	EXPORT void* Allocate(size_t,unsigned);
	EXPORT void  Free(void*,unsigned);
}
}
#endif

namespace math
{

#ifdef _MSC_VER
__declspec(align(16)) class MathSubsystem
#elif __GNUC__
class MathSubsystem
#else
#	error "This compiler seems to be not supported"
#endif
{
public:
	MathSubsystem(){}
	~MathSubsystem(){}

	static void* operator new(size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::MATH_POOL);
	}

	static void  operator delete(void* p)
	{
		core::memory::Free(p,core::memory::MATH_POOL);
	}

	static void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,core::memory::MATH_POOL);
	}

	static void  operator delete[](void* p)
	{
		core::memory::Free(p,core::memory::MATH_POOL);
	}

#ifdef _MSC_VER
};
#elif __GNUC__
} __attribute__ ((aligned(16)));
#else
#	error "This compiler seems to be not supported"
#endif

}

#endif /*MATHSUBSYSTEM_H_*/
