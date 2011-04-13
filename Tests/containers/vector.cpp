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

int main( int argc, char* argv[] )
{
	{
		containers::vector<int> default_int_vector(1000);
	}
	

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;

	system("pause");
	return 0;
}