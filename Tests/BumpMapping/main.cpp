/*
 * main.cpp
 *
 *  Created on: 02.03.2009
 *      Author: vedenko
 */
#include "freya.h"
#include <iostream>

unsigned   frames = 0;
float      fps;

unsigned   active = 1;
int winWidth = 640,winHeight = 640;
const bool	fullscreen = false;

void	_quit() //Quit callback
{
	active = 0;
}

class FPSCounter 		: public core::taskmanager::Task
{
public:
	FPSCounter()
	{
		wm = core::EngineCore::getWindowManager();
		lastt = wm->getTickCount();
	}

	virtual
	int operator() ()
	{
		newt = wm->getTickCount();
		if((newt - lastt) > 1000 ) //Update once per second
		{
			fps  = frames * 1000.0f / float(newt-lastt);
			lastt = newt;
			frames = 0;
			std::stringstream str;
			str << "Bump Mapping Demo [FPS " << fps << "]";
			wm->setCaption(str.str().c_str());
		}
		return FPSCounter::SECONDARY_THREAD;
	}
private:
	unsigned lastt;
	unsigned newt;
	windowmanager::WindowManagerDriver*	wm;
};

class BumpmappingRender : public core::taskmanager::Task
{
public:
	BumpmappingRender (unsigned& camMode,camera::BasicCamera** cameras,primitives::Sphere<30,30>* sphere,	primitives::Cube* cube,bool& useBump,
			renderer::Shader* Shader,primitives::Cube*	LightSource)
	: m_CamMode(camMode), m_Cameras(cameras),m_Sphere(sphere),m_Cube(cube),m_UseBump(useBump), shader(Shader), lightSource(LightSource)
	  {
		rapi = core::EngineCore::getRenderingDriver();
		wm = core::EngineCore::getWindowManager();
	  }
	virtual ~BumpmappingRender()
	{
		std::cout << "Destroying BumpmappingRender" << std::endl;
		delete lightSource;
	}
	virtual
	int operator() ()
	{
		if(!core::EngineCore::getResourceManager()->isReady())
			return BumpmappingRender::MAIN_THREAD;
		//Clear color and depth buffer
		rapi->clearColor();
		rapi->clearDepth();
		rapi->beginScene();
		//Set the light and camera position to the shader
		shader->setUniform("lightPos",lightPos);
		shader->setUniform("eyePos",m_Cameras[m_CamMode]->getPos());
		//Render cube
		m_Sphere->render();
		//cube->render();
		//Save matrix state
		rapi->pushMatrix();
		//Translate to light position
		rapi->translate(lightPos);
		//Scale light source cube
		rapi->scale(0.05,0.05,0.05);
		//Render light source
		lightSource->render();
		//Restore matrix state
		rapi->popMatrix();
		//Swap buffers

		//Apply camera transformation
		m_Cameras[m_CamMode]->apply();
		//Swap buffers (one of the most costly command)
		rapi->endScene();
		wm->swapBuffers();
		frames++;
		return BumpmappingRender::MAIN_THREAD;
	}

	void setLightPos(const math::vector3d& vec)
	{
		lightPos = vec;
	}
private:
	unsigned&					m_CamMode;
	camera::BasicCamera** 		m_Cameras;
	primitives::Sphere<30,30>* 	m_Sphere;
	primitives::Cube*		   	m_Cube;
	bool&						m_UseBump;

	renderer::RenderingAPIDriver* 		rapi;
	windowmanager::WindowManagerDriver* wm;
	renderer::Shader*					shader;
	primitives::Cube*					lightSource;
	math::vector3d						lightPos;

};

