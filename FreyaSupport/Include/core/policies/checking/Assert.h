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
			//! \brief Dereference error checking policy based on assert macro
			//! \ingroup SmartPointers_Policies_Checking
			template<class P>
			class Assert
			{
			public:
				//! Default constructor
				Assert() {}
				//! Copy constructor
				Assert(const Assert& ) {}
				//! Copy constructor accepting implicitly castable to base types
				template<class U>
				Assert(const Assert<U>&) {}
				//! Swap policies
				void	swap(Assert&) {}
			protected:
				//! Check the pointer correctness
				void	check(P val)
				{
					FREYA_SUPPORT_ASSERT(val,"NULL pointer dereferencing"); (void) val;
				}
			};
		}
	}
}

#endif // Assert_h__