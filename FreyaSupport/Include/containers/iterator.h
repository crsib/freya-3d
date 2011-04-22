/* File		: containers/iterator.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_iterator_h__
#define Containers_iterator_h__

namespace containers
{
	//!
	struct	random_access_iterator_tag {};
	//!
	struct  forward_iterator_tag {};
	//! 
	struct	bidirectional_iterator_tag {};

	//!
	template<typename T> 
	struct iterator_traits
	{
		typedef typename T::type base_type;
		typedef typename T::iterator_type iterator_type;
		typedef T self_type;
	};
	//!
	template<typename T>
	struct iterator_traits<T*>
	{
		typedef T base_type;
		typedef random_access_iterator_tag iterator_type;
		typedef T* self_type;
	};
}

#endif // Containers_iterator_h__