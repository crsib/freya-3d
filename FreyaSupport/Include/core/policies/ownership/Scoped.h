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
			template<class P>
			class Scoped
			{
			public:
				Scoped() {}
				Scoped(const Scoped& ) {}
				template<class U>
				Scoped(const Scoped<U>&) {}

				enum { DestructiveCopy = true };

				void swap(const Scoped&) {}
			protected:
				P clone(P& v)
				{
					P temp(v);
					v = NULL;
					return temp;
				}

				bool release(const P& ){ return true;}
			};
		}
	}
}

#endif // Scoped_h__