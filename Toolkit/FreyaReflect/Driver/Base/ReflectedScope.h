/* File         : FreyaReflectBinary: ReflectedScope.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef ReflectedScope_h__
#define ReflectedScope_h__

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <string>

#include "Base/ReflectedElement.h"

class CppNode;

namespace base
{
	class ReflectedScope;

	typedef boost::shared_ptr<ReflectedScope> reflected_scope_ptr;

	class ReflectedScope : public ReflectedElement
	{
		typedef boost::unordered_map<std::string,reflected_element_ptr> child_map_t;
	public:
		REFLECTED_ELEMENT();
		typedef child_map_t::const_iterator child_const_iterator_t;

		ReflectedScope(const std::string& name, CppNode* node) : ReflectedElement(name, node) {}

		child_const_iterator_t  begin() const { return m_ChildMap.begin(); }
		child_const_iterator_t  end()   const { return m_ChildMap.end();   }

		void                    addChild(const reflected_element_ptr& ptr) 
		{
			m_ChildMap[ptr->getElementName()] = ptr;
			ptr->setParent(this);
		}

		reflected_element_ptr  getChild(const std::string& name) const;

		std::string            getScopedName() const;
	private:
		child_map_t       m_ChildMap;
	};
}

#endif // ReflectedScope_h__