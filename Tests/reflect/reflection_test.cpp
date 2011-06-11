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
#include "reflect/Method.h"

#include "reflect/Value.h"

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <stdarg.h>

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
	core::Log::GetInstance().setLogLevel(core::Log::Info);
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
	std::cout << "Id of " << reflect::ReflectionObject::GetClass()->getScopedName().c_str() << " is " << reflect::ReflectionObject::GetClass()->getClassID() << std::endl;

	assert(reflect::ReflectionObject::GetClass()->getClassID() == reflect::ReflectionObject::GetClass()->getClassID());

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
	// Basic method tests
	reflect::Class* refl_obj_class = reflect::ReflectionObject::GetClass();
	assert(refl_obj_class->getMethodsCount() == 2);
	assert(refl_obj_class->getMethod("getClass() const"));
	assert(!refl_obj_class->getMethod("foo()"));
	assert(refl_obj_class->getMethod("getClass() const")->call(&temp_obj).get<reflect::Class*>() == refl_obj_class);
	assert(refl_obj_class->getMethod("GetClass()")->call().get<reflect::Class*>() == refl_obj_class);
	assert(refl_obj_class->getMethod("getClass() const")->isVirtual() && !refl_obj_class->getMethod("getClass() const")->isStatic());
	assert(!refl_obj_class->getMethod("GetClass()")->isVirtual() && refl_obj_class->getMethod("GetClass()")->isStatic());

	//Get class for the ReflectionTestBase
	reflect::Class* refl_test_base = reflect::ReflectionDatabase::GetInstance().getClass("ReflectionTestBase");
	assert(refl_test_base);
	assert(refl_test_base->getClassID() != refl_obj_class->getClassID());
	assert(refl_test_base == ReflectionTestBase::GetClass());

	// Testing factory
	ReflectionTestBase* test_obj = static_cast<ReflectionTestBase*>(refl_test_base->create());
	assert(test_obj);
	assert(test_obj->getClass() == refl_test_base);
	// Testing properties
	assert(refl_test_base->getProperty("readOnlyProperty")->get(test_obj).get<int>() == test_obj->getReadOnlyProperty());
	refl_test_base->getProperty("intProperty")->set(test_obj, 100500);
	assert(test_obj->getIntProperty() == 100500);

	// Testing sum
	assert(refl_test_base->getMethod("sum(int, int) const")->call(test_obj,5,5).get<int>() == test_obj->sum(5,5));
	//Testing virtual
	assert(refl_test_base->getMethod("getClassId() const")->call(test_obj).get<core::string>() == "base");
	delete test_obj;

	//Load library into the address space
#ifdef _MSC_VER
	LoadLibraryA("reflection_test_lib.dll");
#endif
	//void __reflection_module_stub();
	//__reflection_module_stub();
	core::Log::GetInstance().flush();
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}


//ReflectionTestBase

namespace 
{
	using namespace reflect;
	class ReflectionTestBase_getClass_metamethod : public Method
	{
	public:
		ReflectionTestBase_getClass_metamethod() : Method("getClass() const",false,true) {}

		Value call(method_this_ptr_t ptr, ...) const
		{
			return Value(reinterpret_cast<ReflectionObject*>(ptr)->getClass());
		}
	};

	class ReflectionTestBase_GetClass_metamethod : public Method
	{
	public:
		ReflectionTestBase_GetClass_metamethod() : Method("GetClass()",true,false) {}

		Value call(method_this_ptr_t ptr, ...) const
		{
			(void) ptr;
			return Value(ReflectionObject::GetClass());
		}
	};

	class ReflectionTestBase_getReadOnlyProperty_metamethod : public Method
	{
	public:
		ReflectionTestBase_getReadOnlyProperty_metamethod() : Method("getReadOnlyProperty() const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			return Value(reinterpret_cast<ReflectionTestBase*>(ptr)->getReadOnlyProperty());
		}
	};

