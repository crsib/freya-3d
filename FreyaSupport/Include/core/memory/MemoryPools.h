// This file is a part of Freya 3D Engine

#ifndef MEMORYPOOLS_H_
#define MEMORYPOOLS_H_
namespace core
{
namespace memory
{
//!Default memory pools location
	enum MEMORYPOOLTYPE
	{
		DEFAULT_POOL = 0,
		STL_POOL ,
		MATH_POOL,
		GENERIC_POOL,
		CLASS_POOL,
		LUA_POOL,
		LAST_POOL
	};
}
}
#endif /* MEMORYPOOLS_H_ */
