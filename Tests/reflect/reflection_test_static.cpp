/* File		: FreyaReflect Test: reflection_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflection_test.h"
#include "core/Log.h"
// We just implement some other version of ReflectionTestBase

class ReflectionTestStatic : public ReflectionTestBase
{
public:
	REFLECTION_OBJECT();

	virtual core::string getClassId() const { return "static"; }

	int  staticFn() const { return 10; }
};

// Add new method
namespace
{
	using namespace reflect;
	class ReflectionTestStatic_staticFn_metamethod : public Method
	{
	public:
		ReflectionTestStatic_staticFn_metamethod() : Method("staticFn() const", false, false) {}

		Value call(method_this_ptr_t ptr,...) const
		{
			return Value(reinterpret_cast<ReflectionTestStatic*>(ptr)->staticFn());
		}
	};

	class ReflectionTestStatic_metaclass : public Class
	{
	public:
		ReflectionTestStatic_metaclass(reflect::scope_ptr_t parent_scope) : Class("ReflectionTestStatic", parent_scope) 
		{
			{
				method_ptr_t method = method_ptr_t(new ReflectionTestStatic_staticFn_metamethod);
				m_Methods[method->getMethodSignature()] = method;
			}

			addBase("ReflectionTestBase");
		}

		virtual reflect::ReflectionObject* create() const { return new ReflectionTestStatic; }
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
				if(!db->getClass("ReflectionTestStatic"))
					scope_ptr_t(new ReflectionTestStatic_metaclass(root_scope)); //This object will be auto managed by DB

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
	};	

	
}
const ReflectionModule_instance __reflectionmodule_instance;

void __reflection_module_stub()
{
	(void)__reflectionmodule_instance;
};

Class* ReflectionTestStatic::GetClass()
{
	static Class* __class = ReflectionDatabase::GetInstance().getClass("ReflectionTestStatic");
	assert(__class && "Failed to retrieve reflect::ReflectionTestStatic meta class");
	return __class;
}