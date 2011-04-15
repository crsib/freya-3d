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

namespace containers
{
	namespace policies
	{

	}
}

#endif // Policies_h__