class HandleInput 		: public core::taskmanager::Task
{
public:
	HandleInput (unsigned& camMode,camera::BasicCamera** cameras,primitives::Sphere<30,30>* sphere,
			primitives::Cube* cube,bool& useBump,renderer::Texture* Bump,renderer::Texture* Fake,
			BumpmappingRender*						Renderer)
	: m_CamMode(camMode), m_Cameras(cameras),m_Sphere(sphere),m_Cube(cube),m_UseBump(useBump), bump(Bump), fake(Fake),
	  renderer(Renderer)
	  {
		wm = core::EngineCore::getWindowManager();
		kbd = wm->createKeyDrivenDevice("keyboard");
		mouse = wm->createMovementDrivenDevice("mouse");
		oldTime = bumpCallTime = camCallTime = wm->getTickCount();
		lightPos = math::vector3d (1.5,1.5,1.5);
	  }
	virtual
	int operator() ()
	{
		if(active)
		{
			newTime = wm->getTickCount();
			secs = (newTime - oldTime)*0.001; //Seconds passed
			//Update event queue
			wm->updateEvents();
			//Check the input devices state
			{
				//Check for escape
				if(kbd->getKeyState(KeyboardKeys::KEY_ESCAPE))
					active = 0;
				//Check whether we need to change camera
				if(kbd->getKeyState(KeyboardKeys::KEY_C))
					if((newTime - camCallTime) > 300) //if more than 300 ms passed, then change camera
					{
						m_CamMode = (m_CamMode + 1) % 2;
						camCallTime = newTime;
					}
				//Check whether we need to change rendering mode
				if(kbd->getKeyState(KeyboardKeys::KEY_B))
					if((newTime - bumpCallTime) > 300) //if more than 300 ms passed, then change mode
					{
						if(m_UseBump) //We are using bump mapping?
						{
							m_Cube->setBump(fake);//Not anymore, haha
							m_Sphere->setBump(fake);
							m_UseBump = false;
						}
						else
						{
							m_Cube->setBump(bump);
							m_Sphere->setBump(bump);
							m_UseBump = true;
						}
						bumpCallTime = newTime;
					}
				//Settings for rotate camera
				//Key setting for a "rotate camera"
				if(m_CamMode == 0)
				{
					if(kbd->getKeyState(KeyboardKeys::KEY_LEFT))
						//Rotate CW along y axis
						m_Cameras[0]->changeYaw(-secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_RIGHT))
						//Rotate CCW along y axis
						m_Cameras[0]->changeYaw(+secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_UP))
						//Rotate CCW along x axis
						m_Cameras[0]->changePitch(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_DOWN))
						//Rotate CW along X axis
						m_Cameras[0]->changePitch(-secs*0.5);
				}
				else
				{
					//Simply no comments, code is pretty human readable
					if(kbd->getKeyState(KeyboardKeys::KEY_A))
						m_Cameras[1]->moveLeft(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_D))
						m_Cameras[1]->moveRight(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_W))
						m_Cameras[1]->moveForward(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_S))
						m_Cameras[1]->moveBackward(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_UP))
						m_Cameras[1]->moveUp(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_DOWN))
						m_Cameras[1]->moveDown(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_LEFT))
						m_Cameras[1]->changeYaw(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_RIGHT))
						m_Cameras[1]->changeYaw(-secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_E))
						m_Cameras[1]->changePitch(secs*0.5);
					if(kbd->getKeyState(KeyboardKeys::KEY_Q))
						m_Cameras[1]->changePitch(-secs*0.5);

					// Uncoment this to enable mouse. Yet by the time it does not work good in SDL 1.3

					wm->grabInput(true);
					wm->showCursor(false);

					if(m_CamMode)
					{
						int x = 0,y = 0;
						mouse->relativeState(&x,&y);
						//m_Cameras[1]->changeYaw(secs*x*0.5);
						//m_Cameras[1]->changePitch(secs*y*0.5);
					}

				}
			}//End of fake paranthesis for input handling
			//Animate light source
			math::quaternion  lightRot(math::vector3d(-1,0,0),math::pi*secs/2); //Rotate with 0.25 hertz speed
			lightPos = lightRot.rotate(lightPos);
			renderer->setLightPos(lightPos);
			//Swap time values
			oldTime = newTime;
		}
		else
		{
			core::EngineCore::shutdown();
			delete m_Cube;
			delete m_Sphere;
			delete m_Cameras[0];
			delete m_Cameras[1];
		}
		return HandleInput::MAIN_THREAD;
	}
private:
	unsigned&					m_CamMode;
	camera::BasicCamera** 		m_Cameras;
	primitives::Sphere<30,30>* 	m_Sphere;
	primitives::Cube*		   	m_Cube;
	bool&						m_UseBump;
	unsigned  camCallTime ;
	unsigned  bumpCallTime ;
	unsigned  oldTime;
	unsigned  newTime;
	float 	  secs;
	windowmanager::WindowManagerDriver*		wm;
	windowmanager::input::KeyDrivenDevice*   kbd;
	windowmanager::input::MovementDrivenDevice* mouse;
	renderer::Texture*						bump;
	renderer::Texture*						fake;
	BumpmappingRender*						renderer;
	math::vector3d							lightPos;
};

