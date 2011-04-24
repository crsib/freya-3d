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
	//!
	template<typename FirstType, typename SecondType>
	struct pair
	{
		typedef FirstType	first_type;
		typedef SecondType	second_type;

		first_type			first;
		second_type			second;

		pair( typename const_reference<FirstType>::type f,  typename const_reference<SecondType>::type s ) : first(f), second(s) {}
		pair( const pair& other) : first ( other.first ), second (other.second) {}
		pair& operator = ( const pair& lhs ) { first = lhs.first; second = lhs.second; return *this; }

		bool  operator == ( const pair& lhs ) const { return first == lhs.first && second == lhs.second; }
		bool  operator != ( const pair& lhs ) const { return first != lhs.first || second != lhs.second; }
	}; // struct pair

	//!
	template<typename F, typename S>
	pair<F,S>		make_pair( F f,  S s )
	{
		return pair<F,S>(f,s);
	}

	//!
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

} // namespace containers

#endif // utils_h__