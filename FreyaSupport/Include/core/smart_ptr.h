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
	template
	<
		typename T,
		template<class> class StoragePolicy,
		template<class> class OwnershipPolicy,
		template<class> class CheckingPolicy
	>
	class smart_ptr :
		public StoragePolicy<T>,
		public OwnershipPolicy<typename StoragePolicy<T>::pointer_type_t>,
		public CheckingPolicy<typename StoragePolicy<T>::pointer_type_t>
	{
		template
		<
			typename T1,
			template<class> class StoragePolicy1,
			template<class> class OwnershipPolicy1,
			template<class> class CheckingPolicy1
		>
		friend class smart_ptr;

		typedef StoragePolicy<T> storage_policy_t;
		typedef OwnershipPolicy<typename StoragePolicy<T>::pointer_type_t> ownership_policy_t;
		typedef CheckingPolicy<typename StoragePolicy<T>::pointer_type_t>  checking_policy_t;

		struct never_matched
		{
			void foo() {}
		};

	public:
		typedef typename storage_policy_t::base_type_t              base_type_t;
		typedef typename storage_policy_t::pointer_type_t           pointer_type_t;
		typedef typename storage_policy_t::const_pointer_type_t		const_pointer_type_t;
		typedef typename storage_policy_t::reference_type_t				reference_type_t;
		typedef typename storage_policy_t::const_reference_type_t		const_reference_type_t;

		typedef typename containers::select_type<smart_ptr,const smart_ptr,ownership_policy_t::DestructiveCopy> copy_arg_t;

		typedef void (never_matched::*implicit_cast_t)();

		smart_ptr() {}

		explicit smart_ptr(const pointer_type_t& val) : storage_policy_t(val) {}

		smart_ptr( copy_arg_t& rhs ) : storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef() = clone(rhs.getRef());
		}

		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr( const smart_ptr<U, SP, OP, CP>& rhs) :  : storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef = clone(rhs.getRef());
		}

		template
		<
			typename U,
			template<class> class SP,
			template<class> class OP,
			template<class> class CP
		>
		smart_ptr( smart_ptr<U, SP, OP, CP>& rhs) :  : storage_policy_t(rhs), ownership_policy_t(rhs), checking_policy_t(rhs)
		{
			getRef = clone(rhs.getRef());
		}

		void	swap(smart_ptr& rhs)
		{
			storage_policy_t::swap(rhs);
			ownership_policy_t::swap(rhs);
			checking_policy_t::swap(rhs);
		}

		smart_ptr& operator = (copy_arg_t& rhs)
		{
			smart_ptr temp(rhs);
			temp.swap(*this);
			return *this;
		}

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

		void	reset()
		{
			if(release(getRef()))
				destroy();
		}

		~smart_ptr() { reset(); }
	};

	template<typename T>
	class shared_ptr : smart_ptr<T, policies::storage::Default, policies::ownership::RefCounted, policies::checking::Assert> {};
}

#endif // smart_ptr_h__