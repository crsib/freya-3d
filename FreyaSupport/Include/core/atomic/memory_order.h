#ifndef FREYA_MEMORY_ORDER_H_
#define FREYA_MEMORY_ORDER_H_

namespace atomic
{
	enum MemoryOrder
	{
		MemoryOrderSequential,	///<
		MemoryOrderAcquire,		///<
		MemoryOrderRelease,		///<
		MemoryOrderRelaxed		///<
	};
}


#endif//FREYA_MEMORY_ORDER_H_