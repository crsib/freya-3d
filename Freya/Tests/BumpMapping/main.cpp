/*
 * main.cpp
 *
 *  Created on: 02.03.2009
 *      Author: vedenko
 */
#include "freya.h"
#include <iostream>

#include "core/lua/LuaCore.h"

unsigned   frames = 0;
float      fps;
char	   fpsbuf[8];
bool	   fpsup = false;

char	   memory_buf[255];
bool	   mem_buf_up = false;

namespace core
{
namespace memory {
#ifdef _FREYA_DEBUG_MEMORY
extern EXPORT unsigned memory_allocated;
extern EXPORT unsigned allocated_for_buffers;
#endif
}
}

#ifdef _MSC_VER
#include <windows.h>
LONGLONG 	freq;
LONGLONG    count = 0;
#endif

void	format_memory()
{
	if(core::memory::memory_allocated > 1024*1024)
		sprintf(memory_buf,"%5.5f Mb / %5.5f Mb", core::memory::memory_allocated / (1024.0*1024.0),core::memory::allocated_for_buffers / (1024.0*1024.0));
	else if(core::memory::memory_allocated > 1024)
		sprintf(memory_buf,"%3.5f Kb / %5.5f Mb", core::memory::memory_allocated / (1024.0),core::memory::allocated_for_buffers / (1024.0*1024.0));
	else if(core::memory::memory_allocated > 1024*1024)
		sprintf(memory_buf,"%i B / %5.5f mb", core::memory::memory_allocated ,core::memory::allocated_for_buffers / (1024.0*1024.0));
	mem_buf_up = true;
}

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
		lastf = lastt;
		//
	}

	virtual
	int operator() ()
	{
		newt = wm->getTickCount();

		CEGUI::System::getSingleton().injectTimePulse((newt-lastf)*0.001);
		lastf = newt;
		if((newt - lastt) > 1000 ) //Update once per second
		{
			fps  = frames * 1000.0f / float(newt-lastt);
			lastt = newt;
			frames = 0;
			sprintf(fpsbuf,"% 5.2f",fps);
			fpsup = true;
			format_memory();
		}
		return FPSCounter::SECONDARY_THREAD;
	}
private:
	unsigned lastt;
	unsigned lastf;
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
		fpsv  = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive(3);
		mem  = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("Root/Memory");
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
		m_Cameras[m_CamMode]->apply();

		rapi->clearColorValue(0.3,0.4,0.5,1.0);
		rapi->clearColor();
		rapi->clearDepth();
		rapi->beginScene();
		//*
		//Set the light and camera position to the shader
		shader->setUniform("lightPos",lightPos);
		shader->setUniform("eyePos",m_Cameras[m_CamMode]->getPos());
		//Render cube/sphere
		rapi->setMatrix(renderer::Matrix::MODEL,math::matrix4x4::identity);
		m_Sphere->render();
		//Translate to light position
		math::matrix4x4 transf = math::matrix4x4::translationMatrix(lightPos)*math::matrix4x4::scaleMatrix(0.05,0.05,0.05);
		rapi->setMatrix(renderer::Matrix::MODEL,transf);
		lightSource->render();

		//*/
		if(fpsup)
		{
			fpsv->setText(CEGUI::String(fpsbuf));
			fpsup = false;
		}

		if(mem_buf_up)
		{
			mem->setText(memory_buf);
			mem_buf_up = false;
		}

		core::EngineCore::getCEGUISystem()->renderGUI();

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
	CEGUI::Window*				fpsv;
	CEGUI::Window*				mem;

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
		mbut = wm->createKeyDrivenDevice("mouse_buttons");
		oldTime = bumpCallTime = camCallTime = wm->getTickCount();
		lightPos = math::vector3d (1.5,1.5,1.5);
		bumpEnable_w = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive(10);
		x_pos = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive(1000);
		y_pos = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive(1001);
	}
	virtual
	int operator() ()
	{
		//#define PROFILE_UPDATE
#if defined(_MSC_VER) && defined(PROFILE_UPDATE)
		QueryPerformanceCounter((LARGE_INTEGER*)(&count));
#endif
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
							bumpEnable_w->setProperty("Selected","False");
						}
						else
						{
							m_Cube->setBump(bump);
							m_Sphere->setBump(bump);
							m_UseBump = true;
							bumpEnable_w->setProperty("Selected","True");
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

				}
				int x = 0,y = 0;
				static unsigned left = 0;
				static unsigned right = 0;
				mouse->absoluteState(&x,&y);

				if(left == 0)
					sprintf(tbuf,"%i",x);
				else
					sprintf(tbuf,"lft");
				x_pos->setText(tbuf);
				sprintf(tbuf,"%4i",y);
				y_pos->setText(tbuf);

				CEGUI::System::getSingleton().injectMousePosition(x,y);

				if(mbut->getKeyState(windowmanager::input::BUTTON_LEFT))
				{
					if(left == 0)
					{
						CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
						left = 1;

					}
				}
				else if(left)
				{
					CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
					left = 0;
				}

				if(mbut->getKeyState(windowmanager::input::BUTTON_RIGHT))
				{
					if(right == 0)
					{
						CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
						right = 1;
					}
				}
				else if(right)
				{
					CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
					right = 0;
				}
				if(m_CamMode)
				{
					//m_Cameras[1]->changeYaw(secs*x*0.5);
					//	m_Cameras[1]->changePitch(secs*y*0.5);
					//std::cout << x << " " << y << std::endl;
				}
			}//End of fake paranthesis for input handling
			//Animate light source
			math::quaternion  lightRot = math::quaternion::rotationQuat(math::pi*secs/2,math::vector3d(-1,0,0)); //Rotate with 0.25 hertz speed
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
#if defined(_MSC_VER) && defined(PROFILE_UPDATE)
		LARGE_INTEGER new_val;
		QueryPerformanceCounter(&new_val);
		__int64 dif = new_val.QuadPart - count;
		count = new_val.QuadPart;
		std::cout << "Time for update task : " << (double)(dif)/freq << std::endl;
