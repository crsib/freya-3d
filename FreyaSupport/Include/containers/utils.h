/* File		: containers/utils.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_utils_h__
#define Containers_utils_h__

#include "containers/type_utils.h"

namespace containers
{
	//! Pair of elements
	/*!
	 * This template is an ADT describing pair of elements
	 * \tparam FirstType is a type of the first element
	 * \tparam SecondType is a type of second element
	 * \ingroup grpContainers
	 */
	template<typename FirstType, typename SecondType>
	struct pair
	{
		//! Type of the first element typedef
		typedef FirstType	first_type;
		//! Type of the second element typedef
		typedef SecondType	second_type;
		//! First element
		first_type			first;
		//! Second element
		second_type			second;
		//! Create a pair of elements using specified values
		/*!
		 * Create a pair of elements using specified values
		 * \param f is a value of first element
		 * \param s is a value of second element
		 */
		pair( typename const_reference<FirstType>::type f,  typename const_reference<SecondType>::type s ) : first(f), second(s) {}
		//! Copy constructor
		pair( const pair& other) : first ( other.first ), second (other.second) {}
		//! Assignment operator
		pair& operator = ( const pair& lhs ) { first = lhs.first; second = lhs.second; return *this; }
		//! Check two pairs for equality
		bool  operator == ( const pair& lhs ) const { return first == lhs.first && second == lhs.second; }
		//! Check two pair for inequality
		bool  operator != ( const pair& lhs ) const { return first != lhs.first || second != lhs.second; }
	}; // struct pair

	//! Helper method, to create a pair of elements
	//! \ingroup grpContainers
	template<typename F, typename S>
	pair<F,S>		make_pair( F f,  S s )
	{
		return pair<F,S>(f,s);
	}

	//! Equality predicate based on operator ==
	template<typename T>
	struct equal
	{
		bool operator ()  (typename const_reference<T>::type lhs, typename const_reference<T>::type rhs) const
		{
			return lhs == rhs;
		}
	}; //! struct equal

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////// Hashes //////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename T> struct hash;
	//!\cond
	template <typename T> struct hash<T*> // Note that we use the pointer as-is and don't divide by sizeof(T*). This is because the table is of a prime size and this division doesn't benefit distribution.
	{ uint32_t operator()(T* p) const { return uint32_t(uintptr_t(p)); } };

	template <> struct hash<const bool>
	{ uint32_t operator()(const bool val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const char>
	{ uint32_t operator()(const char val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const signed char>
	{ uint32_t operator()(const signed char val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const unsigned char>
	{ uint32_t operator()(const unsigned char val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const signed short>
	{ uint32_t operator()(const short val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const unsigned short>
	{ uint32_t operator()(const unsigned short val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const signed int>
	{ uint32_t operator()(const signed int val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const unsigned int>
	{ uint32_t operator()(const unsigned int val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const signed long>
	{ uint32_t operator()(const signed long val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const unsigned long>
	{ uint32_t operator()(const unsigned long val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const signed long long>
	{ uint32_t operator()(const signed long long val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const unsigned long long>
	{ uint32_t operator()(const unsigned long long val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const float>
	{ uint32_t operator()(const float val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const double>
	{ uint32_t operator()(const double val) const { return static_cast<const uint32_t>(val); } };

	template <> struct hash<const long double>
	{ uint32_t operator()(const long double val) const { return static_cast<const uint32_t>(val); } };
	//!\endcond
} // namespace containers

#endif // utils_h__