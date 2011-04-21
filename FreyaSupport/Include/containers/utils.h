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
		first_type			second;

		pair( typename const_reference<FirstType>::type f,  typename const_reference<SecondType>::type s ) : first(f), second(s) {}
		pair( const pair& other) : first ( other.first ), second (other.second) {}
		pair& operator = ( const pair& lhs ) { first = lhs.first; second = lhs.second; return *this; }

		bool  operator == ( const pair& lhs ) const { return first == lhs.first && second == lhs.second; }
		bool  operator != ( const pair& lhs ) const { return first != lhs.first || second != lhs.second; }
	}; // struct pair

	//!
	template<typename F, typename S>
	pair<F,S>		make_pair( typename const_reference<F>::type f,  typename const_reference<S>::type s )
	{
		return pair<F,S>(f,s);
	}

	//!
	template<typename T>
	struct equal
	{
		bool operator () (typename const_reference<T>::type lhs, typename const_reference<T>::type rhs)
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

	template <> struct hash<bool>
	{ uint32_t operator()(bool val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<char>
	{ uint32_t operator()(char val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<signed char>
	{ uint32_t operator()(signed char val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<unsigned char>
	{ uint32_t operator()(unsigned char val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<signed short>
	{ uint32_t operator()(short val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<unsigned short>
	{ uint32_t operator()(unsigned short val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<signed int>
	{ uint32_t operator()(signed int val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<unsigned int>
	{ uint32_t operator()(unsigned int val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<signed long>
	{ uint32_t operator()(signed long val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<unsigned long>
	{ uint32_t operator()(unsigned long val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<signed long long>
	{ uint32_t operator()(signed long long val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<unsigned long long>
	{ uint32_t operator()(unsigned long long val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<float>
	{ uint32_t operator()(float val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<double>
	{ uint32_t operator()(double val) const { return static_cast<uint32_t>(val); } };

	template <> struct hash<long double>
	{ uint32_t operator()(long double val) const { return static_cast<uint32_t>(val); } };

} // namespace containers

#endif // utils_h__