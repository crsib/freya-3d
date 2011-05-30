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
#include "reflect/ReflectionObject.h"
#include "containers/type_utils.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT Value : public core::Object
	{
	public:
		Value() {}
		Value(const Value& rhs): m_StoredValue(rhs.m_StoredValue->clone()) {}

		void swap(Value& rhs) { m_StoredValue.swap(rhs.m_StoredValue); }

		Value& operator = (const Value& rhs) { Value(rhs).swap(*this); return *this;}

		bool isEmpty() const { return !m_StoredValue; }

		//template<typename T>
		//Value(typename containers::reference<T>::type val) : m_StoredValue(new ValueStorage<T>(val)) {}

		template<typename T>
		Value(const T& val) : m_StoredValue(new ValueStorage<T>(val)) {}

		bool isReflectionObject() const { return !isEmpty() ? m_StoredValue->isReflectionObject() : false; }

		ReflectionObject* getReflectionObject() { return !isEmpty() ? m_StoredValue->getReflectionObject() : NULL; }

		template<typename T>
		T get() { FREYA_REFLECT_ASSERT(!isEmpty(), "Trying to get an inexistant object"); return *reinterpret_cast<T*>(m_StoredValue->getOpaquePtr()); }
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
			ReflectionObject*  getReflectionObject() 
			{ return m_IsReflectionObject ? *reinterpret_cast<ReflectionObject**>(getOpaquePtr()) : NULL; }
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
		}; //

		core::smart_ptr<ValueBase,core::policies::ownership::Scoped>  m_StoredValue;
	}; // class Value
} // namespace reflect

#endif // Reflect_Value_h__