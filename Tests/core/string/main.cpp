#include "core/string.h"
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
	{
		core::string	empty_string;
		assert(empty_string.empty());
		assert(empty_string == "");
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;
		core::string	static_string("I'm the test string");
		assert(static_string.length() == strlen("I'm the test string"));
		std::cout << static_string.c_str() << " ( hash " << static_string.hash() << " )" << std::endl;
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;
		assert(static_string == "I'm the test string");
		assert(static_string != empty_string);
		assert(empty_string < static_string);
		assert(core::string("aBc") < "bcsdf");
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;

		core::string string2 = static_string;
		assert(string2 == static_string);
		string2 = empty_string;
		assert(string2.empty());
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;
		
		using core::string;

		string a1 = "Hello, ";
		a1 += "world!";

		assert(a1 == "Hello, world!");
		assert(a1.length() == strlen("Hello, world!"));
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;

		assert(a1.substr(7) == "world!");
		assert(a1.substr(7).hash() != a1.hash());

		string russian_string = "Строка по русски!";

		assert(russian_string == "Строка по русски!");

	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;
	system("pause");
	return 0;
}