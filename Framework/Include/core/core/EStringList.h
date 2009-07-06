/*
 * EStringList.h
 *
 *  Created on: 26-Aug-08
 *      Author: vedenko
 */

#ifndef ESTRINGLIST_H_
#define ESTRINGLIST_H_
#include "core/EString.h"
#include "core/memory/MemoryAllocator.h"
#include <vector>
//! String list class to be used inside engine
typedef std::vector<EString,core::memory::MemoryAllocator<EString> > EStringList;

#endif /* ESTRINGLIST_H_ */