class Initialize		: public core::taskmanager::Task
{
public:
	Initialize() : m_RendererStarted(0)
	{}
	virtual
	int operator() ()
	{
		static core::filesystem::Filesystem*	fs ;
		static windowmanager::WindowManagerDriver* wm ;
		static renderer::RenderingAPIDriver*		rapi ;
		static resources::ResourceManager*	rm ;
		static resources::Resource*	diffuse_r;
		static resources::Resource*	specular_r;
		static resources::Resource*	bump_r;
		static resources::Resource*	fake_r;
		static unsigned camMode = 0;
		static unsigned tex_load_start;
		if(!m_RendererStarted)
		{
			//Get the address of WindowManger instance
			core::EngineCore::createWindowManager("SDL");
			core::EngineCore::getTaskManager()->setThreadNumber(2);
			wm = core::EngineCore::getWindowManager();
			wm->setQuitCallback(windowmanager::Callback(_quit));
			//Mount filesystems
			fs = core::EngineCore::getFilesystem();
			fs->mount("pwd");
			fs->mount("lzma","Textures.7z");

			//Create window
			windowmanager::WindowFormat*	fmt = new windowmanager::WindowFormat;
			fmt->Multisampled = true;
			fmt->MultisampleSamples = 8;
			wm->setWindowFormat(fmt);
			delete fmt;
			wm->setWindowedModeWindowSize(winWidth,winHeight);
			windowmanager::DisplayMode*	mode = wm->getDisplayMode(0);
			std::cout << "Default fs mode is " << mode->width << "x" << mode->height << "@" << mode->refreshRate << std::endl;
			wm->setFullscreenWindowMode((unsigned)0);
			wm->toggleFullscreen(fullscreen);
			if(fullscreen)
			{
				winWidth = mode->width;
				winHeight = mode->height;
			}
			wm->setCaption("Bump Mapping Demo");
			//wm->createWindow(winWidth,winHeight,"Tutorial 1: Bump mapping",fullscreen ,NULL);
			//Start rendering subsystem
			core::EngineCore::createRenderingDriver(renderer::futures::MULTITEXTURE | renderer::futures::AUTO_TRANSPOSE_MATIRIX | renderer::futures::VERTEX_BUFFER | renderer::futures::TEXTURE_BUFFER |
					renderer::futures::VERTEX_SHADER | renderer::futures::FRAGMENT_SHADER);
			//Get the address of rendering subsystem
			rapi = core::EngineCore::getRenderingDriver();
			//Set the clear color value
			rapi->clearColorValue(0.3,0.4,0.5,1.0);
			rapi->clearColor();
			rapi->clearDepth();
			wm->swapBuffers();
			//Create keyboard and mouse
			windowmanager::input::KeyDrivenDevice* kbd = wm->createKeyDrivenDevice("keyboard");
			//windowmanager::input::MovementDrivenDevice* mouse = wm->createMovementDrivenDevice("mouse");
			//Time variables. We need to know, how much time previuos frame has taken to do the correct animation/camera controlling
			unsigned oldTime = wm->getTickCount(),newTime;
			float secs;
			//Set up view parameters.
			rapi->setViewport(winWidth,winHeight);



			//This is good, for tutorial, but in production depth test should be enabled on only when needed
			rapi->enableDepthTest();

			//Set default camera's settings
			//cams[camMode]->applyRenderingSettings();
			//Create desired textures and set their filtering to LINEAR_MIPMAP_LINEAR
			//Diffuse texture
			m_RendererStarted = 1;
			std::cout << "Loading textures..." << std::endl;
			//Get the resource manager
			//All loading are going to be synchronous so far
			//Also, this example is to primitive to manage resources fully and manually.
			rm = core::EngineCore::getResourceManager();
			tex_load_start = wm->getTickCount();

			std::cout << "Loading diffuse texture" << std::endl;
			diffuse_r = rm->load(":tga:/Textures/diffuse.tga:mipmaps");

			//Specular texture (used to achieve more correct information about material specular propeties)
			std::cout << "Loading specular map" << std::endl;
			specular_r = rm->load(":tga:/Textures/specular.tga:mipmaps");
			//renderer::Texture* specular = rm->load(":tga:/Textures/specular.tga:mipmaps",resources::ResourceManager::IMMEDIATELY)->get<renderer::Texture*>();
			//specular->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
			//Normal texture. Used to achieve the bumpmapping technique
			std::cout << "Loading normal map" << std::endl;

			bump_r = rm->load(":tga:/Textures/normal.tga:mipmaps");
			//renderer::Texture* bump = images::TGALoader::load("/earthbump.tga");

			//Fake texture. Used to show rendering without bumpmapping. Contains value, corresponding to (0,0,1) normal in tangent space
			std::cout << "Loading fake normal map" << std::endl;
			fake_r = rm->load(":tga:/Textures/fake_normal.tga:mipmaps");

		}
		while(!diffuse_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!specular_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!bump_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!fake_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;

		renderer::Texture* diffuse = diffuse_r->get<renderer::Texture*>();
		diffuse->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);

		renderer::Texture* specular = specular_r->get<renderer::Texture*>();
		specular->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);

