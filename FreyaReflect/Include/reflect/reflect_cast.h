/* File		: FreyaReflect: reflect_cast.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_reflect_cast_h__
#define Reflect_reflect_cast_h__

#include "reflect/Class.h"

namespace reflect
{
	//! \brief Safe cast from one object, implementing relfect::ReflectionObject semantics to another
	//! \ingroup grpFreyaReflect
	template<class T, class U>
	T*     reflect_cast(U* obj) 
	{
		Class* lhs = T::GetClass(), *rhs = obj->getClass();
		if((lhs == rhs) || rhs->isSubClass(lhs))
			return static_cast<T*>(obj);
		return NULL;
	}
}

#endif // Reflect_reflect_cast_h__