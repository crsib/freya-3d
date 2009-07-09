/*
 * main.cpp
 *
 *  Created on: 02.03.2009
 *      Author: vedenko
 */
#include "freya.h"
#include <iostream>

const int winWidth = 640,winHeight = 640;
const bool	fullscreen = false;

void	_quit() //Quit callback
{
	core::EngineCore::shutdown();
}


class SecTask : public core::taskmanager::Task
{
public:
	SecTask()
	{
		j = i++;
	}
	virtual int operator () ()
	{
		for(int k = 0; k<100;k++)
			j = sin(j);
		return core::taskmanager::Task::SECONDARY_THREAD;
	}
private:
	static int i;
	int j;
};

int SecTask::i = 0;


class MainTask : public core::taskmanager::Task
{
public:
	virtual int operator () ()
	{
		for(int i = 0; i < 10; i++)
			core::EngineCore::getTaskManager()->addAsynchronousTask(new SecTask);
		return core::taskmanager::Task::DONE;
	}
};


int main(int argC,char** argV)
{
	//Create framework core. Core is responsible on creating/managing various subsystems
	core::EngineCore Core;
	try
	{
		std::cout << "Starting engine" << std::endl;
		//Get the address of WindowManger instance
		Core.createWindowManager("SDL");
		Core.getTaskManager()->addTask(new MainTask);
		//Core.getTaskManager()->addTask(new MainTask);
		//Core.getTaskManager()->addTask(new MainTask);
		//Core.getTaskManager()->addTask(new MainTask);
		Core.getTaskManager()->enterMainLoop();

		windowmanager::WindowManagerDriver* wm = Core.getWindowManager();
		wm->setQuitCallback(windowmanager::Callback(_quit));
		//Mount filesystems
		core::filesystem::Filesystem*	fs = Core.getFilesystem();
		fs->mount("pwd");
		fs->mount("lzma","Textures.7z");

		//Create window
		wm->createWindow(winWidth,winHeight,"Tutorial 1: Bump mapping",fullscreen ,NULL);
		//Start rendering subsystem
		Core.createRenderingDriver(renderer::futures::MULTITEXTURE | renderer::futures::AUTO_TRANSPOSE_MATIRIX |
				renderer::futures::VERTEX_BUFFER | renderer::futures::TEXTURE_BUFFER |
				renderer::futures::VERTEX_SHADER | renderer::futures::FRAGMENT_SHADER);
		//Get the address of rendering subsystem
		renderer::RenderingAPIDriver*		rapi = Core.getRenderingDriver();
		//Set the clear color value
		rapi->clearColorValue(0.3,0.4,0.5,1.0);
		wm->swapBuffers();
		//Create keyboard and mouse
		windowmanager::input::KeyDrivenDevice* kbd = wm->createKeyDrivenDevice("keyboard");
		windowmanager::input::MovementDrivenDevice* mouse = wm->createMovementDrivenDevice("mouse");
		//Time variables. We need to know, how much time previuos frame has taken to do the correct animation/camera controlling
		unsigned oldTime = wm->getTickCount(),newTime;
		float secs;
		//Set up view parameters.
		rapi->setViewport(winWidth,winHeight);

		//Create two cameras (fly and rotate)
		unsigned camMode = 0;//Rotate camera by default
		camera::BasicCamera*	cams[] = {
				new camera::RotateCamera(math::vector3d(3.0,0.0,3.0),math::vector3d(-1.0,0,-1.0),math::vector3d(0.0,1.0,0.0),
						1.04,(float)winWidth/(float)winHeight,1,1000),
						new camera::FlyCamera(math::vector3d(3.0,0.0,3.0),math::vector3d(-1.0,0.0,-1.0),math::vector3d(0.0,1.0,0.0),
								1.04,(float)winWidth/(float)winHeight,1,1000)
		};
		//Sphere test
		primitives::Sphere<30,30> sphere;
		sphere.addInstance(renderer::InstanceData());
		//Create cube
		primitives::Cube cube;
		cube.addInstance(renderer::InstanceData());//Create instance of a cube

		//This is good, for tutorial, but in production depth test should be enabled on only when needed
		rapi->enableDepthTest();

		//Set default camera's settings
		cams[camMode]->applyRenderingSettings();
		//Emulate button delay, as it is not supported by this version of FW (nor by Freya)
		unsigned  camCallTime = oldTime;
		unsigned  bumpCallTime = oldTime;
		//Change exclusive access mode (to enable  mouse)
		//wm->grabInput(true);

		//Create desired textures and set their filtering to LINEAR_MIPMAP_LINEAR
		//Diffuse texture
		std::cout << "Loading textures..." << std::endl;
		//Get the resource manager
		//All loading are going to be synchronous so far
		//Also, this example is to primitive to manage resources fully and manually.
		resources::ResourceManager*	rm = core::EngineCore::getResourceManager();

		unsigned tex_load_start = wm->getTickCount();
		std::cout << "Loading diffuse texture" << std::endl;
		renderer::Texture* diffuse = rm->load(":tga:/Textures/diffuse.tga:mipmaps",resources::ResourceManager::IMMEDIATELY)->get<renderer::Texture*>();
		//renderer::Texture* diffuse = images::TGALoader::load("/earthmap.tga");
		diffuse->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
		//Specular texture (used to achieve more correct information about material specular propeties)
		std::cout << "Loading specular map" << std::endl;
		renderer::Texture* specular = rm->load(":tga:/Textures/specular.tga:mipmaps",resources::ResourceManager::IMMEDIATELY)->get<renderer::Texture*>();
		specular->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
		//Normal texture. Used to achieve the bumpmapping technique
		std::cout << "Loading normal map" << std::endl;
		renderer::Texture* bump = rm->load(":tga:/Textures/normal.tga:mipmaps",resources::ResourceManager::IMMEDIATELY)->get<renderer::Texture*>();
		//renderer::Texture* bump = images::TGALoader::load("/earthbump.tga");
		bump->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
		//Fake texture. Used to show rendering without bumpmapping. Contains value, corresponding to (0,0,1) normal in tangent space
		std::cout << "Loading fake normal map" << std::endl;
		renderer::Texture* fake = rm->load(":tga:/Textures/fake_normal.tga:mipmaps",resources::ResourceManager::IMMEDIATELY)->get<renderer::Texture*>();
		fake->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
		std::cout << "Textures loaded in " << (wm->getTickCount() - tex_load_start)*0.001 << " seconds" << std::endl;
		//Are we using bumpmapping technique?
		bool useBump = true;
		//Set the diffuse texture to a cube. Texture will be bound to 0 unit
		cube.setDiffuse(diffuse);
		sphere.setDiffuse(diffuse);
		//Set the specular texture to a cube. Texture will be bound to first unit
		specular->setUnit(renderer::TextureUnit::TEXTURE1);
		cube.setSpecular(specular);
		sphere.setSpecular(specular);
		//Set the specular texture to a cube. Texture will be bound to second unit
		bump->setUnit(renderer::TextureUnit::TEXTURE2);
		fake->setUnit(renderer::TextureUnit::TEXTURE2);
		cube.setBump(bump);
		sphere.setBump(bump);
		//fine, let us set lighting
		//Initial position of our light source
		math::vector3d lightPos(1.5,1.5,1.5);
		//math::vector3d lightPos(0,10.5,0);
		//Cube for visualation of light position
		primitives::Cube lightSource;
		//Instance of light position source
		//Please NOTE: we create two different cubes (and thus instances, belonging to different cubes) because cubes have different textures and shaders
		lightSource.addInstance(renderer::InstanceData());
		//Let's load shader sources
		//First, create a shader container
		renderer::Shader* shader = rapi->createShader();
		//Load vertex shader source code
		std::cout << "Loading shaders" << std::endl;
		size_t sz;
		char* data = reinterpret_cast<char*>(fs->read("/Shaders/bump.vert",&sz));
		EString vertex(data,sz);
		core::memory::Free(data,2);
		data = reinterpret_cast<char*>(fs->read("/Shaders/bump.frag",&sz));
		EString fragment(data,sz);
		core::memory::Free(data,2);
		shader->addShaders(vertex,fragment);
		//And finally link
		shader->link();
		//Set freshly linked shader to our cube to automate various uniform setting
		cube.setShader(shader);
		sphere.setShader(shader);
		//Applications main loop
		//FPS
		unsigned start = wm->getTickCount(),frames = 0;
		while(Core.isRunning())
		{
			//Get the time moment from framework start (in ms)
			newTime = wm->getTickCount();
			secs = (newTime - oldTime)*0.001; //Seconds passed
			//Update event queue
			wm->updateEvents();
			//Check the input devices state
			{
				//Check for escape
				if(kbd->getKeyState(KeyboardKeys::KEY_ESCAPE))
					Core.shutdown();
				//Check whether we need to change camera
				if(kbd->getKeyState(KeyboardKeys::KEY_C))
					if((newTime - camCallTime) > 300) //if more than 300 ms passed, then change camera
					{
						camMode = (camMode + 1) % 2;
						camCallTime = newTime;
					}
				//Check whether we need to change rendering mode
				if(kbd->getKeyState(KeyboardKeys::KEY_B))
					if((newTime - bumpCallTime) > 300) //if more than 300 ms passed, then change mode
					{
						if(useBump) //We are using bump mapping?
						{
							cube.setBump(fake);//Not anymore, haha
							sphere.setBump(fake);
							useBump = false;
						}
						else
						{
							cube.setBump(bump);
							sphere.setBump(bump);
							useBump = true;
						}
						bumpCallTime = newTime;
					}
				//Settings for rotate camera
				//Key setting for a "rotate camera"
				if(camMode == 0)
				{
					if(kbd->getKeyState(KeyboardKeys::KEY_LEFT))
						//Rotate CW along y axis
						cams[0]->changeYaw(-secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_RIGHT))
						//Rotate CCW along y axis
						cams[0]->changeYaw(+secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_UP))
						//Rotate CCW along x axis
						cams[0]->changePitch(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_DOWN))
						//Rotate CW along X axis
						cams[0]->changePitch(-secs*0.5);
				}
				else
				{
					//Simply no comments, code is pretty human readable
					if(kbd->getKeyState(KeyboardKeys::KEY_A))
						cams[1]->moveLeft(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_D))
						cams[1]->moveRight(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_W))
						cams[1]->moveForward(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_S))
						cams[1]->moveBackward(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_UP))
						cams[1]->moveUp(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_DOWN))
						cams[1]->moveDown(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_LEFT))
						cams[1]->changeYaw(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_RIGHT))
						cams[1]->changeYaw(-secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_E))
						cams[1]->changePitch(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_Q))
						cams[1]->changePitch(-secs*0.5);

					// Uncoment this to enable mouse. Yet by the time it does not work good in SDL 1.3
					//int x,y;
					//mouse->relativeState(&x,&y);
					//cams[1]->changeYaw(-secs*x*0.9);
					//cams[1]->changePitch(secs*y*0.9);
				}
			}//End of fake paranthesis for input handling
			//Clear color and depth buffer
			rapi->clearColor();
			rapi->clearDepth();

			//Set the light and camera position to the shader
			shader->setUniform("lightPos",lightPos);
			shader->setUniform("eyePos",cams[camMode]->getPos());
			//Render cube
			sphere.render();
			//cube.render();
			//Save matrix state
			rapi->pushMatrix();
			//Translate to light position
			rapi->translate(lightPos);
			//Scale light source cube
			rapi->scale(0.05,0.05,0.05);
			//Render light source
			lightSource.render();
			//Restore matrix state
			rapi->popMatrix();
			//Swap buffers

			//Apply camera transformation
			cams[camMode]->apply();
			//Swap buffers (one of the most costly command)
			wm->swapBuffers();

			//Animate light source
			math::quaternion  lightRot(math::vector3d(-1,0,0),math::pi*secs/2); //Rotate with 0.25 hertz speed
			lightPos = lightRot.rotate(lightPos);
			//Swap time values
			oldTime = newTime;
			frames++;

		}
		std::cout << "FPS: " << (float)frames/((wm->getTickCount() - start)*0.001f) << std::endl;
	}
	//Check whether everythig is going fine
	catch(EngineException& ex)
	{
		//Something failed. Ansi c++ standart gurantees that all stack object will be release at this point.
		std::cout << ex.message() << std::endl;
	}
	//Everything is fine, just exit (again, all stack allocated object are cleared
	return 0;
}
