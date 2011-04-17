/* File		: containers tests: vector.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifdef NDEBUG
#	undef NDEBUG
#endif

#include <iostream>
#include "containers/vector.h"

class TestClass
{
	unsigned m_Data;
public:
	TestClass() : m_Data (0) { std::cout << "TestClass::TestClass()" << std::endl; }
	TestClass(unsigned data) : m_Data(data) {std::cout << "TestClass::TestClass(unsigned)" << std::endl;}
	TestClass(const TestClass& other) : m_Data(other.m_Data) { std::cout << "TestClass::TestClass(const TestClass&)" << std::endl; }
	~TestClass() { std::cout << "TestClass::~TestClass()" << std::endl; }
	TestClass& operator = (const TestClass& rhs) { m_Data = rhs.m_Data; std::cout << "TestClass& operator = (const TestClass&)" << std::endl; return *this; }
	
	unsigned	getData() const { return m_Data; }
	void		setData(unsigned data) { m_Data = data; }
};

int main( int argc, char* argv[] )
{
	{
		using namespace containers;
		
		containers::vector<int> default_int_vector(10);
		assert( default_int_vector.capacity() == 16 );

		float		some_array[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };
		typedef containers::vector<float, policies::memory::FreyaAllocator, policies::multithreading::AtomicLock, policies::storage::Greedy> float_vector_t;
		float_vector_t float_vector(some_array, some_array + 5);

		assert( float_vector.size() == 5 );
		assert( fabs(float_vector[1] - some_array[1]) < 1.0e-5f );

		float_vector[2] = 10.0f;
		float_vector.insert(float_vector.begin(), -1);
		float_vector.insert(float_vector.begin() + 2, 666.0f);
		float_vector.insert(float_vector.end(), 1000.f);
		for(float_vector_t::const_iterator it = float_vector.begin(), end = float_vector.end(); it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		float_vector.push_back(101.0f);
		for(float_vector_t::const_reverse_iterator it = float_vector.rbegin(), end = float_vector.rend(); it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		default_int_vector.insert(default_int_vector.begin(), 3); //3
		default_int_vector.insert(default_int_vector.begin(), 1); //1,3
		default_int_vector.insert(default_int_vector.begin()+1, 2);//1,2,3
		default_int_vector.insert(default_int_vector.end(), 4);//1,2,3,4

		default_int_vector.insert(default_int_vector.begin() + 2, 10, 10);

		for( vector<int>::iterator it = default_int_vector.begin(), end = default_int_vector.end(); it != end; ++it )
			std::cout << *it << " ";
		std::cout << std::endl;

		containers::vector<TestClass> test_class_container;

		std::cout << "Push" << std::endl;
		test_class_container.push_back(TestClass());
		test_class_container.back().setData(1);
		std::cout << "Pop" << std::endl;
		test_class_container.pop_back();

		test_class_container.insert(test_class_container.begin(), TestClass(3)); //3
		test_class_container.insert(test_class_container.begin(), TestClass(1)); //1,3
		test_class_container.insert(test_class_container.begin()+1, TestClass(2));//1,2,3
		test_class_container.insert(test_class_container.end(), TestClass(4));//1,2,3,4

		for( vector<TestClass>::iterator it = test_class_container.begin(), end = test_class_container.end(); it != end; ++it )
			std::cout << it->getData() << " ";
		std::cout << std::endl;
	}
	

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}