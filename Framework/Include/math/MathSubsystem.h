#ifndef MATHSUBSYSTEM_H_
#define MATHSUBSYSTEM_H_

#include <cstdlib>
#include "internal.h"
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

class MathSubsystem
{
public:
	MathSubsystem(){}
	~MathSubsystem(){}

	static void* operator new(size_t sz)
	{
		return core::memory::Allocate(sz,1);
	}

	static void  operator delete(void* p)
	{
		core::memory::Free(p,1);
	}

	static void* operator new[](size_t sz)
	{
		return core::memory::Allocate(sz,1);
	}

	static void  operator delete[](void* p)
	{
		core::memory::Free(p,1);
	}
};

}

#endif /*MATHSUBSYSTEM_H_*/
