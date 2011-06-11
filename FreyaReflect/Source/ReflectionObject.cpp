/* File		: FreyaReflect: ReflectionObject.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "reflect/ReflectionObject.h"
#include "reflect/Class.h"
#include "reflect/Namespace.h"
#include "reflect/ReflectionModule.h"
#include "reflect/ReflectionDatabase.h"
#include "reflect/Method.h"

namespace reflect
{
	namespace 
	{
		class ReflectionObject_getClass_metamethod : public Method
		{
		public:
			ReflectionObject_getClass_metamethod() : Method("getClass() const",false,true) {}

			Value call(method_this_ptr_t ptr, ...) const
			{
				return Value(reinterpret_cast<ReflectionObject*>(ptr)->getClass());
			}
		};

		class ReflectionObject_GetClass_metamethod : public Method
		{
		public:
			ReflectionObject_GetClass_metamethod() : Method("GetClass()",true,false) {}

			Value call(method_this_ptr_t ptr, ...) const
			{
				(void) ptr;
				return Value(ReflectionObject::GetClass());
			}
		};

		class ReflectionObject_metaclass : public Class
		{
		public:
			REFLECTION_CLASS();
			ReflectionObject_metaclass(scope_ptr_t reflection_namespace) : Class("ReflectionObject", reflection_namespace) 
			{
				//Add getClass property
				property_ptr_t get_class_prop = property_ptr_t(new PropertyImpl<Class*,ReflectionObject>("class",&ReflectionObject::getClass));
				m_Properties["class"] = get_class_prop;

				{
					method_ptr_t method = method_ptr_t(new ReflectionObject_getClass_metamethod);
					m_Methods[method->getMethodSignature()] = method;
				}

				{
					method_ptr_t method = method_ptr_t(new ReflectionObject_GetClass_metamethod);
					m_Methods[method->getMethodSignature()] = method;
				}
			}

			ReflectionObject* create() { return new ReflectionObject; }
		};

		class ReflectNamespace_metaclass : public Namespace
		{
		public:
			ReflectNamespace_metaclass(scope_ptr_t root_node) : Namespace("reflect", root_node) {} 
		};

		class Reflect_ReflectionModule : public ReflectionModule
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
					
					//Try to add reflect namespace
					scope_ptr_t reflect_namespace = root_scope->getChild("reflect", false);
					if(!reflect_namespace)
						reflect_namespace = scope_ptr_t(new ReflectNamespace_metaclass(root_scope));

					//Try to add ReflectionObject class
					scope_ptr_t reflection_object_class = reflect_namespace->getChild("ReflectionObject", false);
					if(!reflection_object_class)
						reflection_object_class = scope_ptr_t(new ReflectionObject_metaclass(reflect_namespace));

					return true;
				}
				return false;
			}
		}; //class Reflect_ReflectionModule

		class Reflect_ReflectionModule_instance
		{
		public:
			Reflect_ReflectionModule_instance()
			{
				reflection_module_ptr_t module = reflection_module_ptr_t(new Reflect_ReflectionModule);
				ReflectionDatabase::GetInstance().addModule(module);
			}
		};

		static Reflect_ReflectionModule_instance __reflect_reflectionmodule_instance;
	}

	Class* ReflectionObject::GetClass()
	{
		static Class* __class = ReflectionDatabase::GetInstance().getClass("reflect::ReflectionObject");
		FREYA_REFLECT_ASSERT(__class, "Failed to retrieve reflect::ReflectionObject meta class");
		return __class;
	}
} // namespace reflect
