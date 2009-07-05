/*
 * OpenGLSDLAPIInit.cpp
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#include "OpenGLSDLAPIInit.h"
#include <SDL/SDL.h>

namespace windowmanager
{
namespace drivers
{

namespace sdl
{
OpenGLSDLAPIInit::OpenGLSDLAPIInit()
{
	m_RedSize 		=	8;
	m_GreenSize		=	8;
	m_BlueSize		=	8;
	m_AlphaSize		=	8;

	m_Doublebuffer 	=	1;

	m_BufferSize		=	32;
	m_DepthSize		=	24;
	m_StencilSize		=	8;

	m_AccumRedSize	=	0;
	m_AccumGreenSize	=	0;
	m_AccumBlueSize	=	0;
	m_AccumAlphaSize  =   0;
#ifndef MACOSX_SOFTWARE
	m_Accelerated     =   1;
#else
	m_Accelerated     =   0;
#endif

}

OpenGLSDLAPIInit::~OpenGLSDLAPIInit()
{

}

unsigned OpenGLSDLAPIInit::getAPI_ID()
{
	return 0;
}

void OpenGLSDLAPIInit::setupAPI()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,m_RedSize);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,m_GreenSize);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,m_BlueSize);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,m_AlphaSize);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,m_Doublebuffer);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,m_BufferSize);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,m_DepthSize);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,m_StencilSize);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,m_AccumRedSize);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,m_AccumGreenSize);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,m_AccumBlueSize);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,m_AccumAlphaSize);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,m_Accelerated);
}

}
}
}
