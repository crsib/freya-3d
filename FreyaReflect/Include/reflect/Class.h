/* File		: FreyaReflect: Class.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Class_h__
#define Reflect_Class_h__

#include "reflect/Scope.h"
#include "integer.h"

namespace reflect
{
#define REFLECTION_CLASS() \
	static  uint32_t GetClassID() { static uint32_t __class_id = reflection_class_idx++; return __class_id; } \
	virtual uint32_t getClassID() const { return GetClassID(); }

	class ReflectionObject;

	class FREYA_REFLECT_EXPORT Class : public Scope
	{
	protected:
		static uint32_t reflection_class_idx;
		Class(const core::string& name, scope_ptr_t parent_scope) : Scope(ClassScope,name,parent_scope.get())
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}
	public:
		virtual ~Class() {}

		REFLECTION_CLASS();

		bool	isValidClass() const { return getClassID() != Class::GetClassID(); }
	};

} // namespace reflect

#endif // Reflect_Class_h__