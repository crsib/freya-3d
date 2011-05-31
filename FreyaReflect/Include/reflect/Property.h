/* File		: FreyaReflect: Property.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Property_h__
#define Reflect_Property_h__

#include "FreyaReflectInternal.h"

#include "core/RefCountedBase.h"
#include "core/Object.h"
#include "core/string.h"
#include "core/smart_ptr.h"

#include "reflect/Value.h"

namespace reflect
{
	typedef void* property_this_ptr_t;

	class FREYA_REFLECT_EXPORT Property : public core::Object, public core::RefCountedBase
	{
	public:
		Property(const core::string& name, bool readonly) : m_PropertyName(name), m_IsReadonly(readonly) {}
		virtual ~Property() {}

		const core::string& getName() const { return m_PropertyName; }
		bool                isReadonly() const { return m_IsReadonly; }

		bool                set( property_this_ptr_t this_ptr, const Value& value ) const
		{
			if(m_IsReadonly)
				return false;
			setValue(this_ptr,value);
			return true;
		}

		Value               get( property_this_ptr_t this_ptr ) const { return getValue(this_ptr); } 
		
	protected:
		virtual void	setValue( property_this_ptr_t this_ptr, const Value& value ) const = 0;
		virtual Value	getValue( property_this_ptr_t this_ptr ) const = 0;
	private:
		core::string m_PropertyName;
		bool		 m_IsReadonly;

		// Make class non-copyable
		Property(const Property&);
		Property& operator = (const Property&);
	};

	template<typename ValueType, class ClassType, typename SetterType = ValueType>
	class PropertyImpl : public Property
	{
	public:
		typedef ValueType value_type_t;
		typedef ClassType class_type_t;
		typedef SetterType setter_type_t;
		typedef value_type_t (class_type_t::*getter_t)() const;
		typedef void (class_type_t::*setter_t)(setter_type_t);

		PropertyImpl(const core::string& name,getter_t getter) : Property(name,true), m_Getter(getter), m_Setter(NULL) {}
		PropertyImpl(const core::string& name,getter_t getter, setter_t setter) : Property(name,false), m_Getter(getter), m_Setter(setter) {}
	protected:
		void	setValue( property_this_ptr_t this_ptr, const Value& value ) const 
		{ (reinterpret_cast<class_type_t*>(this_ptr)->*m_Setter)(value.get<value_type_t>()); }
		Value	getValue( property_this_ptr_t this_ptr ) const
		{ return Value((reinterpret_cast<class_type_t*>(this_ptr)->*m_Getter)()); }
	private:
		getter_t m_Getter;
		setter_t m_Setter;

		PropertyImpl(const PropertyImpl&);
		PropertyImpl& operator=(const PropertyImpl&);
	};

	typedef core::smart_ptr<Property, core::policies::ownership::Intrusive> property_ptr_t;
} // namespace reflect

#endif // Reflect_Property_h__