/* File         : FreyaReflectBinary: ReflectedEnum.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "Base/ReflectedElement.h"
#include "CppTree/CppNode.h"

#ifndef ReflectedEnum_h__
#define ReflectedEnum_h__

namespace base
{
	class ReflectedEnum : public ReflectedElement
	{
	public:
		ReflectedEnum(CppNodeEnum* enum_) : ReflectedElement(enum_->getName()), m_Enum(enum_) {}
		CppNodeEnum*    getEnumNode () { return m_Enum; }
	private:
		CppNodeEnum*    m_Enum;

	};
}

#endif // ReflectedEnum_h__