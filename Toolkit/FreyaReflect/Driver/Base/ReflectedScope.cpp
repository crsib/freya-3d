/* File         : FreyaReflectBinary: ReflectedScope.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "Base/ReflectedScope.h"

namespace base
{


	base::reflected_element_ptr ReflectedScope::getChild( const std::string& name ) const
	{
		child_const_iterator_t it = m_ChildMap.find(name);
		if(it != m_ChildMap.end())
			return it->second;
		return reflected_element_ptr();
	}

	std::string ReflectedScope::getScopedName() const
	{
		if(m_Parent)
		{
			if(m_Parent->m_Parent)
				return m_Parent->getScopedName() + "::" + m_Name;
			else
				return  m_Name;
		}
		return std::string();
	}

}