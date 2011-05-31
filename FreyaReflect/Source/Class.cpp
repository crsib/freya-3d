/* File		: FreyaReflect: Class.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/Class.h"

namespace reflect
{
	uint32_t Class::reflection_class_idx = 0;

	reflect::property_ptr_t Class::getProperty( const core::string& name ) const
	{
		property_iterator_t it = m_Properties.find(name);
		if(it != m_Properties.end())
			return it->second;
		return property_ptr_t();
	}

	reflect::method_ptr_t Class::getMethod( const core::string& name ) const
	{
		method_iterator_t it =  m_Methods.find(name);
		if(it != m_Methods.end())
			return it->second;
		return method_ptr_t();
	}

} // namespace reflect
