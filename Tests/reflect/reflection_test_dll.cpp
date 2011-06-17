/* File		: FreyaReflect Test: reflection_test_dll.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */


#include "reflection_test.h"
#include "core/Log.h"
/*
#ifdef _MSC_VER
	__declspec(dllexport) int __fake_var; // This variable is required to create exports file
#else
	__attribute__ ((visibility("default"))) int __fake_var;
#endif
*/
class ReflectionTestDll : public ReflectionTestBase
{
public:
	REFLECTION_OBJECT();

	virtual core::string getClassId() const { return "dll"; }

	int  dllFn() const { return 100; }
};

// Add new method
namespace
{
	using namespace reflect;
	class ReflectionTestDll_dllFn_metamethod : public Method
	{
	public:
		ReflectionTestDll_dllFn_metamethod() : Method("dllFn() const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			return Value(reinterpret_cast<ReflectionTestDll*>(ptr)->dllFn());
		}
	};

	class ReflectionTestDll_metaclass : public Class
	{
	public:
		ReflectionTestDll_metaclass(reflect::scope_ptr_t parent_scope) : Class("ReflectionTestDll", parent_scope) 
		{
			{
				method_ptr_t method = method_ptr_t(new ReflectionTestDll_dllFn_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			addBase("ReflectionTestBase");
		}

		virtual reflect::ReflectionObject* create() const { return new ReflectionTestDll; }
	};

	class AppReflectionModule : public ReflectionModule
	{
	public:
		AppReflectionModule() : ReflectionModule("DllModule") {}
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
				if(!db->getClass("ReflectionTestDll"))
					scope_ptr_t(new ReflectionTestDll_metaclass(root_scope)); //This object will be auto managed by DB

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
			InfoLog("Constructing module");
			reflection_module_ptr_t module = reflection_module_ptr_t(new AppReflectionModule);
			ReflectionDatabase::GetInstance().addModule(module);
		}

		void activate(){}
	};
}

const ReflectionModule_instance __module_instance;

Class* ReflectionTestDll::GetClass()
{
	static Class* __class = ReflectionDatabase::GetInstance().getClass("ReflectionTestDll");
	assert(__class && "Failed to retrieve reflect::ReflectionObject meta class");
	return __class;
}
