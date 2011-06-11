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
	std::cout << "Starting hash map test" << std::endl;
	{
		using namespace containers;
		using core::string;

		typedef hash_map<string,string> string_lookup_t;
		typedef hash_map<string,int>	string_int_lookup_t;
		typedef hash_map<int, int>		int_lookup_t;

		string_lookup_t		string_lookup;
		string_int_lookup_t string_int_lookup;
		int_lookup_t		int_lookup;

		std::cout << "Basic tests" << std::endl;

		string_lookup["test"] = "foo";
		std::cout << "Writing data" << std::endl;

		string_int_lookup["foo"]  = 1;
		int_lookup[1] = 2;

		assert(string_lookup["test"] == "foo");
		assert(int_lookup[string_int_lookup[string_lookup["test"]]] == 2);

		assert(int_lookup.find(2) == int_lookup.end());

		std::cout << "Const tests" << std::endl;

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

		typedef hash_multimap<string,string> multistring_lookup_t;

		multistring_lookup_t multi_lookup;
		multi_lookup.insert(multistring_lookup_t::value_type("test", "foo"));
		multi_lookup.insert(multistring_lookup_t::value_type("test", "bar"));
		multi_lookup.insert(multistring_lookup_t::value_type("test", "moo"));

		multistring_lookup_t::iterator_range range = multi_lookup.find("test");

		for( multistring_lookup_t::iterator it = range.first; it != range.second; ++it)
			std::cout << it->first.c_str() << " -> " << it->second.c_str() << std::endl;

		multi_lookup.erase( range.first, range.second );
		assert(multi_lookup.empty());
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}