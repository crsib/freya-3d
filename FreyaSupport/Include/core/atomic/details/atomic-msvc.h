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
#include "../memory_order.h"
#include "../atomic-interface.h"

#pragma intrinsic(_ReadWriteBarrier)	// Prevents compiler load/store reorder.

#pragma intrinsic(_bittestandset)		// bts instruction
#pragma intrinsic(_bittestandreset)		// btr instruction

#pragma intrinsic(_InterlockedIncrement16)	// Atomic Word increment
#pragma intrinsic(_InterlockedIncrement)	// Atomic Double word increment
//#pragma intrinsic(_InterlockedIncrement64)	// Atomic Quad word increment

#pragma intrinsic(_InterlockedDecrement16)	// Atomic Word decrement
#pragma intrinsic(_InterlockedDecrement)	// Atomic Double word decrement
//#pragma intrinsic(_InterlockedDecrement64)	// Atomic Quad word decrement


namespace atomic
{
	namespace details 
	{
		inline void fence(const MemoryOrder order);

		template<typename BuiltIn, size_t Sz>
		inline BuiltIn increment(volatile BuiltIn* var);

		template<typename BuiltIn, size_t Sz>
		inline BuiltIn decrement(volatile BuiltIn* var);

		template<typename BuiltIn, size_t Sz>
		inline unsigned bts(BuiltIn* var, const unsigned bit_num);

		template<typename BuiltIn, size_t Sz>
		inline unsigned btr(BuiltIn* var, const unsigned bit_num);

		void fence(const MemoryOrder order)
		{
			switch(order)
			{
				case(MemoryOrderSequential) :
					MemoryBarrier(); // Prevent cpu load/store reordering, full fence.
					break;
				default : ;
			}
		}

		template<>
		int increment<int, 4>(volatile int* var)
		{
			return _InterlockedIncrement(reinterpret_cast<volatile LONG*>(var));
		}

		/*template<>
		long increment<long, 8>(volatile long* var)
		{
			return _InterlockedIncrement64(reinterpret_cast<volatile __int64*>(var));
		}*/

		template<>
		int decrement<int, 4>(volatile int* var)
		{
			return _InterlockedDecrement(reinterpret_cast<volatile LONG*>(var));
		}

		/*template<>
		long decrement<long, 8>(volatile long* var)
		{
			return _InterlockedDecrement64(reinterpret_cast<volatile __int64*>(var));
		}*/

		template<>
		unsigned bts<int, 4>(int* var, const unsigned bit_num)
		{
			return _bittestandset(reinterpret_cast<LONG*>(var), bit_num);
		}

		template<>
		unsigned btr<int, 4>(int* var, const unsigned bit_num)
		{
			return _bittestandreset(reinterpret_cast<LONG*>(var), bit_num);
		}
	}

	template<typename BuiltIn>
	atomic<BuiltIn>::operator bool() const
	{
		bool ret = m_variable;
		details::fence(MemoryOrderSequential); // update ret immediately
		return ret;
	}

	template<typename BuiltIn>
	atomic<BuiltIn>::operator BuiltIn() const
	{
		BuiltIn ret = m_variable;
		details::fence(MemoryOrderSequential); // update ret immediately
		return ret;
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(void)
	{
		return --details::increment<BuiltIn, sizeof(BuiltIn)>(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator++(int)
	{
		return details::increment<BuiltIn, sizeof(BuiltIn)>(&m_variable);
	}

	template<typename BuiltIn>
	BuiltIn atomic<BuiltIn>::operator--(void)
	{
		return ++details::decrement<BuiltIn, sizeof(BuiltIn)>(&m_variable);
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