/* File		: FreyaReflect: Property.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_Property_h__
#define Reflect_Property_h__

#include "FreyaReflectInternal.h"

#include "core/RefCountedBase.h"
#include "core/Object.h"

#include "core/smart_ptr.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT Property : public core::Object, public core::RefCountedBase
	{

	};

	typedef core::smart_ptr<Property, core::policies::ownership::Intrusive> property_ptr_t;
} // namespace reflect

#endif // Reflect_Property_h__