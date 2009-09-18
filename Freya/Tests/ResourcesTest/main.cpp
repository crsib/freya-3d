/*
 * main.cpp
 *
 *  Created on: 24.05.2009
 *      Author: vedenko
 */
#include "freya.h"

#include <iostream>

using std::cout;
using std::endl;

const unsigned winWidth = 512;
const unsigned winHeight = 512;
//*** Simple rendering task
class SimpleRenderer : public core::taskmanager::Task
{
public:
	virtual int operator () ()
	{
		rapi->clearColor();

		wm->swapBuffers();
		//std::cout << "Render task " << std::endl;
		return core::taskmanager::Task::MAIN_THREAD;
	}
	windowmanager::WindowManagerDriver* wm;
	renderer::RenderingAPIDriver*		rapi;
};
//***	Simple update task
class SimpleUpdate : public core::taskmanager::Task
{
public:
	SimpleUpdate() : firstpass(true),firstnotify(true){}
	virtual int operator () ()
	{
		wm->updateEvents();
		if(kbd->getKeyState(KeyboardKeys::KEY_ESCAPE))
			core::EngineCore::shutdown();
		if(firstpass)
		{
			res = core::EngineCore::getResourceManager()->load(":tga:/Base/Fonts/STKaiti.tga:mipmaps");
			firstpass = false;
		}
		else
		{
			if(res->ready())
				if(firstnotify)
				{
					std::cout << "Resource ready" << std::endl;
					firstnotify = false;
				}
		}
		//std::cout << "Update task" << std::endl;
		//sleep(3);
		return core::taskmanager::Task::MAIN_THREAD;
		//return core::taskmanager::Task::DONE;
	}
	windowmanager::WindowManagerDriver* wm;
	windowmanager::input::KeyDrivenDevice*		kbd;
	resources::Resource*					res;
	bool firstpass;
	bool firstnotify;
};

int main()
{
	core::EngineCore core;
	try
	{
		//Start up WM and renderer
		core.createWindowManager("SDL");

		windowmanager::WindowManagerDriver* wm = core.getWindowManager();
		wm->createWindow(winWidth,winHeight,"Resource manager test",false,NULL);

		core::filesystem::Filesystem* fs = core::EngineCore::getFilesystem();
		fs->mount("pwd");
		fs->mount("lzma","Base.7z");

		core.createRenderingDriver(renderer::futures::MULTITEXTURE | renderer::futures::AUTO_TRANSPOSE_MATIRIX |
				renderer::futures::VERTEX_BUFFER | renderer::futures::TEXTURE_BUFFER |
				renderer::futures::VERTEX_SHADER | renderer::futures::FRAGMENT_SHADER);
		renderer::RenderingAPIDriver*		rapi = core.getRenderingDriver();

		resources::ResourceManager* rm =    core.getResourceManager();

		//Setup renderer
		rapi->setViewport(winWidth,winHeight);
		rapi->setMatrixMode(renderer::MatrixMode::PROJECTION);
		rapi->setOrtho(winWidth,winHeight,-1,1);
		rapi->setMatrixMode(renderer::MatrixMode::MODELVIEW);
		rapi->loadIdentityMatrix();
		rapi->clearColorValue(0.2,0.4,0.8,1.0);
		//Create keyboard
		windowmanager::input::KeyDrivenDevice*		kbd = wm->createKeyDrivenDevice("keyboard");
		//Create tasks
		SimpleUpdate*  updT = new SimpleUpdate;
		updT->wm = wm;
		updT->kbd = kbd;

		SimpleRenderer* renT = new SimpleRenderer;
		renT->wm = wm;
		renT->rapi = rapi;

		//Resource management task here
		size_t old_time, new_time;
		old_time = wm->getTickCount();
		//Synchronous test
		resources::Resource*	res = rm->load(":tga:/Base/Textures/Strange.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);
		new_time = wm->getTickCount();
		std::cout << "Resource loading: synchronous : attempt 1: " << (new_time - old_time)*0.001 << " secs" << std::endl;
		old_time = wm->getTickCount();
		res = rm->load(":tga:/Base/Textures/Strange.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);
		new_time = wm->getTickCount();
		std::cout << "Resource loading: synchronous : attempt 2: " << (new_time - old_time)*0.001 << " secs" << std::endl;
		old_time = wm->getTickCount();
		res = rm->load(":tga:/Base/Textures/Strange.tga:mipmaps",resources::ResourceManager::IMMEDIATELY);
		new_time = wm->getTickCount();
		std::cout << "Resource loading: synchronous : attempt 3: " << (new_time - old_time)*0.001 << " secs" << std::endl;
		//Async/sync
		old_time = wm->getTickCount();
		rm->load(":tga:mipmaps:/Base/Textures/dno.tga",resources::ResourceManager::IMMEDIATELY);
		res->get<renderer::Texture*>();
		new_time = wm->getTickCount();
		std::cout << "Resource loading: synchronous (4) : " << (new_time - old_time)*0.001 << " secs" << std::endl;

		core.getTaskManager()->addTask(updT);
		core.getTaskManager()->addTask(renT);
		core.getTaskManager()->enterMainLoop();
	}
	catch(EngineException& ex)
	{
		cout << ex.message() << endl;
	}
	return 0;
}
