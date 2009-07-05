/*
 * EString.h
 *
 *  Created on: 25-Aug-08
 *      Author: vedenko
 */

#ifndef ESTRING_H_
#define ESTRING_H_
#include <string>
#include <core/memory/MemoryAllocator.h>
//! String class to be used inside engine
typedef std::basic_string<char,std::char_traits<char>,core::memory::MemoryAllocator<char> > EString;
//typedef std::string EString;
#endif /* ESTRING_H_ */
