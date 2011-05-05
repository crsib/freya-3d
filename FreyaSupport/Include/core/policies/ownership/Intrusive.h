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
			template<class P>
			class	Intrusive
			{
			public:
				Intrusive() {}
				Intrusive(const Intrusive& ) {}
				template<class U>
				Intrusive(const Intrusive<U>& ){}

				enum { DestructiveCopy = false };

				void	swap(const Intrusive& ) {}
			protected:
				P	clone(const P& val)
				{
					if(val)
						val->retain();
					return val;
				}

				bool release(const P& val)
				{
					if(val)
						val->release();
					return false;
				}
			};
		}
	}
}

#endif // Intrusive_h__