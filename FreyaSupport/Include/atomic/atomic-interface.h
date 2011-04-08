/* File		: /atomic/details/atomic-interface.h
 * Author	: V. Sverchinsky
 * E-Mail	: vitalii.sverchinsky@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_ATOMIC_INTERFACE_H_
#define FREYA_ATOMIC_INTERFACE_H_

#include "FreyaSupportInternal.h"
#include "atomic/memory_order.h"

///
namespace atomic
{
	///
	template<typename BuiltIn>
	class FREYA_SUPPORT_EXPORT atomic
	{
	public:

		///Default constructor. Initializes with default to base type.
		inline atomic() { }
		///Initialize atomic with a specified value.
		inline explicit atomic(const BuiltIn& init_val) : m_variable(init_val) { }

		///Compares two atomics for equality.
		/** */
		inline bool operator==(const atomic<BuiltIn>& other) const
		{ 
			return m_variable == other.m_variable;
		}
		///Compares this atomic and builtin for equality.
		/** */
		inline bool operator==(const BuiltIn& other) const
		{ 
			return m_variable == other;
		}
		///Compares two atomics for inequality.
		/** */
		inline bool operator!=(const atomic<BuiltIn>& other) const
		{ 
			return m_variable != other.m_variable;
		}
		///Compares this atomic and builtin for inequality.
		/** */
		inline bool operator!=(const BuiltIn& other) const 
		{
			return m_variable != other; 
		}

		///Assignment with cast from builtin to atomic.
		/** */
		inline atomic<BuiltIn>& operator=(const BuiltIn& rval)
		{
			store(rval, MemoryOrderSequential);
			return *this;
		}

		inline BuiltIn operator++();	///< Atomic postfix increment.
		inline BuiltIn operator++(int);	///< Atomic prefix increment.
		inline BuiltIn operator--();	///< Atomic postfix decrement.
		inline BuiltIn operator--(int);	///< Atomic prefix decrement.

		// :TODO: Implement
		/* inline atomic<BuiltIn>& operator+=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator-=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator&=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator|=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator^=(const BuiltIn& rval);
		*/

		///Load value from memory.
		inline BuiltIn load(const MemoryOrder order = MemoryOrderSequential) const;
		///Store value into memory.
		inline void store(const BuiltIn& from, const MemoryOrder order = MemoryOrderSequential);

		/// Atomic bit test and set.
		/** \param bit_num Bit number [0..sizeof(BuiltIn)*8](depends on base type size) to test
		  * and set(to 1 if test have returned 0).
		  * \return Result of the test, i.e. if specified bit was equal to 1(test was failed)
		  * it will return 1.
		  */
		inline unsigned bit_test_and_set(const unsigned bit_num);
		/// Atomic bit test and reset.
		/** \param bit_num Bit number [0..sizeof(BuiltIn)*8](depends on base type size) to test
		  * and reset(to 0 if test have returned 1).
		  * \return Result of the test, i.e. if specified bit was equal to 0(test was failed)
		  * it will return 0.
		  */
		inline unsigned bit_test_and_reset(const unsigned bit_num);

	private:
		/// Copy constructor is depricated.
		atomic(const atomic<BuiltIn>&);
		/// Assignment operator is depricated.
		atomic<BuiltIn>& operator=(const atomic<BuiltIn>&);

		BuiltIn m_variable;
	};
}

#endif//FREYA_ATOMIC_INTERFACE_H_
