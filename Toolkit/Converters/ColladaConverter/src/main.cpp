
#include "common.h"

#include "GData.h"
#include "LuaGenerator.h"

int main(int _argc, char* _argv[])
{	
	Object o1("A");
	Object o2("B");
	o2 = 7;
	o1.set(&o2);
	Object o3("D");
	o3 = 3.15f;
	o1.set(&o3);
	Object o4("D");
	o1.set(&o4);

	Object o5("E");
	o5 = "Hey, hey";
	o4.set(&o5);

	LuaFile luaFile("untitled2.lua");
	luaFile.write(&o1);

	
	
	std::string fileName = "untitled2.dae";
	DAE mCollada;
    int res = mCollada.load(fileName.c_str());

	if (res != DAE_OK)
		ERROR2("Can't open file `" << fileName << "`!", return -1);

	domCOLLADA* mRoot = mCollada.getRoot(fileName);

	if (!mRoot)
		ERROR2("Can't open file `" << fileName << "`!", return -1);

	GData gdata;
	gdata.handle(mRoot->getLibrary_geometries_array());

	return 0;
}


