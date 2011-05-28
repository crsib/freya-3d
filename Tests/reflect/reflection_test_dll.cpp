/* File		: FreyaReflect Test: reflection_test_dll.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */


#include "reflection_test.h"

#ifdef _MSC_VER
	__declspec(dllexport) int __fake_var; // This variable is required to create exports file
#else
	__attribute__ ((visibility("default"))) int __fake_var;
#endif