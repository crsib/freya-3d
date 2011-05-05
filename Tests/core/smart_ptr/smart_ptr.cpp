/* File		: tests: smart_ptr.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */


#include <iostream>

#include "core/memory/MemoryArena.h"

#include "core/smart_ptr.h"

int main(int argc, char* argv[])
{
	{
		using namespace core;
		shared_ptr<int> test;
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}