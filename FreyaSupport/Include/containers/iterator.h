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
	//! \brief Type trait to check, if the iterator is a random access iterator
	//! \ingroup grpContainers
	struct	random_access_iterator_tag {};
	//! \brief Type trait to check, if the iterator is a forward iterator
	//! \ingroup grpContainers
	struct  forward_iterator_tag {};
	//! \brief Type trait to check, if the iterator is a bidirectional iterator
	//! \ingroup grpContainers
	struct	bidirectional_iterator_tag {};

	//! \brief Retrieve the iterator traits
	//!\ingroup grpContainers
	template<typename T> 
	struct iterator_traits
	{
		//! Iterator base type
		typedef typename T::type base_type;
		//! Type of iterator
		/*!
		 * Type of iterator
		 * \sa containers::random_access_iterator_tag, containers::forward_iterator_tag, containers::bidirectional_iterator_tag
		 */
		typedef typename T::iterator_type iterator_type;
		typedef T self_type;
	};
	//!\cond
	template<typename T>
	struct iterator_traits<T*>
	{
		typedef T base_type;
		typedef random_access_iterator_tag iterator_type;
		typedef T* self_type;
	};
	//!\endcond
}

#endif // Containers_iterator_h__