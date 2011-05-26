/* File		: FreyaReflect: ReflectionDatabase.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_ReflectionDatabase_h__
#define Reflect_ReflectionDatabase_h__

#include "FreyaReflectInternal.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT ReflectionDatabase
	{
		ReflectionDatabase();
		~ReflectionDatabase();
	public:
		static ReflectionDatabase&		getInstance() { static ReflectionDatabase __db; return __db; }
	}; // class ReflectionDatabase
} // namespace reflect

#endif // Reflect_ReflectionDatabase_h__