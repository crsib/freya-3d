/* File		: tests: hashmap_perf.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <iostream>

#include "core/memory/MemoryArena.h"

#include "containers/hash_map.h"
#include "containers/policies/Policies.h"

int main(int argc, char* argv[])
{
	{

	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}