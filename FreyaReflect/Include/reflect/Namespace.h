/* File		: FreyaReflect: Namespace.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Namespace_h__
#define Reflect_Namespace_h__

#include "reflect/Scope.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT Namespace : public reflect::Scope
	{
	public:
		Namespace(const core::string& name, scope_ptr_t parent_scope) : Scope(NamespaceScope,name,parent_scope.get())
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}
	};
} // namespace reflect

#endif // Reflect_Namespace_h__