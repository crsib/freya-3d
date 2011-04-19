/* File		: containers/policies/Policies.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Container_Policies_h__
#define Container_Policies_h__

#include "containers/policies/memory/FreyaAllocator.h"
#include "containers/policies/memory/Malloc.h"
#include "containers/policies/memory/New.h"

#include "containers/policies/multithreading/AtomicLock.h"
#include "containers/policies/multithreading/NoLock.h"

#include "containers/policies/storage/Exponential.h"
#include "containers/policies/storage/FixedSize.h"
#include "containers/policies/storage/Greedy.h"

//! \defgroup grpContainers Freya 3D Engines generic containers

//! \brief This namespace contains interfaces to Freya 3D Engines generic containers
//! \ingroup grpContainers
namespace containers
{
	//! \defgroup grpContainers_Policies Policies, controlling Freya 3D Engine containers
	//! \ingroup grpContainers

	//! \brief This namespace contains various policies to control the behavior of Freya 3D Engines containers
	//! \ingroup grpContainers_Policies
	namespace policies
	{
		//! \defgroup grpContainers_Policies_Memory Memory management related policies
		//! \ingroup grpContainers_Policies

		//! \brief Memory management related policies interfaces
		//! \ingroup grpContainers_Policies_Memory
		namespace memory {}

		//! \defgroup grpContainers_Policies_MultiThreading Thread safety  policies
		//! \ingroup grpContainers_Policies

		//! \brief Thread safety policies interfaces
		//! \ingroup grpContainers_Policies_MultiThreading
		namespace multithreading {}

		//! \defgroup grpContainers_Policies_Storage Storage expansion policies
		//! \ingroup grpContainers_Policies

		//! \brief Storage expansion policies interfaces
		//! \ingroup grpContainers_Policies_Storage
		namespace storage {}
	}
}

#endif // Policies_h__