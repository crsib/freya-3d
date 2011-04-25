/* File		: tests: hashset_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <iostream>

#include "core/memory/MemoryArena.h"

#include "core/string.h"
#include "containers/hash_set.h"
#include "containers/policies/Policies.h"

int main(int argc, char* argv[])
{
	{
		using namespace containers;
		using core::string;
		
		typedef hash_set<string> string_set_t;
		string_set_t string_set;

		string_set.insert("a");
		string_set.insert("b");
		string_set.insert("c");
		assert(!string_set.insert("a").second);

		assert(string_set.size() == 3);

		assert(string_set.find("b") != string_set.end() );
		assert(string_set.find("d") == string_set.end() );

		typedef hash_multiset<int> int_set_t;

		int_set_t int_set;

		int_set.insert(1);
		int_set.insert(2);
		int_set.insert(3);
		int_set.insert(4);
		int_set.insert(5);
		int_set.insert(6);
		int_set.insert(1);
		int_set.insert(2);
		int_set.insert(3);
		int_set.insert(4);

		assert(int_set.size() == 10);

		for(int_set_t::iterator it = int_set.begin(); it != int_set.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}