		renderer::Texture* bump 	= bump_r->get<renderer::Texture*>();
		renderer::Texture* fake     = fake_r->get<renderer::Texture*>();

		bump->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);
		fake->setMinFilter(renderer::TextureFiltering::LINEAR_MIPMAP_LINEAR);

		std::cout << "Textures loaded in " << (wm->getTickCount() - tex_load_start)*0.001 << " seconds" << std::endl;

		std::cout << "diffuse_r: " << (void*)diffuse_r << std::endl;
		std::cout << "specular_r: " << (void*)specular_r << std::endl;
		std::cout << "bump_r: " << (void*)bump_r << std::endl;
		std::cout << "fake_r: " << (void*)fake_r << std::endl;
		//Are we using bumpmapping technique?
		static bool useBump = true;
		//Sphere test
		static primitives::Sphere<30,30>* sphere = new primitives::Sphere<30,30>;
		//Create cube
		static primitives::Cube* cube = new primitives::Cube;
		//Set the diffuse texture to a cube-> Texture will be bound to 0 unit
		cube->setDiffuse(diffuse);
		sphere->setDiffuse(diffuse);
		//Set the specular texture to a cube-> Texture will be bound to first unit
		specular->setUnit(renderer::TextureUnit::TEXTURE1);
		cube->setSpecular(specular);
		sphere->setSpecular(specular);
		//Set the specular texture to a cube-> Texture will be bound to second unit
		bump->setUnit(renderer::TextureUnit::TEXTURE2);
		fake->setUnit(renderer::TextureUnit::TEXTURE2);
		cube->setBump(bump);
		sphere->setBump(bump);
		//fine, let us set lighting
		//Initial position of our light source
		math::vector3d lightPos(1.5,1.5,1.5);
		//math::vector3d lightPos(0,10.5,0);
		//Cube for visualation of light position
		primitives::Cube* lightSource = new primitives::Cube;
		//Instance of light position source
		//Please NOTE: we create two different cubes (and thus instances, belonging to different cubes) because cubes have different textures and shaders
		//Let's load shader sources
		//First, create a shader container
		renderer::Shader* shader = rapi->createShader();
		//Load vertex shader source code
		std::cout << "Loading shaders" << std::endl;
		size_t sz;
		char* data = reinterpret_cast<char*>(fs->read("/Shaders/bump.vert",&sz));
		EString vertex(data,sz);
		core::memory::Free(data,core::memory::GENERIC_POOL);
		data = reinterpret_cast<char*>(fs->read("/Shaders/bump.frag",&sz));
		EString fragment(data,sz);
		core::memory::Free(data,core::memory::GENERIC_POOL);
		shader->addShaders(vertex,fragment);
		//And finally link
		shader->link();
		//Set freshly linked shader to our cube to automate various uniform setting
		cube->setShader(shader);
		sphere->setShader(shader);

		//Create two cameras (fly and rotate)
		//Rotate camera by default
		static camera::BasicCamera*	cams[] = {
				new camera::RotateCamera(math::vector3d(3.0,0.0,3.0),math::vector3d(-1.0,0,-1.0),math::vector3d(0.0,1.0,0.0),
						1.04,(float)winWidth/(float)winHeight,1,1000),
						new camera::FlyCamera(math::vector3d(3.0,0.0,3.0),math::vector3d(-1.0,0.0,-1.0),math::vector3d(0.0,1.0,0.0),
								1.04,(float)winWidth/(float)winHeight,1,1000)
		};

		//Initialization done
		cams[0]->applyRenderingSettings();
		BumpmappingRender*	renderer =  new BumpmappingRender(camMode,cams,sphere,cube,useBump,shader,lightSource);
		core::EngineCore::getTaskManager()->addTask(new HandleInput(camMode,cams,sphere,cube,useBump,bump,fake,renderer));
		core::EngineCore::getTaskManager()->addTask(renderer);
		core::EngineCore::getTaskManager()->addTask(new FPSCounter);
		return core::taskmanager::Task::DONE;
	}
private:
	unsigned 		m_RendererStarted;
	unsigned		m_SynResources;
};


int main(int argC,char** argV)
{
	//Create framework core::EngineCore:: Core is responsible on creating/managing various subsystems
	std::cout << "Starting engine" << std::endl;
	core::EngineCore Core(argC,argV,"BumpMapping");
	try
	{
		core::EngineCore::getTaskManager()->addTask(new Initialize);
		core::EngineCore::getTaskManager()->enterMainLoop();
		std::cout << "FPS: " << fps << std::endl;
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
	//Everything is fine, just exit (again, all stack allocated object are cleared
	return 0;
}
