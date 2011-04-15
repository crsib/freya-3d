/* File		: /atomic/memory_order.h
 * Author	: V. Sverchinsky
 * E-Mail	: vitalii.sverchinsky@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef FREYA_MEMORY_ORDER_H_
#define FREYA_MEMORY_ORDER_H_

namespace atomic
{
	/// \brief This enumeration provides values to use with atomic::load and atomic::store
	enum MemoryOrder
	{
		MemoryOrderSequential,		///< Loads and Stores could not be reordered.
		MemoryOrderAcquire,			///< Load operations follows the acquire semantics
		MemoryOrderRelease,			///< Store operations follows the release semantics.
		MemoryOrderRelaxed			///< Loads and Stores could be reordered.
	};
}


#endif//FREYA_MEMORY_ORDER_H_