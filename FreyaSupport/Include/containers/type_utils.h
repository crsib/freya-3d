/* File		: containers/type_utils.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_type_utils_h__
#define Containers_type_utils_h__

namespace containers
{
	//! Make a constant reference type
	template<class T> 
	struct	const_reference { typedef const T& type; };
	//! Make a constant reference type
	template<class  T>
	struct const_reference<const T> { typedef const T& type;	};
	//! Make a constant reference type
	template<class  T>
	struct const_reference<const T&> { typedef const T& type; };
	//! Make a constant reference type
	template<class  T>
	struct const_reference<T&> { typedef const T& type; };
	//! Make a constant pointer type
	template<class T> 
	struct	const_pointer { typedef const T* type; };
	//! Make a constant pointer type
	template<class  T>
	struct const_pointer<const T> { typedef const T* type;	};
	//!Make constant from a type
	template<class T>
	struct constant { typedef const T type; }; 
	//!Make constant from a type
	template<class T>
	struct constant<const T> { typedef const T type; }; 
	//!Drop constant qualifier
	template<class T>
	struct drop_const { typedef T type; };
	//!Drop constant qualifier
	template<class T>
	struct drop_const<const T> { typedef T type; };

	//! Select one of two types
	template<typename T1, typename T2, bool s> struct select_type;
	//! Select one of two types
	template<typename T1, typename T2>
	struct select_type<T1,T2,true> { typedef T1 type; };
	//! Select one of two types
	template<typename T1, typename T2>
	struct select_type<T1,T2,false> { typedef T2 type; };
}

#endif // type_utils_h__