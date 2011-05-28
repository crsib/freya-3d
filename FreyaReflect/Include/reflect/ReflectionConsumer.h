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

	class FREYA_REFLECT_EXPORT ReflectionConsumer
	{
		core::string     m_ReflectionConsumerName;
	protected:
		static uint32_t  reflection_consumer_idx;
		ReflectionConsumer(const core::string& name) : m_ReflectionConsumerName(name) {}
	public:
		REFLECTION_CONSUMER();

		const core::string&  getConsumerName() const { return m_ReflectionConsumerName; }
	};
}

#endif // Reflect_ReflectionConsumer_h__