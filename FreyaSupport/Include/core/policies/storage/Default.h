/* File		: core/policies/storage/Default.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef SmartPtr_Default_h__
#define SmartPtr_Default_h__

#include "containers/type_utils.h"

namespace core
{
	namespace policies
	{
		namespace storage
		{
			//! \brief Default storage policy using NULL as default value and operator delete for destruction 
			template<typename T>
			class Default
			{
			public:
				//! Stored type base
				typedef T  base_type_t;
				//! Stored pointer type
				typedef T* pointer_type_t;
				//! Stored constant pointer type
				typedef typename containers::const_pointer<T>::type const_pointer_type_t;
				//! Reference to the base type
				typedef T& reference_type_t;
				//! Constant reference to the base type
				typedef typename containers::const_reference<T>::type const_reference_type_t;
				//! Initialize the pointer to the default value 
				Default() : m_Pointee(default()) {}
				//! Fake copy constructor. Data is initialized by ownership policy
				Default(const Default& ) : m_Pointee(NULL) {}
				//! Overloaded version of copy constructor to support storing pointers, which are implicitly castable to stored type
				template<typename U>
				Default(const Default<U>&) : m_Pointee(NULL) {}
				Default(const pointer_type_t& ptr) : m_Pointee(ptr) {}
				//! Retrieve stored pointer
				pointer_type_t get() { return m_Pointee; };
				//! Retrieve constant version of stored pointer
				const_pointer_type_t get() const { return m_Pointee; }
				//! Swap storages
				void	swap(Default& rhs)
				{
					pointer_type_t temp = rhs.m_Pointee;
					rhs.m_Pointee = m_Pointee;
					m_Pointee = temp;
				}
			protected:
				pointer_type_t&	getRef() { return m_Pointee; }
				const pointer_type_t& getRef() const { return m_Pointee; }
				//! Destroy an object
				void	destroy()
				{ delete m_Pointee;	}
				//! Default value for the pointer
				pointer_type_t default() const
				{ return NULL; }
			private:
				pointer_type_t m_Pointee;
			};
		}
	}
}

#endif // Default_h__