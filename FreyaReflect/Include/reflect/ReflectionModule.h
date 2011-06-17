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
	//! Module, containing reflection data
	/*!
	 * This class manages the reflection process. It allows to reflect data to a specified ReflectionConsumer
	 * in a safe way along as a way to check, if this module supports the specific reflection consumer.
	 * For debugging reasons mostly, a module is identified by a name. This name is not used internally for any purpose.
	 * \ingroup grpFreyaReflect
	 */
	class FREYA_REFLECT_EXPORT ReflectionModule : public core::Object, public core::RefCountedBase
	{
		core::string    m_ModuleName;
		ReflectionModule();
	protected:
		//! Create a module with a name \a module_name
		ReflectionModule(const core::string& module_name) : m_ModuleName(module_name) {}
	public:
		//! Destructor
		virtual ~ReflectionModule() {}
		//! Checks, if module supports reflection to a consumer with name \a consumer_name
		virtual bool	canReflectTo(const core::string& consumer_name) const = 0;
		//! Checks, if a module supports reflection to a consumer with id \a consumer_id
		virtual bool	canReflectTo(uint32_t consumer_id) const = 0;
		//! Try to reflect module to the consumer \a consumer
		virtual bool	reflectTo(ReflectionConsumer* consumer) = 0;
		//! Retrieves module name
		const core::string& getModuleName() const { return m_ModuleName; }
	};
	//! \brief Pointer to the ReflectionModule
	//! \ingroup grpFreyaReflect
	typedef core::smart_ptr<reflect::ReflectionModule, core::policies::ownership::Intrusive> reflection_module_ptr_t;
} // namespace reflect

#endif // Reflect_ReflectionModule_h__