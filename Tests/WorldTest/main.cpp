/*
 * main.cpp
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Nov 5, 2009
 *      Author: Dmitri crsib Vedenko
 */

#include "freya.h"
#include "framework/World.h"
#include "framework/SceneNodeController.h"

class Initialize :
public core::taskmanager::Task
{
public:
	Initialize()
	{
		lua = core::EngineCore::getLuaCore();
		fs = core::EngineCore::getFilesystem();
	}
	virtual ~Initialize(){}
	virtual int
	operator() ()
	{
		fs->mount("pwd");
		size_t ssz;
		void* s_src = fs->read("/Scripts/Startup.lua",&ssz);
		std::cout << "Running script" << std::endl;
		EString scr(reinterpret_cast<char*>(s_src),ssz);
		core::EngineCore::getLuaCore()->startJIT(core::lua::LuaCore::FULL_OPTIMIZATION);
		core::EngineCore::getLuaCore()->runScript(scr);
		std::cout << "Script finished" << std::endl;
		core::memory::Free(s_src,core::memory::GENERIC_POOL);
		//resources::Resource*	res = core::EngineCore::getResourceManager()->load(":vbo:/vbos/cube.vdata");
		//framework::World*	wrld = framework::World::loadFromXML("/Worlds/World.xml");
		//wrld->destroy();
		return Initialize::DONE;
	}
private:
	core::lua::LuaCore*						lua;
	core::filesystem::Filesystem*			fs;
};

int main(int argc, char* argv[])
{
	core::EngineCore	core(argc,argv,"WorldTest");
	try
	{
		core::EngineCore::getTaskManager()->addTask(new Initialize);
		core::EngineCore::getTaskManager()->enterMainLoop();
		std::cout << "Exiting engine after mainloop termination " << std::endl;
	}
	catch(EngineException& ex)
	{
		//Something failed. Ansi c++ standart gurantees that all stack object will be release at this point.
		std::cout << "[ENGINE]: "<< ex.message() << std::endl;
	}
	catch(std::exception& ex)
	{
		std::cout << "[STD]: "<< ex.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Unknown exception" << std::endl;
	}
}
