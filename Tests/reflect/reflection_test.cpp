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

#ifdef _MSC_VER
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
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
	core::Log::GetInstance().flush();
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
