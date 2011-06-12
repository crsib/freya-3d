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
	//! \brief Just an alias to reflect::Scope with ability to auto add namespace to the parent scope
	//! \ingroup grpFreyaReflect
	class FREYA_REFLECT_EXPORT Namespace : public reflect::Scope
	{
	public:
		//! Constructs a namespace with name \a name in scope \a parent_scope
		Namespace(const core::string& name, scope_ptr_t parent_scope) : Scope(NamespaceScope,name,parent_scope.get())
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}
	};
} // namespace reflect

#endif // Reflect_Namespace_h__