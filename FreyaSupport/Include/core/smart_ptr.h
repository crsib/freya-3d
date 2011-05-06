/* File		: core/smart_ptr.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Core_smart_ptr_h__
#define Core_smart_ptr_h__

#include "core/policies/SmartPtrPolicies.h"
#include "containers/type_utils.h"

namespace core
{
	//! Policy based smart pointer implementation
	/*!
	 * Smart pointers are objects, exposing some semantics of the generic pointer
	 * along with controlling the lifetime of an owned object. Smart pointers could
	 * not be used in pointer arithmetics or as iterators. This class template provides
	 * a flexible implementation of smart pointer concept using policies to control
	 * ownership, storage and error checking aspects. Please note, that there is a 
	 * public \b pointer_type_t \b get() method exposed by storage policy, which could
	 * be used to retrieve the raw pointer to the stored data. Still, it is completely user 
	 * responsibility to assure, that life time management is not interfered by usage of such a
	 * raw pointer. More over, in most cases user should assure, that there is no link dependencies 
	 * between two objects, stored in smart pointer (i.e object A stores smart pointer to object B and vice versa).
	 * Default policies are implementing behaviour, similar to boost::shared_ptr, yet without shared_from_this concept.
	 * <BR><BR>
	 * The smart_ptr is controlled by the following policies:
	 *  - \b OwnershipPolicy controls the actual life time management. \ref SmartPointers_Policies_Ownership
	 *  - \b StoragePolicy controls the actual storage of the owned object and its destruction. Ownership policy is used, to
	 *     determine when to destruct an object. \ref SmartPointers_Policies_Storage
	 *  - \b CheckingPolicy controls the error checking upon stored pointer dereferencing. \ref SmartPointers_Policies_Checking
	 * <BR>
	 * \tparam T is a type of stored object
	 * \tparam OwnershipPolicy is a class template implementing ownership policy
	 * \tparam StoragePolicy is a class template implementing storage policy
	 * \tparam CheckingPolicy is a class template implementing checking policy
	 * \ingroup SmartPointers
	 */
	template
	<
		typename T,
		template<class> class OwnershipPolicy = policies::ownership::RefCounted,
		template<class> class StoragePolicy = policies::storage::Default,
		template<class> class CheckingPolicy = policies::checking::Assert
	>
	class smart_ptr :
		public StoragePolicy<T>,
		public OwnershipPolicy<typename StoragePolicy<T>::pointer_type_t>,
		public CheckingPolicy<typename StoragePolicy<T>::pointer_type_t>
	{
		template
		<
			typename U,
			template<class> class OP,
			template<class> class SP,
			template<class> class CP
		>
		friend class smart_ptr;

		typedef StoragePolicy<T> storage_policy_t;
		typedef OwnershipPolicy<typename StoragePolicy<T>::pointer_type_t> ownership_policy_t;
		typedef CheckingPolicy<typename StoragePolicy<T>::pointer_type_t>  checking_policy_t;

		struct never_matched
		{
			never_matched(int) {}
			void foo() {}
		};

	public:
		//! Type of the stored object
		typedef typename storage_policy_t::base_type_t              base_type_t;
		//! Type of the pointer to the stored object
		typedef typename storage_policy_t::pointer_type_t           pointer_type_t;
		//! Type of the constant pointer to the stored object
		typedef typename storage_policy_t::const_pointer_type_t		const_pointer_type_t;
		//! Type of the reference to the stored object
		typedef typename storage_policy_t::reference_type_t			reference_type_t;
		//! Type of the constant reference to the stored object
		typedef typename storage_policy_t::const_reference_type_t	const_reference_type_t;
		//! Type of argument, used in copy constructor and operator =
		typedef typename containers::select_type<smart_ptr,const smart_ptr,ownership_policy_t::DestructiveCopy>::type copy_arg_t;
		//! Analogue of boolean type to be used to enable \a if(sp)
		typedef void (never_matched::*unspecified_boolean_t)();
		//! Default constructor. Policies are in charge of correct initialization
		smart_ptr() {}
		//! Constructor, initializing smart pointer with specific raw pointer. Ownership over the pointer is aquired accordin to ownership policy
		explicit smart_ptr(const pointer_type_t& val) : storage_policy_t(val) {}
		//! Copy constructor. When ownership follows destructive copy semantics (same as std::auto_ptr does) the value of \a rhs could possibly be modified
		smart_ptr( copy_arg_t& rhs ) : storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef() = clone(rhs.getRef());
		}
		//! Copy constructor to allow handling the pointer ownership by the smart pointers with implicitly castable base type
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr( const smart_ptr<U, SP, OP, CP>& rhs) : storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef() = clone(rhs.getRef());
		}
		//! Copy constructor to allow handling the pointer ownership by the smart pointers with implicitly castable base type (version for destructive copy ownership)
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr( smart_ptr<U, SP, OP, CP>& rhs) :  storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef() = clone(rhs.getRef());
		}
		//! Swap to smart pointers
		void	swap(smart_ptr& rhs)
		{
			storage_policy_t::swap(rhs);
			ownership_policy_t::swap(rhs);
			checking_policy_t::swap(rhs);
		}
		//! Overloaded assignment operator
		smart_ptr& operator = (copy_arg_t& rhs)
		{
			smart_ptr temp(rhs);
			temp.swap(*this);
			return *this;
		}
		//! Overloaded assignment operator to allow handling the pointer ownership by the smart pointers with implicitly castable base type
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr& operator = (const smart_ptr<U,SP,OP,CP>& rhs)
		{
			smart_ptr temp(rhs);
			temp.swap(*this);
			return *this;
		}
		//! Overloaded assignment operator to allow handling the pointer ownership by the smart pointers with implicitly castable base type
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr& operator = ( smart_ptr<U,SP,OP,CP>& rhs)
		{
			smart_ptr temp(rhs);
			temp.swap(*this);
			return *this;
		}
		//! Reset smart pointer ownership on the object
		void	reset()
		{
			if(release(getRef()))
				destroy();
			getRef() = default();
		}
		//! Smart pointer destructor, calling \a reset() for correct ownership managment 
		~smart_ptr() { reset(); }
		//! Retrieve the stored pointer
		pointer_type_t	operator -> () { check(getRef()); return get(); }
		//! Retrieve constant version of the stored pointer
		const_pointer_type_t operator -> () const { check(getRef());  return get(); }
		//! Dereference operator
		reference_type_t operator * () { check(getRef()); return *get(); }
		//! Constant dereference operator
		const_reference_type_t operator * () const { check(getRef()); return *get(); }
		//! Enables \a if(!sp)
		bool	operator! () const { return get() == default(); }
		//! Equality operator
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		bool	operator == (const smart_ptr<U,SP,OP,CP>& rhs) const { return get() == rhs.get(); }
		//! Inequality operator
		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		bool	operator != (const smart_ptr<U,SP,OP,CP>& rhs) const { return get() != rhs.get(); }
		//! Enables if(sp)
		operator unspecified_boolean_t () const { return get() == default() ? NULL : &never_matched::foo; }
	};
}

#endif // smart_ptr_h__