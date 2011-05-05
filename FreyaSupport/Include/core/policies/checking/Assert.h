/* File		: core/policies/checking/Assert.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef SmartPtr_Assert_h__
#define SmartPtr_Assert_h__

#include "FreyaSupportInternal.h"

namespace core
{
	namespace policies
	{
		namespace checking
		{
			template<class P>
			class Assert
			{
			public:
				Assert() {}
				Assert(const Assert& ) {}
				template<class U>
				Assert(const Assert<U>&) {}

				void	swap(Assert&) {}
			protected:
				void	check(P val)
				{
					assert(val); (void) val;
				}
			};
		}
	}
}

#endif // Assert_h__