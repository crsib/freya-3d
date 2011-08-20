/* File         : FreyaReflectBinary: ReflectedClass.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "Base/ReflectedClass.h"
#include "CppTree/CppNode.h"
//Debug
#include <iostream>

namespace base
{

	ReflectedClass::ReflectedClass( CppNodeClass* node ) : ReflectedScope(node->getNodeName(), node)
	{
		std::clog << "Adding class " << node->getScopedName() << std::endl;
	}

}