#include "math/MathSubsystem.h"

#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
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
	void* Allocate(size_t,unsigned);
	void  Free(void*,unsigned);
}
}
#endif

namespace math
{

MathSubsystem::MathSubsystem()
{
}

MathSubsystem::~MathSubsystem()
{
}

void* MathSubsystem::operator new(size_t sz)
{
	return core::memory::Allocate(sz,1);
}

void  MathSubsystem::operator delete(void* p)
{
	core::memory::Free(p,1);
}

void* MathSubsystem::operator new[](size_t sz)
{
	return core::memory::Allocate(sz,1);
}

void  MathSubsystem::operator delete[](void* p)
{
	core::memory::Free(p,1);
}
}