	class ReflectionTestBase_getIntProperty_metamethod : public Method
	{
	public:
		ReflectionTestBase_getIntProperty_metamethod() : Method("getIntProperty() const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			return Value(reinterpret_cast<ReflectionTestBase*>(ptr)->getIntProperty());
		}
	};

	class ReflectionTestBase_setIntProperty_metamethod : public Method
	{
	public:
		ReflectionTestBase_setIntProperty_metamethod() : Method("setIntProperty() const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			va_list list;
			va_start(list, ptr);
			reinterpret_cast<ReflectionTestBase*>(ptr)->setIntProperty(va_arg(list,int));
			va_end(list);
			return Value();
		}
	};

	class ReflectionTestBase_getClassId_metamethod : public Method
	{
	public:
		ReflectionTestBase_getClassId_metamethod() : Method("getClassId() const", false, true) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			return Value(reinterpret_cast<ReflectionTestBase*>(ptr)->getClassId());
		}
	};

	class ReflectionTestBase_sum_metamethod : public Method
	{
	public:
		ReflectionTestBase_sum_metamethod() : Method("sum(int, int) const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			va_list list;
			va_start(list, ptr);
			int result = reinterpret_cast<ReflectionTestBase*>(ptr)->sum(va_arg(list,int), va_arg(list, int));
			va_end(list);
			return Value(result);
		}
	};

	class ReflectionTestBase_metaclass : public Class
	{
	public:
		REFLECTION_CLASS();
		ReflectionTestBase_metaclass(scope_ptr_t ptr) : Class("ReflectionTestBase", ptr) 
		{
			//Add getClass property
			property_ptr_t get_class_prop = property_ptr_t(new PropertyImpl<Class*,ReflectionTestBase>("class",&ReflectionTestBase::getClass));
			m_Properties["class"] = get_class_prop;

			//Add readOnlyProperty
			property_ptr_t readOnly_prop = property_ptr_t(new PropertyImpl<int,ReflectionTestBase>("readOnlyProperty",&ReflectionTestBase::getReadOnlyProperty));
			m_Properties["readOnlyProperty"] = readOnly_prop;

			//Add intProperty
			property_ptr_t int_prop = property_ptr_t(new PropertyImpl<int,ReflectionTestBase>("intProperty",&ReflectionTestBase::getIntProperty, &ReflectionTestBase::setIntProperty));
			m_Properties["intProperty"] = int_prop;

			//Add methods
			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_getClass_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_GetClass_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_getClassId_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_getReadOnlyProperty_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_getIntProperty_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_setIntProperty_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			{
				method_ptr_t method = method_ptr_t(new ReflectionTestBase_sum_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			addBase("reflect::ReflectionObject");
			addBase("core::Object");
		}

		ReflectionObject* create() const { return new ReflectionTestBase; }
	};
	
	class AppReflectionModule : public ReflectionModule
	{
	public:
		virtual bool	canReflectTo(const core::string& module) const
		{
			return (module == "FreyaReflect");
		}

		virtual bool	canReflectTo(uint32_t consumer_id) const
		{
			return (consumer_id == ReflectionDatabase::GetConsumerID());
		}

		virtual bool	reflectTo(ReflectionConsumer* consumer)
		{
			if(consumer->getConsumerID() == ReflectionDatabase::GetConsumerID())
			{
				scope_ptr_t root_scope = ReflectionDatabase::GetInstance().getRootScope();

				ReflectionDatabase* db = static_cast<ReflectionDatabase*>(consumer);

				// Add ReflectionTestBase
				if(!db->getClass("ReflectionTestBase"))
					scope_ptr_t(new ReflectionTestBase_metaclass(root_scope)); //This object will be auto managed by DB

				return true;
			}
			return false;
		}
	}; //class AppReflectionModule

	class ReflectionModule_instance
	{
	public:
		ReflectionModule_instance()
		{
			reflection_module_ptr_t module = reflection_module_ptr_t(new AppReflectionModule);
			ReflectionDatabase::GetInstance().addModule(module);
		}
	};

	static ReflectionModule_instance __reflectionmodule_instance;

	// In binary module
}