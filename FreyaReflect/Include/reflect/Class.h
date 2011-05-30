/* File		: FreyaReflect: Class.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Class_h__
#define Reflect_Class_h__

#include "FreyaReflectInternal.h"
#include "integer.h"

#include "core/string.h"

#include "containers/hash_map.h"
#include "containers/policies/Policies.h"

#include "reflect/Scope.h"
#include "reflect/Property.h"


namespace reflect
{
#define REFLECTION_CLASS() \
	static  uint32_t GetClassID() { static uint32_t __class_id = reflection_class_idx++; return __class_id; } \
	virtual uint32_t getClassID() const { return GetClassID(); }

	class ReflectionObject;

	class FREYA_REFLECT_EXPORT Class : public Scope
	{
	protected:
		static uint32_t reflection_class_idx;
		Class(const core::string& name, scope_ptr_t parent_scope) : Scope(ClassScope,name,parent_scope.get())
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}

		typedef containers::hash_map
			<
			core::string, property_ptr_t,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> property_map_t;

		property_map_t       m_Properties;
	public:
		typedef property_map_t::const_iterator property_iterator_t;

		virtual ~Class() {}

		REFLECTION_CLASS();

		bool	isValidClass() const { return getClassID() != Class::GetClassID(); }

		size_t              getPropertiesCount() const { return m_Properties.size(); }
		property_iterator_t propertiesBegin() const { return m_Properties.begin(); }
		property_iterator_t propertiesEnd() const { return m_Properties.end(); }

		property_ptr_t      getProperty(const core::string& name) const;
	};

} // namespace reflect

#endif // Reflect_Class_h__