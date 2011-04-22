/* File		: hashtable_test.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifdef NDEBUG
#undef NDEBUG
#endif

#include "containers/policies/Policies.h"
#include <iostream>

#include "containers/utils.h"
#include "containers/details/hashtable.h"
#include "core/string.h"

template<typename Pair>
struct pair_extractor { typename Pair::first_type*	operator()(const Pair& p) const  { return &p.first; } };

int main() 
{
	using namespace containers;
	
	{
		typedef details::HashTable<const core::string, pair<const core::string, unsigned>,
		hash<const std::string> , equal<const std::string> , pair_extractor< pair<const core::string, unsigned> >, 
		policies::memory::FreyaAllocator,  policies::multithreading::AtomicLock, policies::rehash::PrimeNumber > test_string_table_t;

		test_string_table_t test_string_table (0.75);

		assert( test_string_table.begin() == test_string_table.end());

		test_string_table_t::const_iterator const_it = test_string_table.begin();
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}