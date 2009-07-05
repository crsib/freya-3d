#include "math/MathSubsystem.h"

namespace core
{
namespace memory
{
	void* Allocate(size_t,unsigned);
	void  Free(void*,unsigned);
}
}
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
