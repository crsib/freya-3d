/* File		: FreyaReflect: ReflectionModule.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_ReflectionModule_h__
#define Reflect_ReflectionModule_h__

#include "FreyaReflectInternal.h"
#include "core/Object.h"
#include "core/RefCountedBase.h"
#include "core/string.h"
#include "integer.h"

#include "reflect/ReflectionConsumer.h"

#include "core/smart_ptr.h"

namespace reflect
{
	class FREYA_REFLECT_EXPORT ReflectionModule : public core::Object, public core::RefCountedBase
	{
	public:
		virtual ~ReflectionModule() {}

		virtual bool	canReflectTo(const core::string& module) const = 0;
		virtual bool	canReflectTo(uint32_t consumer_id) const = 0;

		virtual bool	reflectTo(ReflectionConsumer* consumer) = 0;
	};

	typedef core::smart_ptr<ReflectionModule, core::policies::ownership::Intrusive> reflection_module_ptr_t;
} // namespace reflect

#endif // Reflect_ReflectionModule_h__