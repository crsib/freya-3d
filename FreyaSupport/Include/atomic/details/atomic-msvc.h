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
//#pragma intrinsic(_intrelockedbittestandreset)	// btr instruction

//#pragma intrinsic(_InterlockedIncrement16)		// Atomic Word increment
#pragma intrinsic(_InterlockedIncrement)		// Atomic Double word increment


//#pragma intrinsic(_InterlockedDecrement16)		// Atomic Word decrement
#pragma intrinsic(_InterlockedDecrement)		// Atomic Double word decrement


// Intrinsics available only on x64(Intel 64 or AMD 64) machines
#if defined(_M_X64) || defined(_M_AMD64)
//	#pragma intrinsic(_InterlockedIncrement64)			// Atomic Quad word increment
//	#pragma intrinsic(_InterlockedDecrement64)			// Atomic Quad word decrement
	#pragma intrinsic(_interlockedbittestandset64)		// bts instruction for quad word operand
	#pragma intrinsic(_interlockedbittestandreset64)	// btr instruction for quad word operand
#endif


namespace atomic
{
	namespace details 
	{
		inline void fence(const MemoryOrder order);

		template<typename BuiltIn, size_t Sz>
		inline BuiltIn increment(volatile BuiltIn* address);

		template<typename BuiltIn, size_t Sz>
		inline BuiltIn decrement(volatile BuiltIn* address);

		template<typename BuiltIn, size_t Sz>
		inline unsigned bts(BuiltIn* var, const unsigned bit_num);

		template<typename BuiltIn, size_t Sz>
		inline unsigned btr(BuiltIn* var, const unsigned bit_num);

//-------------------------------------------------------------------------------------------------

		void fence(const MemoryOrder order)
		{
			switch(order)
			{
				case(MemoryOrderSequential) :
					MemoryBarrier();
					break;
				default : ;
			}
		}

//-------------------------------------------------------------------------------------------------

/*		template<> inline //signed word
		__int16 increment<__int16, 2>(volatile __int16* var)
		{
			return static_cast<__int16>(_InterlockedIncrement16(reinterpret_cast<volatile short*>(var)));
		}*/

/*		template<> inline // unsigned word
		unsigned __int16 increment<unsigned __int16, 2>(volatile unsigned __int16* var)
		{
			return static_cast<unsigned __int16>(_InterlockedIncrement16(reinterpret_cast<volatile short*>(var)));
		}*/

		template<> inline // signed word
		short increment<short, 2>(volatile short* var)
		{
			return _InterlockedIncrement16(var);
		}

		template<> inline // unsigned word
		unsigned short increment<unsigned short, 2>(volatile unsigned short* var)
		{
			return static_cast<unsigned short>(_InterlockedIncrement16(reinterpret_cast<volatile short*>(var)));
		}

/*		template<> inline // signed double word
		__int32 increment<__int32, 4>(volatile __int32* var)
		{
			return static_cast<__int32>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}*/

/*		template<> inline // unsigned double word
		unsigned __int32 increment<unsigned __int32, 4>(volatile unsigned __int32* var)
		{
			return static_cast<unsigned __int32>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}*/

		template<> inline // signed double word
		int increment<int, 4>(volatile int* var)
		{
			return static_cast<int>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}

		template<> inline // unsigned double word
		unsigned increment<unsigned, 4>(volatile unsigned* var)
		{
			return static_cast<unsigned>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}

		template<> inline // signed double word
		long increment<long, 4>(volatile long* var)
		{
			return static_cast<long>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}

		template<> inline // unsigned double word
		unsigned long increment<unsigned long, 4>(volatile unsigned long* var)
		{
			return static_cast<unsigned long>(_InterlockedIncrement(reinterpret_cast<volatile LONG*>(var)));
		}

#if defined(_M_X64) || defined(_M_AMD64)
		
		template<> inline // signed quad word
		__int64 increment<__int64, 8>(volatile __int64* var)
		{
			return _InterlockedIncrement64(var);
		}

		template<> inline // unsigned quad word
		unsigned __int64 increment<unsigned __int64, 8>(volatile unsigned __int64* var)
		{
			return static_cast<unsigned __int64>(_InterlockedIncrement64(reinterpret_cast<volatile __int64*>(var)));
		}

		template<> inline // signed quad word
		long increment<long, 8>(volatile long* var)
		{
			return static_cast<long>(_InterlockedIncrement64(reinterpret_cast<volatile __int64*>(var)));
		}

