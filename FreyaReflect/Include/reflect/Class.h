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
#include "containers/hash_set.h"
#include "containers/policies/Policies.h"

#include "reflect/Scope.h"
#include "reflect/Property.h"
#include "reflect/Method.h"

namespace reflect
{
#define REFLECTION_CLASS() \
	static  uint32_t GetClassID() { static uint32_t __class_id = reflection_class_idx++; return __class_id; } \
	virtual uint32_t getClassID() const { return GetClassID(); }

	class ReflectionObject;

	class FREYA_REFLECT_EXPORT Class : public Scope
	{
		friend class ReflectionDatabase;
	protected:
		static uint32_t reflection_class_idx;
		
		typedef containers::hash_map
			<
			core::string, property_ptr_t,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> property_map_t;

		typedef containers::hash_map
			<
			core::string, method_ptr_t,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> method_map_t;

		typedef containers::hash_set
			<
			const Class*,
			containers::hash<const Class*>,
			containers::equal<const Class*>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> class_set_t;

		property_map_t       m_Properties;
		method_map_t		 m_Methods;

		class_set_t          m_Bases;
		class_set_t          m_Ancesstors;	

		Class(const core::string& name, scope_ptr_t parent_scope) : Scope(ClassScope,name,parent_scope.get()), m_Bases(1.0f), m_Ancesstors(1.0f)
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}

		void	addBase(Class* base);

		void	addBase(const core::string& scoped_name);
	public:
		typedef property_map_t::const_iterator property_iterator_t;
		typedef method_map_t::const_iterator   method_iterator_t;

		typedef class_set_t::const_iterator          class_iterator_t;

		virtual ~Class() {}

		REFLECTION_CLASS();

		bool	            isValidClass() const { return getClassID() != Class::GetClassID(); }

		bool                hasProperty(const core::string& name) const { return !!getProperty(name); }
		property_ptr_t      getProperty(const core::string& name) const;

		bool                hasMethod(const core::string& name) const { return !!getMethod(name); }
		method_ptr_t		getMethod(const core::string& signature) const;

		class_iterator_t	basesBegin() const { return m_Bases.begin(); }
		class_iterator_t    basesEnd() const { return m_Bases.end(); }

		class_iterator_t    ancesstorsBegin() const { return m_Ancesstors.begin(); }
		class_iterator_t    ancesstorsEnd() const { return m_Ancesstors.end(); }

		bool                isSubClass(const Class* base_class) const;
		bool                isSuperClass(const Class* ancesstor_class) const;

		bool                canBeCasted(const Class* cast_to) const { return (cast_to == this) || isSuperClass(cast_to) || isSubClass(cast_to); }

		virtual ReflectionObject* create() const { return NULL; }
	};

} // namespace reflect

#endif // Reflect_Class_h__