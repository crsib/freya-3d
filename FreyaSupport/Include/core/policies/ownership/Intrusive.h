/* File		: core/policies/ownership/Intrusive.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef SmartPtr_Intrusive_h__
#define SmartPtr_Intrusive_h__

namespace core
{
	namespace policies
	{
		namespace ownership
		{
			//! Ownership policy implementing the reference counted policy with reference counter provided by the stored class
			/*!
			 * This policy implies, that the stored object has the following methods:
			 *  - \b void \b retain() - increments the reference counter by 1
			 *  - \b void \b release() - decrements the reference conter by 1. Destoys the object, if reference counter reaches 0
			 * \sa core::RefCountedBase
			 * \ingroup SmartPointers_Policies_Ownership
			 */
			template<class P>
			class	Intrusive
			{
			public:
				//! Default constructor
				Intrusive() {}
				//! Copy constructor
				Intrusive(const Intrusive& ) {}
				//! Copy constructor
				template<class U>
				Intrusive(const Intrusive<U>& ){}
				
				//! Swap the policies
				void	swap(Intrusive& ) {}
			protected:
				//! Increase owner ship level
				P	clone(const P& val)
				{
					if(val)
						val->retain();
					return val;
				}
				//! Decrease owner ship level
				bool release(const P& val)
				{
					if(val)
						val->release();
					return false;
				}

				//! This policy does not follow destructive copy semantics
				enum { DestructiveCopy = false };
			};
		}
	}
}

#endif // Intrusive_h__