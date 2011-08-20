/* File         : FreyaReflectBinary: ReflectedClass.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef ReflectedClass_h__
#define ReflectedClass_h__

#include "Base/ReflectedScope.h"

class CppNodeClass;

namespace base
{
	class ReflectedClass : public ReflectedScope
	{
		ReflectedClass(const ReflectedClass&);
		ReflectedClass& operator = (const ReflectedClass&);
	public:
		REFLECTED_ELEMENT();

		ReflectedClass(CppNodeClass* node);

	};
}

#endif // ReflectedClass_h__