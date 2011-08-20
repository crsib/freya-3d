/* File         : FreyaReflectBinary: ReflectionDatabaseGenerator.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef ReflectionDatabaseGenerator_h__
#define ReflectionDatabaseGenerator_h__

#include "Base/ReflectedScope.h"

class CppTree;

namespace base
{
	class ReflectionDatabaseGenerator
	{
		ReflectionDatabaseGenerator();
		ReflectionDatabaseGenerator(const ReflectionDatabaseGenerator&);
		ReflectionDatabaseGenerator& operator = (const ReflectionDatabaseGenerator&);
	public:
		ReflectionDatabaseGenerator(CppTree* tree);

	private:
		base::reflected_scope_ptr       m_RootScope;
	};
}

#endif // ReflectionDatabaseGenerator_h__