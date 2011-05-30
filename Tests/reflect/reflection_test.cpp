/* File		: FreyaReflect Test: reflection_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifdef NDEBUG
#	undef NDEBUG
#endif

#include <iostream>
#include <cstdio>

#include "reflection_test.h"
#include "core/Log.h"

#include "reflect/Value.h"

#ifdef _MSC_VER
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
	// Basic tests
	assert(reflect::ReflectionDatabase::GetInstance().getModulesCount() > 0);
	assert(reflect::ReflectionObject::GetClass());
	assert(reflect::ReflectionObject::GetClass()->getName() == "ReflectionObject");
	assert(reflect::ReflectionObject::GetClass()->getScopedName() == "reflect::ReflectionObject");
	assert(reflect::ReflectionDatabase::GetInstance().getRootScope()->getName() == "");
	assert(reflect::ReflectionDatabase::GetInstance().getClass("reflect::ReflectionObject") == reflect::ReflectionObject::GetClass());
	assert(!reflect::ReflectionDatabase::GetInstance().getScope("abc::def::foo"));
	assert(reflect::ReflectionDatabase::GetInstance().getScope("reflect")->getScopeType() == reflect::Scope::NamespaceScope);
	assert(reflect::ReflectionDatabase::GetInstance().getScope("reflect")->getChild("ReflectionObject"));
	assert(reflect::ReflectionDatabase::GetInstance().getScope("::reflect::ReflectionObject"));
	std::cout << "Id of " << reflect::ReflectionObject::GetClass()->getScopedName().c_str() << " is " << reflect::ReflectionObject::GetClass()->getClassID() << std::endl;
	std::cout << "Base class ID " << reflect::Class::GetClassID() << std::endl;

	//Value test
	int tmp = 2;
	reflect::Value val, val2(tmp);
	val = val2;
	assert(val.get<int>() == 2);
	assert(val2.get<int>() == 2);
	val = &tmp;
	assert(*val.get<int*>() == 2);
	assert(val2.get<int>() == 2);

	val2 = core::string("test");
	assert(val2.get<core::string>() == "test");

	reflect::ReflectionObject temp_obj;
	val = &temp_obj;
	assert(val.isReflectionObject());
	assert(!val2.isReflectionObject());

	assert(reflect::Value().isEmpty());
	assert(val2.getReflectionObject() == NULL);

	assert(val.getReflectionObject()->getClass() == reflect::ReflectionObject::GetClass());

	// ReflectionObject property
	assert(reflect::ReflectionObject::GetClass()->getPropertiesCount());
	assert(reflect::ReflectionObject::GetClass()->getProperty("class"));
	assert(reflect::ReflectionObject::GetClass()->getProperty("class")->get(&temp_obj).get<reflect::Class*>() == reflect::ReflectionObject::GetClass());

	core::Log::GetInstance().flush();
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
