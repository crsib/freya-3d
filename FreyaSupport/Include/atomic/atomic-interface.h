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

/// \brief This namespace contains built-in based atomic template class implementation.
namespace atomic
{
	/// \brief This template class provides built-in based atomic data types, and the set of useful operations.
	/** There is a number of constraints applied to base type: it's size should be at least 2 bytes,
	 * but does not exceed the size of 8 bytes. Besides, not all machines provides native support of
	 * atomic quadword operations. So it is highly recommended to use dword-sized types as base for
	 * atomics.
	 * \tparam BuiltIn Base type for atomic, provides information about it's size and interpretation rules.
	 */
	template<typename BuiltIn>
	class atomic
	{
	public:

		/// \brief Default constructor. Initializes with default to base type.
		inline atomic() { }
		/// \brief Initialize atomic with a specified value.
		inline explicit atomic(const BuiltIn& init_val) : m_variable(init_val) { }

		/// \brief Compares two atomics for equality.
		inline bool operator==(const atomic<BuiltIn>& other) const
		{ 
			return load() == other.load();
		}
		/// \brief Compares this atomic and builtin for equality.
		inline bool operator==(const BuiltIn& other) const
		{ 
			return load() == other;
		}
		/// \brief Compares two atomics for inequality.
		inline bool operator!=(const atomic<BuiltIn>& other) const
		{ 
			return load() != other.load();
		}
		/// \brief Compares this atomic and builtin for inequality.
		inline bool operator!=(const BuiltIn& other) const 
		{
			return load() != other; 
		}

		/// \brief Store(MemoryOrderSequential) with cast from builtin.
		inline atomic<BuiltIn>& operator=(const BuiltIn& rval)
		{
			store(rval);
			return *this;
		}

		/// \brief Atomic postfix increment.
		/** \return Value before increment was applied. */
		inline BuiltIn operator++();
		/// \brief Atomic prefix increment.
		/** \return Resulting value. */
		inline BuiltIn operator++(int);
		/// \brief Atomic postfix deccrement.
		/** \return Value before decrement was applied. */
		inline BuiltIn operator--();
		/// \brief Atomic prefix decrement.
		/** \return Resulting value. */
		inline BuiltIn operator--(int);

		// :TODO: Implement the following
		/* inline atomic<BuiltIn>& operator+=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator-=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator&=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator|=(const BuiltIn& rval);
		inline atomic<BuiltIn>& operator^=(const BuiltIn& rval);
		*/

		/// \brief Load value from memory.
		/** 
		 * \param order Memory consistency model(see atomic::MemoryOrder).
		 * \return Local copy of the variable. Result may vary depending on memory order.
		 */
		inline BuiltIn load(const MemoryOrder order = MemoryOrderSequential) const;
		/// \brief Store value into memory.
		/** The value of variable would be updated immediately if default memory order was used.
		 * \param value Value to be stored.
		 * \param order Memory consistency model(see atomic::MemoryOrder).
		 * \return Local copy of the variable. Result may vary depending on memory order.
		 */
		inline void store(const BuiltIn value, const MemoryOrder order = MemoryOrderSequential);

		/// \brief Atomic bit test and set.
		/** \param bit Bit number [0..sizeof(BuiltIn)*8 - 1](depends on base type size) to test
		  * and set(to 1 if test have returned 0).
		  * \return Result of the test, i.e. if specified bit was equal to 1(test was failed)
		  * it will return 1.
		  */
		inline unsigned bit_test_and_set(const unsigned bit);
		/// \brief Atomic bit test and reset.
		/** \param bit Bit number [0..sizeof(BuiltIn)*8 - 1](depends on base type size) to test
		  * and reset(to 0 if test have returned 1).
		  * \return Result of the test, i.e. if specified bit was equal to 0(test was failed)
		  * it will return 0.
		  */
		inline unsigned bit_test_and_reset(const unsigned bit);

	private:
		/// Copy constructor is forbidden.
		atomic(const atomic<BuiltIn>&);
		/// Assignment operator is depricated.
		atomic<BuiltIn>& operator=(const atomic<BuiltIn>&);

		BuiltIn m_variable;
	};
}

#endif//FREYA_ATOMIC_INTERFACE_H_
