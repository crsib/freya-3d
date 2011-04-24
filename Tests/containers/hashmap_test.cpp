/* File		: tests: hashmap_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <iostream>

#include "core/memory/MemoryArena.h"

#include "containers/hash_map.h"
#include "containers/policies/Policies.h"
#include "core/string.h"

int main(int argc, char* argv[])
{
	{
		using namespace containers;
		using core::string;

		typedef hash_map<string,string> string_lookup_t;
		typedef hash_map<string,int>	string_int_lookup_t;
		typedef hash_map<int, int>		int_lookup_t;

		string_lookup_t		string_lookup;
		string_int_lookup_t string_int_lookup;
		int_lookup_t		int_lookup;

		string_lookup["test"] = "foo";
		string_int_lookup["foo"]  = 1;
		int_lookup[1] = 2;

		assert(string_lookup["test"] == "foo");
		assert(int_lookup[string_int_lookup[string_lookup["test"]]] == 2);

		assert(int_lookup.find(2) == int_lookup.end());

		struct test_const_find
		{
			int_lookup_t test;
			test_const_find() { test[2] = 3; }
			int const_fn() const { return test.find(2)->second; }
		};
		test_const_find test_const_find_object;
		assert( test_const_find_object.const_fn() == 3 );

		int_lookup_t::const_iterator test_const_assigmnet = int_lookup.begin();

		assert(int_lookup.insert( int_lookup_t::value_type(10,10) ).first != int_lookup.end());

		int_lookup.erase(10); 
		assert( int_lookup.find(10) == int_lookup.end() );
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}