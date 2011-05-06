/* File		: core/policies/SmartPtrPolicies.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Core_SmartPtrPolicies_h__
#define Core_SmartPtrPolicies_h__

#include "core/policies/checking/Assert.h"

#include "core/policies/ownership/Intrusive.h"
#include "core/policies/ownership/RefCounted.h"
#include "core/policies/ownership/Scoped.h"

#include "core/policies/storage/Array.h"
#include "core/policies/storage/Default.h"

//! \defgroup SmartPointers Freya 3D Engine smart pointers support

//! \defgroup SmartPointers_Policies Policies, controlling the behaviour of smart pointers
//! \ingroup  SmartPointers

//! \defgroup SmartPointers_Policies_Checking Policies, controlling the nul pointer checking upon pointer dereferencing
//! \ingroup  SmartPointers_Policies

//! \defgroup SmartPointers_Policies_Storage Policies, controlling the storage details of pointers
//! \ingroup  SmartPointers_Policies

//! \defgroup SmartPointers_Policies_Ownership Policies, controlling the ownership rules between smart pointer and actual pointer
//! \ingroup SmartPointers_Policies

namespace core
{
	namespace policies
	{
		//! \brief Namespace, containing policies, which control the ownership rules between smart pointer and actual pointer
		//! \ingroup SmartPointers_Policies_Ownership
		namespace ownership {}
		//! \brief Namespace, containing policies, which control how the pointer is stored and destroyed
		//! \ingroup SmartPointers_Polices_Storage
		namespace storage {}
		//! \brief Namespace, containing policies, which provide error checking upon pointers dereferencing
		//! \ingroup SmartPointers_Policies_Checking
		namespace checking {}
	}
}


#endif // SmartPtrPolicies_h__