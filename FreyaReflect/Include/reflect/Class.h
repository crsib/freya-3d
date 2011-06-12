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
	//! Meta class object
	/*!
	 * This class provides access to meta information of the C++ class.
	 * This contains the following information about the class:
	 *  - Name
	 *  - Properties
	 *  - Methods
	 *  - Base classes
	 *  - Inherited classes
	 *  - Enclosing scope
	 *
	 * This class is non copyable. It's lifetime is managed by reflect::ReflectionDatabase. It is gaurunteed,
	 * that equality of types, represented by this class, means equality of pointers to the meta classes (i.e. there
	 * is only one Class created per actual class).
	 *
	 * It is important, that both method and property lookup will traverse the whole hierarchy if the class does not
	 * contain the specific method/property itself. It helps to reduce the generated code base, but makes difficult to
	 * list all the class methods/properties
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT Class : public Scope
	{
		friend class ReflectionDatabase;
	protected:
		//! Last unused index to identify the Class
		static uint32_t reflection_class_idx;
		//! {property name}->reflect::Property map. This map should be filled by ancestors
		typedef containers::hash_map
			<
			core::string, property_ptr_t,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> property_map_t;
		//! {method signature}->reflect::Method map. This map should be filled by ancestors
		typedef containers::hash_map
			<
			core::string, method_ptr_t,
			containers::hash<const core::string>,
			containers::equal<const core::string>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> method_map_t;
		//! Set of classes. This is used as storage for both base and inherited classes.
		typedef containers::hash_set
			<
			const Class*,
			containers::hash<const Class*>,
			containers::equal<const Class*>,
			containers::policies::rehash::PrimeNumber,
			containers::policies::memory::FreyaAllocator, 
			containers::policies::multithreading::AtomicLock
			> class_set_t;
		//! Class properties
		property_map_t       m_Properties;
		//! Class methods
		method_map_t		 m_Methods;
		//! Base classes
		class_set_t          m_Bases;
		//! Inherited classes
		class_set_t          m_Ancesstors;	
		//! Create a Class object
		/*!
		 * Create a Class object in \a parent_scope. Class will be added to scope automatically.
		 * \param name is a name of described class
		 * \param parent_scope is a scope to add the class to
		 */
		Class(const core::string& name, scope_ptr_t parent_scope) : Scope(ClassScope,name,parent_scope.get()), m_Bases(1.0f), m_Ancesstors(1.0f)
		{
			this->retain(); 
			parent_scope->addChild(scope_ptr_t(this));
		}
		//! Add a base class
		/*!
		 * Will attempt to add the base class to the class. If base class is not
		 * currently relfected to the reflect::ReflectionDatabase this method will
		 * add the base to the database list and the database will resolve it
		 * as the required class is loaded. This behavior is required, as the order
		 * of global objects construction is undefined. This will both add base class
		 * to the current class and register current class as ancestor of base.
		 * This method should be called by inherited classes in order to register
		 * it's bases.
		 * \param scoped_name is a scoped name of the class (i.e. namespace::ClassName)
		 */
		void	addBase(const core::string& scoped_name);
		//! Property map iterator
		typedef property_map_t::const_iterator property_iterator_t;
		//! Method map iterator
		typedef method_map_t::const_iterator   method_iterator_t;
	public:
		//! Class set iterator
		typedef class_set_t::const_iterator          class_iterator_t;
		//! Destructor
		virtual ~Class() {}
		//! Macro, used to create a valid class ID
		/*!
		 * This macro will "generate" the valid ID for the class by adding
		 * two implemented methods:
		 *  - static GetClassID() 
		 *  - virtual getClassID()
		 *
		 * Both methods are returning unsigned integer values, uniquely describing
		 * the Class. Inherited class should include this macro in order to make 
		 * reflection system to function properly.
		 */
		REFLECTION_CLASS();
		//! Checks, if Class is actually representing a class
		bool	            isValidClass() const { return getClassID() != Class::GetClassID(); }
		//! Checks, if the class has a property named \a name
		bool                hasProperty(const core::string& name) const { return !!getProperty(name); }
		//! Returns reflect::Property pointer to the property named \a name or a NULL pointer if no such property exists
		property_ptr_t      getProperty(const core::string& name) const;
		//! Checks, if the class has a method with signature \a signature. See reflect::Method for details on signature format
		bool                hasMethod(const core::string& signature) const { return !!getMethod(signature); }
		//! Returns reflect::Method pointer to the method with signature \a signature or a NULL pointer if no such signature exists
		method_ptr_t		getMethod(const core::string& signature) const;
		//! Returns an iterator, pointing to the first base class
		class_iterator_t	basesBegin() const { return m_Bases.begin(); }
		//! Return an iterator, pointing past the last base class
		class_iterator_t    basesEnd() const { return m_Bases.end(); }
		//! Returns an iterator, pointing to the first ancestor class
		class_iterator_t    ancesstorsBegin() const { return m_Ancesstors.begin(); }
		//! Return an iterator, pointing past the last ancestor class
		class_iterator_t    ancesstorsEnd() const { return m_Ancesstors.end(); }
		//! Checks, if the class is inherited from \abase_class
		bool                isSubClass(const Class* base_class) const;
		//! Checks, if the class is a base class to \a ancestor_class
		bool                isSuperClass(const Class* ancestor_class) const;
		//! Factory, to create a class, inherited from relfect::ReflectionObject.
		/*!
		 * This method should be reimplemented by the inherited class for every class,
		 * inherited from reflect::ReflectionObject. It should create the actual class,
		 * described by this one.
		 */
		virtual ReflectionObject* create() const { return NULL; }

	private:
		void	addBase(Class* base);
	};

} // namespace reflect

#endif // Reflect_Class_h__