/* File		: /atomic/details/atomic-gcc-4.1.0+.h
 * Author	: V. Sverchinsky
 * E-Mail	: vitalii.sverchinsky@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_ATOMIC_DETAILS_ATOMIC_GCC_4_1_0_H_
#define	FREYA_ATOMIC_DETAILS_ATOMIC_GCC_4_1_0_H_

#include "FreyaSupportInternal.h"
#include "atomic/memory_order.h"
#include "atomic/atomic-interface.h"
#include <stddef.h>

namespace atomic
{
    namespace details
    {
        template<typename BuiltIn, size_t Sz = sizeof(BuiltIn)>
        struct intrinsics
        {
                inline static void exchange(BuiltIn* dest, BuiltIn src);
        };
        
#if defined(__GNUC__)
        template<typename BuiltIn, size_t Sz>
        FREYA_SUPPORT_FORCE_INLINE void intrinsics<BuiltIn, Sz>::exchange(BuiltIn* dest, BuiltIn src)
        {
            __asm__
            (
                "lock; xchg      %0, %1" : "=m"(*dest) : "r"(src), "m"(*dest) : "memory"
            );
        }
#elif defined(__clang__)
        template<typename BuiltIn, size_t Sz>
        FREYA_SUPPORT_FORCE_INLINE void intrinsics<BuiltIn, Sz>::exchange(BuiltIn* dest, BuiltIn src)
        {
            __sync_swap(dest, src);
        }
#endif
        
    }//namespace details
    
    template<typename BuiltIn>
    inline BuiltIn atomic<BuiltIn>::operator ++()
    {
        return __sync_add_and_fetch(&m_variable, 1);
    }
    
    template<typename BuiltIn>
    inline  BuiltIn atomic<BuiltIn>::operator ++(int)
    {
        return __sync_fetch_and_add(&m_variable, 1);
    }
    
    template<typename BuiltIn>
    inline BuiltIn atomic<BuiltIn>::operator --()
    {
        return __sync_sub_and_fetch(&m_variable, 1);
    }
    
    template<typename BuiltIn>
    inline BuiltIn atomic<BuiltIn>::operator --(int)
    {
        return __sync_fetch_and_sub(&m_variable, 1);
    }
    
    template<typename BuiltIn>
    inline BuiltIn atomic<BuiltIn>::load(const MemoryOrder order) const
    {
        BuiltIn ret = *static_cast<volatile const BuiltIn*>(&m_variable);
        //TODO: provide memory barrier
        return ret;
    }
    
    template<typename BuiltIn>
    inline void atomic<BuiltIn>::store(const BuiltIn value, const MemoryOrder order)
    {
        switch(order)
        {
            case(MemoryOrderSequential):
                details::intrinsics<BuiltIn>::exchange(&m_variable, value);
                break;
            case(MemoryOrderAcquire):
                *static_cast<volatile BuiltIn*>(&m_variable) = value;
                break;
            default:
                m_variable = value;
        }
    }
    
    template<typename BuiltIn>
    inline unsigned atomic<BuiltIn>::bit_test_and_set(const unsigned bit)
    {
        const BuiltIn mask = 0x1 << bit;
        return (unsigned) ((__sync_lock_test_and_set(&m_variable, mask) & mask) == mask);
    }
    
    template<typename BuiltIn>
    inline unsigned atomic<BuiltIn>::bit_test_and_reset(const unsigned bit)
    {
        //:TODO: It is for a while...
        const BuiltIn mask = 0x1 << bit;
        if((__sync_lock_test_and_set(&m_variable, mask) & mask) == mask)
        {
                __sync_and_and_fetch(&m_variable, ~mask);
                return 1;
        }
        return 0;
    }
    
}//namespace atomic

#endif/*FREYA_ATOMIC_DETAILS_ATOMIC_GCC_4_1_0_H_*/

