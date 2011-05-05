/* File		: tests: smart_ptr.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */


#include <iostream>

#include "core/memory/MemoryArena.h"

#include "core/smart_ptr.h"
#include "core/Object.h"
#include "core/RefCountedBase.h"

class SomeTestClass : public core::Object
{
public:
	~SomeTestClass() { std::cout<<"~SomeTestClass"<<std::endl; }
};

class IntrusiveTestClass : public core::RefCountedBase
{
public:
	~IntrusiveTestClass() { std::cout<<"~IntrusiveTestClass"<<std::endl; }
};

int main(int argc, char* argv[])
{
	{
		using namespace core;
		smart_ptr<SomeTestClass> basic_test( new SomeTestClass );
		{
			smart_ptr<SomeTestClass> basic_test_int = basic_test;
			//*basic_test_int = 5;

			smart_ptr<SomeTestClass, policies::ownership::Scoped> scoped_int(new SomeTestClass), second_scoped_int(new SomeTestClass);

			scoped_int = second_scoped_int;
			assert(second_scoped_int.get() == NULL);

			assert(basic_test_int == basic_test);
			assert(basic_test_int != scoped_int);
			assert(scoped_int);
		}
		//assert(*basic_test == 5);

		smart_ptr<IntrusiveTestClass, policies::ownership::Intrusive> intrusive_test ( new IntrusiveTestClass );
		smart_ptr<IntrusiveTestClass, policies::ownership::Intrusive>  intrusive_test_2;
		intrusive_test_2 = intrusive_test;

		assert( intrusive_test->getRetainCount() == 2 );

		smart_ptr<SomeTestClass, policies::ownership::RefCounted, policies::storage::Array> array_ptr( new SomeTestClass [10] );

		smart_ptr<int> int_ptr;
		assert(!int_ptr);

		smart_ptr<Object> obj_ptr;
		assert(!obj_ptr);
		obj_ptr = basic_test;
		assert(obj_ptr);
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}