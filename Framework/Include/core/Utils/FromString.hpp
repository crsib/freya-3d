#ifndef FROMSTRING_HPP_
#define FROMSTRING_HPP_

//Based on code from http://www.codeguru.com/forum/showthread.php?t=231054

#include <string>
#include <sstream>
#include <iostream>

#include <core/EString.h>

//!Convert string to value (overloaded version to work with engine strings
/*!
 * Get an item of type T from string.
 * \tparam T is a real type (not reference) of a value to be read
 * \param t is reference to value to be read
 * \param s is a string to be parsed
 * \param f is std::ios_base to use with integer numbers
 * \return true on success, false otherwise
 */
//*
template <class T> bool from_string(T& t, const EString& s,std::ios_base& (*f)(std::ios_base&) = std::dec)
{
	std::istringstream iss(s.c_str());
	return !(iss >> f >> t).fail();
}
//*/
#endif /*FROMSTRING_HPP_*/
