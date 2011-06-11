/* File		: FreyaReflect Test: reflection_test.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef reflection_test_h__
#define reflection_test_h__

#include "reflect/ReflectionDatabase.h"
#include "reflect/Class.h"
#include "reflect/ReflectionObject.h"
#include "core/Object.h"

// Some test interface
class	ReflectionTestBase : public reflect::ReflectionObject, public core::Object
{
	int		m_IntProperty;
	int		m_ReadOnlyProperty;
public:
	//Declare this class as reflection object
	REFLECTION_OBJECT();
	ReflectionTestBase() : m_IntProperty(0), m_ReadOnlyProperty(10) {}

	int		getReadOnlyProperty() const { return m_ReadOnlyProperty; }
	
	int		getIntProperty() const { return m_IntProperty; }
	void	setIntProperty(int value)  { m_IntProperty = value; }

	virtual core::string getClassId() const { return "base"; }

	int	sum(int a, int b) const { return a+b + m_ReadOnlyProperty; }
};

inline reflect::Class* ReflectionTestBase::GetClass()
{
	static reflect::Class* __class = reflect::ReflectionDatabase::GetInstance().getClass("ReflectionTestBase");
	assert(__class && "Failed to retrieve ReflectionTestBase meta class");
	return __class;
}

#endif // reflection_test_h__