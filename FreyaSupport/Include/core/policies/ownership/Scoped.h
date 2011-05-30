/* File		: core/policies/ownership/Scoped.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef SmartPtr_Scoped_h__
#define SmartPtr_Scoped_h__

namespace core
{
	namespace policies
	{
		namespace ownership
		{
			//! \brief Policy, implementing the ownership following destructive copy semantics 
			//! \ingroup SmartPointers_Policies_Ownership
			template<class P>
			class Scoped
			{
			public:
				//! Default constructor
				Scoped() {}
				//! Copy constructor
				Scoped(const Scoped& ) {}
				//! Copy constructor
				template<class U>
				Scoped(const Scoped<U>&) {}
				//! Swap policies
				void swap(Scoped&) 
				{}

			protected:
				//! Take the ownership over the pointer and release previous pointers ownership
				P clone(P& v)
				{
					P temp(v);
					v = NULL;
					return temp;
				}

				//! Release the ownership of the object an let the storage policy to destroy it
				bool release(const P& ){ return true;}
				//! This policy follows destructive copy semantics
				enum { DestructiveCopy = true };
			};
		}
	}
}

#endif // Scoped_h__