/* File		: containers/policies/multithreading/AtomicLock.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_AtomicLock_h__
#define Containers_Policies_AtomicLock_h__

namespace containers
{
	namespace policies
	{
		namespace multithreading
		{

			class AtomicLock
			{

				static void		lock() throw() {}
				static void		unlock() throw() {}
			};

		}
	}
}

#endif // Containers_Policies_AtomicLock_h__