/* File		: FreyaReflect: Scope.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/Scope.h"

namespace reflect
{


	scope_ptr_t Scope::getChild( const core::string& name, bool recursive /*= true*/ ) const
	{
		// Try to find a name, as a local name
		const_child_iterator_t it = m_Children.find(name);
		
		if(it != m_Children.end())
			return it->second;

		//Separate the full name of this scope out
		core::string::range r = name.find(m_ScopeName);

		if(r.empty() && m_Parent) //Nope, scope name not found. Bail out
			return scope_ptr_t();

		// Remove {m_ScopeName}::
		core::string child_name = m_Parent ? name.substr(r.begin() + 2) : name;

		it = m_Children.find(child_name);
		//Scope found
		if(it != m_Children.end())
			return it->second;

		if(recursive)
		{
			//Actually, we will note use recursion))
			core::string current_child_name = child_name;
			// Const cast is safe here, as only reference counter will be modified
			scope_ptr_t	 current_child = scope_ptr_t(const_cast<Scope*>(this));

			while(true)
			{
				r = current_child_name.find("::");
				
				core::string local_name = !r.empty() ? current_child_name.substr(0,r.begin()) : current_child_name;

				child_storage_t& child_storage = current_child->m_Children;
				it = child_storage.find(local_name);
				if(it != child_storage.end())
				{
					if(r.empty())
						return it->second;
					else
					{
						current_child_name = current_child_name.substr(r.end());
						current_child = it->second;
					}
				}
				else //Failed to find the child
					return scope_ptr_t();
			} //while(true)
		}

		//Failed to find the child
		return scope_ptr_t();
	}

	core::string Scope::getFullScopeName() const
	{
		if(m_Parent)
			return m_Parent->getFullScopeName() + m_ScopeName;
		// Root node. Return nothing, abort recursion
		return core::string();
	}

} // namespace reflect
