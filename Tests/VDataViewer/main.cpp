/*
 * main.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: crsib
 */

#include "freya.h"
#include "core/lua/LuaCore.h"


class RunScript : public core::taskmanager::Task
{
public:
	virtual int operator() ()
	{
		core::filesystem::Filesystem * fs = core::EngineCore::getFilesystem();
		fs->mount("pwd");
		size_t ssz;
		void* s_src = fs->read("/Scripts/VDataViewer/Startup.lua",&ssz);
		std::cout << "Running script" << std::endl;
		EString scr(reinterpret_cast<char*>(s_src),ssz);
		//core::EngineCore::getLuaCore()->setValue("reload_vdata",core::Variable(reload));
		core::EngineCore::getLuaCore()->startJIT(core::lua::LuaCore::FULL_OPTIMIZATION);

		core::EngineCore::getLuaCore()->runScript(scr);
		core::memory::Free(s_src,core::memory::GENERIC_POOL);
		return RunScript::DONE;
	}
};

int main(int argc, char* argv[])
{

	try
	{
		core::EngineCore	core(argc,argv,"VDataViewer");
		core::EngineCore::getTaskManager()->addTask(new RunScript);
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
	return 0;
}
