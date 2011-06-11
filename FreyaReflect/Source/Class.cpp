/* File		: FreyaReflect: Class.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/Class.h"
#include "reflect/ReflectionDatabase.h"
#include "core/Log.h"

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

	bool Class::isSubClass( const Class* base_class ) const
	{
		// 
		class_iterator_t it = m_Bases.find(base_class);
		if( it != m_Bases.end())
			return true;

		class_iterator_t end = m_Bases.end();

		for( it = m_Bases.begin(); it != end; ++it )
			 if((*it)->isSubClass(base_class))
				 return true;

		return false;
	}

	bool Class::isSuperClass( const Class* ancesstor_class ) const
	{
		// 
		class_iterator_t it = m_Ancesstors.find(ancesstor_class);
		if( it != m_Ancesstors.end())
			return true;

		class_iterator_t end = m_Ancesstors.end();

		for( it = m_Ancesstors.begin(); it != end; ++it )
			 if((*it)->isSuperClass(ancesstor_class)) 
				 return true;

		return false;
	}

	void Class::addBase( const core::string& scoped_name )
	{
		Class* base = ReflectionDatabase::GetInstance().getClass(scoped_name);
		if(!base )
		{
			DebugLog("Base class \"%s\" is not found. Adding to deferred lookup list", scoped_name.c_str());
			ReflectionDatabase::GetInstance().m_DeferredLookupTable.insert(containers::make_pair<const core::string,Class*>(scoped_name, this));
		}
		else
			addBase(base);
	}

} // namespace reflect
