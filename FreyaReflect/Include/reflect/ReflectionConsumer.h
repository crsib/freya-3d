/* File		: FreyaReflect: ReflectionConsumer.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Reflect_ReflectionConsumer_h__
#define Reflect_ReflectionConsumer_h__

#include "core/string.h"
#include "integer.h"
#include "FreyaReflectInternal.h"

namespace reflect
{
#define REFLECTION_CONSUMER() \
	static  uint32_t GetConsumerID() { static uint32_t __consumer_id = reflection_consumer_idx++; return __consumer_id; } \
	virtual uint32_t getConsumerID() const { return GetConsumerID(); }
	//! \brief Base class to reflection data consumers
	/*!
	 * This class is a base class to all reflection consumers, such as reflect::ReflectionDatabase.
	 * It provides methods to identify the concrete consumer which allows to determine, wether the current reflect::ReflectionModule is capable to 
	 * provide the reflection data of the format, required by the consumer.
	 */
	class FREYA_REFLECT_EXPORT ReflectionConsumer
	{
		core::string     m_ReflectionConsumerName;
	protected:
		static uint32_t  reflection_consumer_idx;
		//! Create a consumer with name \a name
		ReflectionConsumer(const core::string& name) : m_ReflectionConsumerName(name) {}
	public:
		//! Create a valid ID for the consumer. All classes, inherited from this should include this macro in public section
		REFLECTION_CONSUMER();
		//! Retrieve the consumers name
		const core::string&  getConsumerName() const { return m_ReflectionConsumerName; }
	};
}

#endif // Reflect_ReflectionConsumer_h__