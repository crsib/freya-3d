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

int main()
{
	core::EngineCore core;
	try
	{
		//Start up WM and renderer
		core.createWindowManager("SDL");

		windowmanager::WindowManagerDriver* wm = core.getWindowManager();
		wm->createWindow(winWidth,winHeight,"Resource manager test",false,NULL);

		core.createRenderingDriver("OpenGL GLSL SM4");
		renderer::RenderingAPIDriver*		rapi = core.getRenderingDriver();

	}
	catch(EngineException& ex)
	{
		cout << ex.message() << endl;
	}
	return 0;
}