#endif
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
	windowmanager::input::KeyDrivenDevice*	 mbut;
	windowmanager::input::MovementDrivenDevice* mouse;
	renderer::Texture*						bump;
	renderer::Texture*						fake;
	BumpmappingRender*						renderer;
	math::vector3d							lightPos;
	CEGUI::Window*							bumpEnable_w;
	char									tbuf[5];
	CEGUI::Window*							x_pos;
	CEGUI::Window*							y_pos;
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
		static resources::Resource* shader_r;
		static unsigned camMode = 0;
		static unsigned tex_load_start;
		if(!m_RendererStarted)
		{
#ifdef _MSC_VER && defined(PROFILE_UPDATE)
			QueryPerformanceFrequency((LARGE_INTEGER*)(&freq));
			if(freq == 0)
				freq = 1;
			QueryPerformanceCounter((LARGE_INTEGER*)(&count));
#endif
			//Get the address of WindowManger instance
			core::EngineCore::createWindowManager("SDL");
			core::EngineCore::getTaskManager()->setThreadNumber(2);
			wm = core::EngineCore::getWindowManager();
			wm->setQuitCallback(windowmanager::Callback(_quit));
			//Mount filesystems
			fs = core::EngineCore::getFilesystem();
			fs->mount("pwd");
			fs->mount("lzma","Textures.7z");
			fs->mount("lzma","StdGUI.7z");
			fs->mount("lzma","StdShaders.7z");

			//Create window
			windowmanager::WindowFormat*	fmt = new windowmanager::WindowFormat;
			fmt->Multisampled = true;
			fmt->MultisampleSamples = 8;
			fmt->VSync = false;
			wm->setWindowFormat(fmt);
			delete fmt;
			wm->showCursor(false);
			wm->grabInput(true);
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
			core::EngineCore::createRenderingDriver(renderer::futures::MULTITEXTURE | renderer::futures::VERTEX_BUFFER | renderer::futures::TEXTURE_BUFFER |
					renderer::futures::VERTEX_SHADER | renderer::futures::FRAGMENT_SHADER);
			//Get the address of rendering subsystem
			rapi = core::EngineCore::getRenderingDriver();
			//Set the clear color value
			rapi->clearColorValue(0.3,0.4,0.5,1.0);
			rapi->clearColor();
			rapi->clearDepth();
			wm->swapBuffers();
			//Create keyboard and mouse
			//windowmanager::input::KeyDrivenDevice* kbd = wm->createKeyDrivenDevice("keyboard");
			//windowmanager::input::MovementDrivenDevice* mouse = wm->createMovementDrivenDevice("mouse");
			//Time variables. We need to know, how much time previuos frame has taken to do the correct animation/camera controlling
			unsigned oldTime = wm->getTickCount(),newTime;
			float secs;
			//Set up view parameters.
			rapi->setViewport(0,0,winWidth,winHeight);



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

			shader_r = rm->load(":shader:vertex:/Shaders/bump.vert:fragment:/Shaders/bump.frag");

		}
		while(!diffuse_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!specular_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!bump_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!fake_r->ready())
			return core::taskmanager::Task::MAIN_THREAD;
		while(!shader_r->ready())
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
		//specular->setUnit(renderer::TextureUnit::TEXTURE1);
		cube->setSpecular(specular);
		sphere->setSpecular(specular);
		//Set the specular texture to a cube-> Texture will be bound to second unit
		//bump->setUnit(renderer::TextureUnit::TEXTURE2);
		//fake->setUnit(renderer::TextureUnit::TEXTURE2);
		cube->setBump(bump);
		sphere->setBump(bump);
		//fine, let us set lighting
		//Initial position of our light source
		math::vector3d lightPos(1.5,1.5,1.5);
		//math::vector3d lightPos(0,10.5,0);
		//Cube for visualation of light position
		primitives::Cube* lightSource = new primitives::Cube;

		renderer::Shader* shader = shader_r->get<renderer::Shader*>();
		//shader->link();
		//Set freshly linked shader to our cube to automate various uniform setting
		cube->setShader(shader);
		sphere->setShader(shader);
		lightSource->setShader(shader);

		lightSource->setDiffuse(diffuse);
		lightSource->setSpecular(specular);
		lightSource->setBump(fake);

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
		core::EngineCore::startCEGUI();
		CEGUI::System::getSingleton().getRenderer()->setDisplaySize(CEGUI::Size(winWidth,winHeight));
		CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

		CEGUI::FontManager::getSingleton().create( "DejaVuSans-10.font" );

		CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );

		{
			using namespace CEGUI;
			Window* root = WindowManager::getSingleton().loadWindowLayout( "BumpMapping.layout" );
			System::getSingleton().setGUISheet( root );
			root->getChildRecursive(5)->setText(String(core::EngineCore::getRenderingDriver()->getRendererName().c_str()));
			root->getChildRecursive(4)->setText(String((core::EngineCore::getRenderingDriver()->getAPIName() + " " + core::EngineCore::getRenderingDriver()->getShaderAPIName()).c_str()));

			Window*	descr = WindowManager::getSingleton().getWindow("Root/desc");
			descr->setText(
					"\'C\' - toggle camera mode (rotate/flight)\n"
					"\'B\' - toggle bumpmapping on/of\n"
					"Rotate camera mode:\n"
					"Arrows - angle control\n"
					"Flight camera:\n"
					"\'W\',\'A\',\'S\',\'D\',Up,Down - move\n"
					"\'Q\',\'E\' - change pitch\n"
					"Left/Right - rotate left/right");
		}

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
	core::EngineCore* Core = NULL;
	try
	{
		std::cout << "Starting engine" << std::endl;
		Core = new core::EngineCore(argC,argV,"BumpMapping");
		core::EngineCore::getTaskManager()->addTask(new Initialize);
		//core::EngineCore::getTaskManager()->setThreadNumber(3);
		core::EngineCore::getTaskManager()->enterMainLoop();
		std::cout << "FPS: " << fps << std::endl;
		delete Core;
	}
	catch(EngineException& ex)
	{
		//Something failed. Ansi c++ standart gurantees that all stack object will be release at this point.
		std::cout << "[ENGINE]: "<< ex.message() << std::endl;
		delete Core;
	}
	catch(std::exception& ex)
	{
		std::cout << "[STD]: "<< ex.what() << std::endl;
		delete Core;
	}
	catch(...)
	{
		std::cout << "Unknown exception" << std::endl;
		delete Core;
	}
	//Everything is fine, just exit (again, all stack allocated object are cleared
	return 0;
}
