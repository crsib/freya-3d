/* File		: FreyaReflect: ReflectionObject.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_ReflectionObject_h__
#define Reflect_ReflectionObject_h__

#include "FreyaReflectInternal.h"

namespace reflect
{

#define REFLECTION_OBJECT() \
	static  Class* GetClass(); \
	virtual Class* getClass() const { return GetClass(); }

	class Class;

	class FREYA_REFLECT_EXPORT ReflectionObject
	{
	public:
		REFLECTION_OBJECT();
	};
} // namespace reflect

#endif // Reflect_Class_h__