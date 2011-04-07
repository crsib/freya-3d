#ifndef CMEMALLOCATOR_H_
#define CMEMALLOCATOR_H_
#include <cctype>
#include <cstdlib>
#include <iostream>
#include "FreyaSupportInternal.h"
#include "core/memory/MemoryPools.h"
namespace core
{
namespace memory
{

FREYA_SUPPORT_EXPORT void*	alloc(size_t size, unsigned pool = core::memory::GENERIC_POOL) throw();
FREYA_SUPPORT_EXPORT void	dealloc(void* p, unsigned pool = core::memory::GENERIC_POOL) throw();	

//!STL compatible memory allocator to use memory arena for allocation. For detailed information use C++ documentation
template<typename T,unsigned pool = core::memory::STL_POOL>
class MemoryAllocator// : public std::allocator<T>
{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	MemoryAllocator(){};
	~MemoryAllocator(){};
	template<class U,unsigned p> 	 MemoryAllocator(const MemoryAllocator<U,p>& m)
	{

	}
	static void* operator new(size_t sz);

	static void* operator new(size_t sz,void* p);

	static void  operator delete(void* p);

	static void* operator new[](size_t sz);

	static void  operator delete[](void* p);
	//!Provided for STL compatibility
	pointer alloc(size_type n,const void* hint = 0);
	//!Provided for STL compatibility
	void dealloc(pointer p,size_type n);
	//!Provided for STL compatibility
	pointer address(reference r) const {return &r;}
	//!Provided for STL compatibility
	const_pointer address(const_reference r) const {return &r;}
	//!Provided for STL compatibility
	void construct(pointer p, const_reference val)
	{
		::new(p) T(val);
	}
	//!Provided for STL compatibility
	void destroy(pointer p){p->~T();}
	//!Provided for STL compatibility
	size_type max_size()const {return -1;}
	//void dispose() { }
	//!Provided for STL compatibility
	template<class U,unsigned p = 0> struct rebind {typedef MemoryAllocator<U,p> other;};
};
//!Provided for STL compatibility
template<typename T,unsigned pool> bool operator== (const MemoryAllocator<T,pool>& _1,const MemoryAllocator<T,pool>& _2)
{
	return true;
}
//!Provided for STL compatibility
template<typename T,unsigned pool> bool operator!= (const MemoryAllocator<T,pool>& _1,const MemoryAllocator<T,pool>& _2)
{
	return false;
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void* MemoryAllocator<T,pool>::operator new(size_t sz)
{
	return alloc(sz,pool);
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void*  MemoryAllocator<T,pool>::operator new(size_t sz,void* p)
{
	return p;
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void   MemoryAllocator<T,pool>::operator delete(void* p)
{
	dealloc(p,pool);
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void*  MemoryAllocator<T,pool>::operator new[](size_t sz)
{
	return alloc(sz,pool);
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void   MemoryAllocator<T,pool>::operator delete[](void* p)
{
	dealloc(p,pool);
}
//!Provided for STL compatibility
template<typename T,unsigned pool> T*  MemoryAllocator<T,pool>::alloc(size_t n,const void* hint)
{
	return static_cast<T*> (alloc(n*sizeof(T),core::memory::STL_POOL));
}
//!Provided for STL compatibility
template<typename T,unsigned pool> void  MemoryAllocator<T,pool>::dealloc(T* p,size_t n)
{
	dealloc(p,core::memory::STL_POOL);
}

//typedef MemoryAllocator <T,0> MemAllocator<T>;
}
}

#endif /*CMEMALLOCATOR_H_*/


