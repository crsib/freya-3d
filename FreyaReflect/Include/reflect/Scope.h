/* File		: FreyaReflect: Scope.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Scope_h__
#define Reflect_Scope_h__

#include "FreyaReflectInternal.h"
#include "core/Object.h"
#include "core/RefCountedBase.h"
#include "core/smart_ptr.h"
#include "core/string.h"
#include "containers/policies/Policies.h"
#include "containers/hash_map.h"

namespace reflect
{
	class Scope;
	class Namespace;
	class Class;
	//! \brief Pointer to the reflect::Scope
	//! \ingroup grpFreyaReflect
	typedef core::smart_ptr<reflect::Scope, core::policies::ownership::Intrusive> scope_ptr_t;
	
	//! C++ scope abstraction 
	/*!
	 * This class is a base for both reflect::Namespace and reflect::Class, providing 
	 * storage for child objects and functionality to retrieve the child object by its 
	 * name (possibly scoped).
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT Scope : public core::Object, public core::RefCountedBase
	{
		typedef	 containers::hash_map<core::string,scope_ptr_t> child_storage_t;
	public:
		//! Destructor
		virtual ~Scope() {}
		//! Type of the current scope
		enum	ScopeType
		{
			//! This scope is a namespace (reflect::Namespace)
			NamespaceScope,
			//! This scope is a class (reflect::Class)
			ClassScope
		};
		//! Iterator to the scopes child
		typedef  child_storage_t::iterator	         child_iterator_t;
		//! Constant iterator to the scopes child
		typedef	 child_storage_t::const_iterator     const_child_iterator_t;
		//! Retrieves the scopes name
		const core::string&      getName() const { return m_ScopeName; }
		//! Retrieves the scoped name of the scope without leading ::
		core::string			 getScopedName() const;
		//! Retrieves the current scope type
		ScopeType                getScopeType() const { return m_ScopeType; }
		//! Retrieves the first child iterator
		child_iterator_t         begin()              { return m_Children.begin(); }
		//! Retrieves the first child iterator (constant version)
		const_child_iterator_t   begin() const        { return m_Children.begin(); }
		//! Retrieves the one-past-last child iterator
		child_iterator_t         end()                { return m_Children.end(); }
		//! Retrieves the one-past-last child iterator (constant version)
		const_child_iterator_t   end() const          { return m_Children.end(); }

		//! Retrieves the child with name \a name (recursively, if \a recursive is true)
		scope_ptr_t              getChild(const core::string& name, bool recursive = true) const;

		//! Retrieves the first child of the scope
		scope_ptr_t				 getFirstChild() const { return m_Children.begin()->second; }
		//! Retrieves number of children
		size_t                   getChildrenCount() const { return m_Children.size(); }
	protected:
		//! Create a scope named \a scope_name in parent scope \a parent
		Scope(ScopeType scope_type, const core::string& scope_name, Scope* parent) 
			: m_ScopeName(scope_name), m_ScopeType(scope_type), m_Parent(parent) {}	
		//! Add a child to the scope
		void					addChild(const scope_ptr_t& child) { m_Children[child->getName()] = child; }
	private:
		core::string				m_ScopeName;
		ScopeType                   m_ScopeType;

		Scope*						m_Parent;
		child_storage_t             m_Children;

		friend class Namespace;
		friend class Class;
	};
} // namespace reflect

#endif // Reflect_Scope_h__