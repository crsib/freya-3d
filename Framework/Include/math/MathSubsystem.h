#ifndef MATHSUBSYSTEM_H_
#define MATHSUBSYSTEM_H_

#include <cstdlib>

namespace math
{

class MathSubsystem
{
public:
	MathSubsystem();
	~MathSubsystem();

	static void* operator new(size_t sz);
	static void  operator delete(void* p);

	static void* operator new[](size_t sz);
	static void  operator delete[](void* p);
};

}

#endif /*MATHSUBSYSTEM_H_*/
