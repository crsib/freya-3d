/* File		: FreyaReflect: Value.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Value_h__
#define Reflect_Value_h__

#include "FreyaReflectInternal.h"
#include "core/Object.h"
#include "core/smart_ptr.h"
//#include "reflect/ReflectionObject.h"
#include "containers/type_utils.h"

namespace reflect
{
	class ReflectionObject;

	//! Wrapper class to contain value of the any copyable type
	/*!
	 * This class is a container to the any copy-constructible and copyable type.
	 * This class does not use any form of RTTI to check type safety of retrieving 
	 * the stored data and should be used carefully, as it can lead to undefined behavior
	 * of the application. The only exception is storing the raw pointer to the reflect::ReflectionObject.
	 * In this case, reflect::reflect_cast can guarantee the type safety of casting opertions
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT Value : public core::Object
	{
	public:
		//! Construct an empty Value
		Value() {}
		//! Copy constructor
		Value(const Value& rhs): m_StoredValue(rhs.m_StoredValue->clone()) {}
		//! Swaps the two values
		void swap(Value& rhs) { m_StoredValue.swap(rhs.m_StoredValue); }
		//! Assignment operator
		Value& operator = (const Value& rhs) { Value(rhs).swap(*this); return *this;}
		//! Checks, if the value does not store any data
		bool isEmpty() const { return !m_StoredValue; }

		//! Creates a Value, holding the object of type T
		template<typename T>
		Value(const T& val) : m_StoredValue(new ValueStorage<T>(val)) {}
		//! Checks, if the Value is a pointer to the reflect::ReflectionObject
		bool isReflectionObject() const { return !isEmpty() ? m_StoredValue->isReflectionObject() : false; }
		//! Retrieves the pointer to stored reflect::ReflectionObject or NULL, if the different data type is stored
		ReflectionObject* getReflectionObject() { return !isEmpty() ? m_StoredValue->getReflectionObject() : NULL; }
		//! Retrieves the stored data of type \a T. \b Warning: this operation is not type safe
		template<typename T>
		T get() { FREYA_REFLECT_ASSERT(!isEmpty(), "Trying to get an inexistant object"); return *reinterpret_cast<T*>(m_StoredValue->getOpaquePtr()); }
		//! Retrieves the stored data of type \a const \a T. \b Warning: this operation is not type safe
		template<typename T>
		typename containers::constant<T>::type 
			get() const { FREYA_REFLECT_ASSERT(!isEmpty(), "Trying to get an inexistant object"); return *reinterpret_cast<T const*>(m_StoredValue->getOpaquePtr()); }

	private:
		class FREYA_REFLECT_EXPORT ValueBase : public core::Object
		{
			bool     m_IsReflectionObject;
		public:
			ValueBase(bool reflection_object) 
				: m_IsReflectionObject(reflection_object) {}
			virtual ~ValueBase() {}
			virtual ValueBase* clone() const = 0;
			virtual void*      getOpaquePtr() = 0;
			virtual const void*getOpaquePtr() const = 0;
			ReflectionObject*  getReflectionObject() 
			{ return m_IsReflectionObject ? *reinterpret_cast<ReflectionObject**>(getOpaquePtr()) : NULL; }
			const ReflectionObject*  getReflectionObject() const
			{ return m_IsReflectionObject ? *reinterpret_cast<ReflectionObject* const *>(getOpaquePtr()) : NULL; }
			bool               isReflectionObject() const { return m_IsReflectionObject; }
		};//ValueBase

		template<typename T>
		class ValueStorage : public ValueBase
		{
			T       m_StoredValue;
		public:
			ValueStorage(typename containers::const_reference<T>::type value) : ValueBase(false), m_StoredValue(value) {}
			ValueStorage(const ValueStorage& rhs) : ValueBase(false), m_StoredValue(rhs.m_StoredValue) {}

			ValueStorage* clone() const
			{
				return new ValueStorage(m_StoredValue);
			}

			void*         getOpaquePtr() { return reinterpret_cast<void*>(&m_StoredValue); }
			const void*   getOpaquePtr() const { return reinterpret_cast<const void*>(&m_StoredValue); }
		};

		template<>
		class ValueStorage<ReflectionObject*> : public ValueBase
		{
			ReflectionObject*	m_StoredValue;
		public:
			ValueStorage(ReflectionObject* value) : ValueBase(true), m_StoredValue(value) {}
			ValueStorage(const ValueStorage& rhs) : ValueBase(true), m_StoredValue(rhs.m_StoredValue) {}

			ValueStorage* clone() const
			{
				return new ValueStorage(m_StoredValue);
			}

			void*         getOpaquePtr() { return reinterpret_cast<void*>(&m_StoredValue); }
			const void*   getOpaquePtr() const { return reinterpret_cast<const void*>(&m_StoredValue); }
		}; //

		core::smart_ptr<ValueBase,core::policies::ownership::Scoped>  m_StoredValue;
	}; // class Value
} // namespace reflect

#endif // Reflect_Value_h__