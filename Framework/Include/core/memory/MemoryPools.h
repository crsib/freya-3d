/*
 * MemoryPools.h
 *
 *  Created on: Oct 12, 2009
 *      Author: crsib
 */

#ifndef MEMORYPOOLS_H_
#define MEMORYPOOLS_H_
namespace core
{
namespace memory
{
//!Default memory pools location
	enum MEMORYPOOLTYPE
	{
		STL_POOL = 0,
		MATH_POOL,
		GENERIC_POOL,
		CLASS_POOL,
		LUA_POOL,
		XML_POOL,
	};
}
}
#endif /* MEMORYPOOLS_H_ */
