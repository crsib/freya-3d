/* File		: containers/policies/multithreading/NoLock.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Containers_Policies_NoLock_h__
#define Containers_Policies_NoLock_h__

namespace containers
{
	namespace policies
	{
		namespace multithreading
		{

			class NoLock
			{
			public:
				void		lock() const throw() 
				{
				}

				void		unlock() const throw() 
				{
				}
			};

		}
	}
}

#endif // Containers_Policies_NoLock_h__