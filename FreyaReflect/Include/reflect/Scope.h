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

	typedef core::smart_ptr<Scope, core::policies::ownership::Intrusive> scope_ptr_t;

	class FREYA_REFLECT_EXPORT Scope : public core::Object, public core::RefCountedBase
	{
		typedef	 containers::hash_map<core::string,scope_ptr_t> child_storage_t;
	public:
		virtual ~Scope() {}

		enum	ScopeType
		{
			NamespaceScope,
			ClassScope
		};

		typedef  child_storage_t::iterator	         child_iterator_t;
		typedef	 child_storage_t::const_iterator     const_child_iterator_t;

		const core::string&      getScopeName() const { return m_ScopeName; }
		core::string			 getFullScopeName() const;

		ScopeType                getScopeType() const { return m_ScopeType; }

		child_iterator_t         begin()              { return m_Children.begin(); }
		const_child_iterator_t   begin() const        { return m_Children.begin(); }

		child_iterator_t         end()                { return m_Children.end(); }
		const_child_iterator_t   end() const          { return m_Children.end(); }

		scope_ptr_t              getChild(const core::string& name, bool recursive = true) const;

		scope_ptr_t				 getFirstChild() const { return m_Children.begin()->second; }
		
		size_t                   getChildrenCount() const { return m_Children.size(); }
	protected:
		Scope(ScopeType scope_type, const core::string& scope_name, Scope* parent) 
			: m_ScopeName(scope_name), m_ScopeType(scope_type), m_Parent(parent) {}	
	private:
		core::string				m_ScopeName;
		ScopeType                   m_ScopeType;

		Scope*						m_Parent;
		child_storage_t             m_Children;
	};
} // namespace reflect

#endif // Reflect_Scope_h__