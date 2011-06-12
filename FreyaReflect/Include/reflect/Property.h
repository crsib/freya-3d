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
	//! \brief High level representation of getters and setters
	//! \ingroup grpFreyaReflect
	class FREYA_REFLECT_EXPORT Property : public core::Object, public core::RefCountedBase
	{
	public:
		//! Constructs a property with name \a name
		Property(const core::string& name, bool readonly) : m_PropertyName(name), m_IsReadonly(readonly) {}
		//! Destructor
		virtual ~Property() {}
		//! Retrieves the name of the property
		const core::string& getName() const { return m_PropertyName; }
		//! Checks, if the property is read only
		bool                isReadonly() const { return m_IsReadonly; }
		//! Attempts to set the property value \a value on object \a this_ptr. Will have no effect on readonly properties
		bool                set( property_this_ptr_t this_ptr, const Value& value ) const
		{
			if(m_IsReadonly)
				return false;
			setValue(this_ptr,value);
			return true;
		}
		//! Retrieves the current property value from the object \a this ptr. This method is not thread safe
		Value               get( property_this_ptr_t this_ptr ) const { return getValue(this_ptr); } 
		
	protected:
		//! Re-implement this method to call the actual setter
		virtual void	setValue( property_this_ptr_t this_ptr, const Value& value ) const = 0;
		//! Re-implement this method to call the actual getter
		virtual Value	getValue( property_this_ptr_t this_ptr ) const = 0;
	private:
		core::string m_PropertyName;
		bool		 m_IsReadonly;

		// Make class non-copyable
		Property(const Property&);
		Property& operator = (const Property&);
	};
	//! Wrapper class to simplify the creation of custom properties
	/*!
	 * This class is a simple wrapper allowing to easily create custom properties.
	 * \tparam ValueType is a type of the value as returned by getter
	 * \tparam ClassType is an actual class type
	 * \tparam SetterType is a type, used in setter method
	 * \ingroup grpFreyaReflect
	 */
	template<typename ValueType, class ClassType, typename SetterType = ValueType>
	class PropertyImpl : public Property
	{
	public:
		//! Value type alias
		typedef ValueType value_type_t;
		//! Actual class type alias
		typedef ClassType class_type_t;
		//! Setter type alias
		typedef SetterType setter_type_t;
		//! Getter method pointer
		typedef value_type_t (class_type_t::*getter_t)() const;
		//! Setter method pointer
		typedef void (class_type_t::*setter_t)(setter_type_t);
		//! Constructs a readonly property
		PropertyImpl(const core::string& name,getter_t getter) : Property(name,true), m_Getter(getter), m_Setter(NULL) {}
		//! Construct a random access property
		PropertyImpl(const core::string& name,getter_t getter, setter_t setter) : Property(name,false), m_Getter(getter), m_Setter(setter) {}
	protected:
		//! Overloaded setValue implementation
		void	setValue( property_this_ptr_t this_ptr, const Value& value ) const 
		{ (reinterpret_cast<class_type_t*>(this_ptr)->*m_Setter)(value.get<value_type_t>()); }
		//! Overloaded getValue implemetation
		Value	getValue( property_this_ptr_t this_ptr ) const
		{ return Value((reinterpret_cast<class_type_t*>(this_ptr)->*m_Getter)()); }
	private:
		getter_t m_Getter;
		setter_t m_Setter;

		PropertyImpl(const PropertyImpl&);
		PropertyImpl& operator=(const PropertyImpl&);
	};
	//! Pointer to the Property
	//! \ingroup grpFreyaReflect
	typedef core::smart_ptr<Property, core::policies::ownership::Intrusive> property_ptr_t;
} // namespace reflect

#endif // Reflect_Property_h__