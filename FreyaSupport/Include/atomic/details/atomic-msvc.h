/* File		: /atomic/details/atomic-msvc.h
 * Author	: V. Sverchinsky
 * E-Mail	: vitalii.sverchinsky@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_ATOMIC_MSVC_H_
#define FREYA_ATOMIC_MSVC_H_

#include <Windows.h>
#include <intrin.h>
#include "atomic/memory_order.h"
#include "atomic/atomic-interface.h"

// Intrinsics available on all x86 based machines
#pragma intrinsic(_ReadWriteBarrier)			// Prevents compiler load/store reorder.
#pragma intrinsic(_interlockedbittestandset)	// bts instruction
#pragma intrinsic(_InterlockedIncrement)		// Atomic Double word increment
#pragma intrinsic(_InterlockedDecrement)		// Atomic Double word decrement
#pragma intrinsic(_InterlockedExchange)			// Exchange for double word operands


// Intrinsics available only on x64(Intel 64 or AMD 64) machines
#if defined(_M_X64) || defined(_M_AMD64)
//	#pragma intrinsic(_InterlockedIncrement64)			// Atomic Quad word increment
//	#pragma intrinsic(_InterlockedDecrement64)			// Atomic Quad word decrement
	#pragma intrinsic(_interlockedbittestandset64)		// bts instruction for quad word operand
	#pragma intrinsic(_interlockedbittestandreset64)	// btr instruction for quad word operand

	#pragma intrinsic(_IntrelockedExchange64)			// Exchange for quad word operands
#endif


namespace atomic
{
	namespace details 
	{
		//-----------------------------------------------------------------------------------------

		// Helper structure. You need to provide only type(first param).
		template<typename Type, size_t Sz = sizeof(Type)>
		struct intrinsics
		{
			inline static Type inc(volatile Type* memaddr);

			inline static Type dec(volatile Type* memaddr);

			inline static unsigned bts(volatile Type* memaddr, const unsigned bit);

			inline static unsigned btr(volatile Type* memaddr, const unsigned bit);

			inline static void exchange(volatile Type* memaddr, const Type value);
		};

		//-----------------------------------------------------------------------------------------

		// implementation for word sized types
		template<typename Type>
		struct intrinsics<Type, 2>
		{
			// follows from compiler provided intrinsic functions prototypes
			typedef volatile short* dest_ptr_t;

			typedef short source_t;

			inline static Type inc(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedIncrement16(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

			inline static Type dec(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedDecrement16(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

#if defined(_M_IX86)

			inline static unsigned bts(volatile Type* memaddr, const unsigned bit)
			{
				__asm 
				{
					xor			eax, eax				// clear eax
					mov			ebx, bit
					mov			ecx, memaddr
					lock bts	word ptr [ecx], ebx
					adc			eax, eax				// eax += CF
				};//ret - eax
			}

			inline static unsigned btr(volatile Type* memaddr, const unsigned bit)
			{
				__asm
				{
					xor			eax, eax				// clear eax
					mov			ebx, bit
					mov			ecx, memaddr
					lock btr	word ptr [ecx], ebx
					adc			eax, eax				// eax += CF
				};//ret - eax
			}

			inline static void exchange(volatile Type* memaddr, const Type value)
			{
				__asm
				{
					mov			bx,	value
					mov			eax, memaddr
					xchg		word ptr [eax], bx
				};
			}
#endif// _M_IX86
		};

		//-----------------------------------------------------------------------------------------

		// implementation for dword sized types
		template<typename Type>
		struct intrinsics<Type, 4>
		{
			// follows from compiler provided intrinsic functions prototypes
			typedef LONG			dest_t;
			typedef volatile LONG*	dest_ptr_t;
			
			typedef LONG			source_t;
			typedef LONG*			source_ptr_t;

			inline static Type inc(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedIncrement(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

			inline static Type dec(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedDecrement(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

			inline static unsigned bts(volatile Type* memaddr, const unsigned bit)
			{
				return _interlockedbittestandset(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(bit));
			}

			inline static unsigned btr(volatile Type* memaddr, const unsigned bit)
			{
				return _interlockedbittestandreset(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(bit));
			}

			inline static void exchange(volatile Type* memaddr, const Type value)
			{
				_InterlockedExchange(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(value));
			}
		};

		//-----------------------------------------------------------------------------------------

#if defined(_M_X64) || defined(_M_AMD64)
		
		// implementation for qword sized types
		template<typename Type>
		struct intrinsics<Type, 8>
		{
			// follows from compiler provided intrinsic functions prototypes
			typedef __int64				dest_t;
			typedef volatile __int64*	dest_ptr_t;
			
			typedef __int64		source_t;
			typedef __int64*	source_ptr_t;

			inline static Type inc(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedIncrement64(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

			inline static Type dec(volatile Type* memaddr)
			{
				return static_cast<Type>( _InterlockedDecrement64(reinterpret_cast<dest_ptr_t>(memaddr)) );
			}

			inline static unsigned bts(volatile Type* memaddr, const unsigned bit)
			{
				return _interlockedbittestandset64(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(bit));
			}

			inline static unsigned btr(volatile Type* memaddr, const unsigned bit)
			{
				return _interlockedbittestandreset(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(bit));
			}

			inline static void exchange(volatile Type* memaddr, const Type value)
			{
				_InterlockedExchange(reinterpret_cast<dest_ptr_t>(memaddr), static_cast<source_t>(value));
			}
		};

		//-----------------------------------------------------------------------------------------

#endif// _M_X64 || _M_AMD64
		// read-write memory barrier
		inline void fence(const MemoryOrder order)
		{
			switch(order)
			{
				case(MemoryOrderSequential) :
					MemoryBarrier(); // full fence
					break;
				default : 
					break;
			}
		}

	}//namespace details

//-------------------------------------------------------------------------------------------------

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(void)
	{
		return details::intrinsics<BuiltIn>::inc(&m_variable) - 1;
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(int)
	{
		return details::intrinsics<BuiltIn>::inc(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator--(void)
	{
		return details::intrinsics<BuiltIn>::dec(&m_variable) + 1;
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator--(int)
	{
		return details::intrinsics<BuiltIn>::dec(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::load(const MemoryOrder order) const
	{
		BuiltIn ret = *reinterpret_cast<volatile const BuiltIn*>(&m_variable); // depricate compiler optimizations
		details::fence(order);
		return ret;
	}

	template<typename BuiltIn> 
	void atomic<BuiltIn>::store(const BuiltIn& source, const MemoryOrder order)
	{
		// make a local copy of the source variable to prevent data corumption
		BuiltIn temp = *reinterpret_cast<volatile const BuiltIn*>(&source);
		switch(order)
		{
		case(MemoryOrderSequential) :
			details::intrinsics<BuiltIn>::exchange(&m_variable, temp);
			break;
		default:
			break;
		};
	}

	template<typename BuiltIn>
	unsigned atomic<BuiltIn>::bit_test_and_set(const unsigned bit)
	{
		return details::intrinsics<BuiltIn>::bts(&m_variable, bit);
	}

	template<typename BuiltIn>
	unsigned atomic<BuiltIn>::bit_test_and_reset(const unsigned bit)
	{
		return details::intrinsics<BuiltIn>::btr(&m_variable, bit);
	}

}//namespace atomic

#endif//FREYA_ATOMIC_MSVC_H_