		template<> inline // unsigned quad word
		unsigned long increment<unsigned long, 8>(volatile unsigned long* var)
		{
			return static_cast<unsigned long>(_InterlockedIncrement64(reinterpret_cast<volatile __int64*>(var)));
		}

#endif

//-------------------------------------------------------------------------------------------------

		template<> inline
		__int16 decrement<__int16, 2>(volatile __int16* var)
		{
			return _InterlockedDecrement16(reinterpret_cast<volatile short*>(var));
		}

		template<> inline
		unsigned __int16 decrement<unsigned __int16, 2>(volatile unsigned __int16* var)
		{
			return _InterlockedDecrement16(reinterpret_cast<volatile short*>(var));
		}

		template<> inline
		int decrement<int, 4>(volatile int* var)
		{
			return _InterlockedDecrement(reinterpret_cast<volatile LONG*>(var));
		}

		template<> inline
		unsigned decrement<unsigned, 4>(volatile unsigned* var)
		{
			return _InterlockedDecrement(reinterpret_cast<volatile LONG*>(var));
		}

#if defined(_M_X64) || defined(_M_AMD64)

		template<> inline
		__int64 decrement<__int64, 8>(volatile __int64* var)
		{
			return _InterlockedDecrement64(var);
		}

		template<> inline
		unsigned __int64 decrement<unsigned __int64, 8>(volatile unsigned __int64* var)
		{
			return _InterlockedDecrement64(reinterpret_cast<volatile unsigned __int64*>(var));
		}

#endif

//-------------------------------------------------------------------------------------------------

		template<> inline
		unsigned bts<int, 4>(int* var, const unsigned bit_num)
		{
			return _interlockedbittestandset(reinterpret_cast<LONG*>(var), bit_num);
		}

//-------------------------------------------------------------------------------------------------

		template<> inline
		unsigned btr<int, 4>(int* var, const unsigned bit_num)
		{
			return _interlockedbittestandreset(reinterpret_cast<LONG*>(var), bit_num);
		}

		//-------------------------------------------------------------------------------------------------

		template<> inline
			unsigned bts<unsigned, 4>(unsigned* var, const unsigned bit_num)
		{
			return _interlockedbittestandset(reinterpret_cast<LONG*>(var), bit_num);
		}

		//-------------------------------------------------------------------------------------------------

		template<> inline
			unsigned btr<unsigned, 4>(unsigned* var, const unsigned bit_num)
		{
			return _interlockedbittestandreset(reinterpret_cast<LONG*>(var), bit_num);
		}
	}

//-------------------------------------------------------------------------------------------------

	/*template<typename BuiltIn>
	atomic<BuiltIn>::operator bool() const
	{
		bool ret = (m_variable != 0);
		details::fence(MemoryOrderSequential); // update ret immediately
		return ret;
	}*/

	/*template<typename BuiltIn>
	atomic<BuiltIn>::operator BuiltIn() const
	{
		BuiltIn ret = m_variable;
		details::fence(MemoryOrderSequential);
		return ret;
	}*/

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(void)
	{
		return details::increment<BuiltIn, sizeof(BuiltIn)>(&m_variable) - 1;
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(int)
	{
		return details::increment<BuiltIn, sizeof(BuiltIn)>(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator--(void)
	{
		return 1 + details::decrement<BuiltIn, sizeof(BuiltIn)>(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator--(int)
	{
		return details::decrement<BuiltIn, sizeof(BuiltIn)>(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::load(const MemoryOrder order) const
	{
		BuiltIn ret = *reinterpret_cast<volatile const BuiltIn*>(&m_variable); // depricate compiler optimizations
		details::fence(order);
		return ret;
	}

	template<typename BuiltIn> 
	void atomic<BuiltIn>::store(const BuiltIn& from, const MemoryOrder order)
	{
		m_variable = from;
		details::fence(order);
	}

	template<typename BuiltIn>
	unsigned atomic<BuiltIn>::bit_test_and_set(const unsigned bit_num)
	{
		return details::bts<BuiltIn, sizeof(BuiltIn)>(&m_variable, bit_num);
	}

	template<typename BuiltIn>
	unsigned atomic<BuiltIn>::bit_test_and_reset(const unsigned bit_num)
	{
		return details::btr<BuiltIn, sizeof(BuiltIn)>(&m_variable, bit_num);
	}
}

#endif//FREYA_ATOMIC_MSVC_H_