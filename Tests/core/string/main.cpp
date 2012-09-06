/* File		: strings test:main.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifdef NDEBUG
#	undef NDEBUG
#endif

#include "core/string.h"
#include <iostream>
#include <cstdio>

#ifdef _MSC_VER
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
	SetConsoleOutputCP(65001); //Set utf-8 encoding
#endif	
	//setlocale(LC_CTYPE, "ru_ru.utf-8");
	{
		core::string	empty_string;
		assert(empty_string.empty());
		assert(empty_string == "");
		assert(!(empty_string < ""));
		assert(!(core::string("") < empty_string));
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
		std::cout << a1.c_str() << std::endl;
		assert(a1 == "Hello, world!");
		assert(a1.length() == strlen("Hello, world!"));
		std::cout << "Allocated " << core::memory::memory_allocated << std::endl;

		assert(a1.substr(string::range(7,12)) == "world");
		assert(a1.substr(string::range(7,12)) != "world!");
		assert(a1.substr(7).hash() != a1.hash());

		string russian_string = "Строка по русски!";

		russian_string += string(" ") + russian_string;

		assert(russian_string == "Строка по русски! Строка по русски!");
		assert(russian_string.length() == 35);

		string::range	r = a1.find("llo");
		assert(a1.substr(r) == "llo");

		r = russian_string.find("по");
		assert(russian_string.substr(r) == "по");

		r = russian_string.find("");
		assert(r.empty());
		r = empty_string.find("");
		assert(r.empty());
		r = empty_string.find("test");
		assert(r.empty());
		r = a1.find("test");
		assert(r.empty());


		r = a1.find(a1.substr(7,12));
		assert(r == string::range(7,12));

		string rfind_test = "The sixth sick sheik's sixth sheep's sick.";
		r = rfind_test.rfind("sixth",30);
		assert(r.length() == 5);
		assert(r.begin() > 20);
		assert(rfind_test.substr(r) == "sixth");
		assert(rfind_test.substr(r).c_str()[5] == 0);
		std::cout << rfind_test.substr(r).c_str() << std::endl;
		r = rfind_test.rfind("sixth",r.begin());
		assert(r.length() == 5);
		assert(r.begin() == 4);

		std::cout << rfind_test.to_upper().c_str() << std::endl;
		std::cout << rfind_test.to_lower().c_str() << std::endl;

		printf("%s %s\n", russian_string.c_str(), russian_string.to_upper().c_str());

		std::cout << rfind_test.replace("sixth", "seventh").c_str() << std::endl;

		string formatted = string::withFormat("I have %i apples in (странная вставка) the %i jars",30,3);

		printf("%s\n", formatted.c_str());
	}

	std::cout << "allocs: " << core::memory::allocation_count << "\ndeallocs: " << core::memory::deallocation_count
		<< "\nleaked: " << core::memory::memory_allocated << std::endl;
	system("pause");
	return 0;
}
