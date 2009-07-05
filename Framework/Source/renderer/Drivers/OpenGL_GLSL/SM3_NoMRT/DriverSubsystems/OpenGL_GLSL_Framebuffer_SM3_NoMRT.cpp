/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_NoMRT.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRT/DriverSubsystems/OpenGL_GLSL_Texture_SM3_NoMRT.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL_GLSL_ConstantsTables.h"

#include "renderer/3DConstants.h"
namespace renderer
{
namespace drivers
{
namespace opengl_glsl_sm3_nomrt
{
OpenGL_GLSL_Framebuffer::OpenGL_GLSL_Framebuffer()
{
	glGenFramebuffersEXT(1,&m_Framebuffer);
	m_Width = m_Height = 0;
	m_Bounded = false;
	m_ReadBuffer = OpenGL_GLSL_Tables::FramebufferAttachment[FramebufferAttachment::COLOR_ATTACHMENT0];
	m_DrawBuffers.push_back(OpenGL_GLSL_Tables::FramebufferAttachment[FramebufferAttachment::COLOR_ATTACHMENT0]);
	glGetIntegerv ( GL_MAX_COLOR_ATTACHMENTS_EXT, &m_MaxColorAttachments );
}

OpenGL_GLSL_Framebuffer::~OpenGL_GLSL_Framebuffer()
{
	glDeleteFramebuffersEXT(1,&m_Framebuffer);
	for(RenderBufferListIterator it = m_RenderBuffers.begin();it != m_RenderBuffers.end();it++)
		glDeleteRenderbuffersEXT(1,&(*it));
	m_RenderBuffers.clear();
	m_DrawBuffers.clear();
}

void		OpenGL_GLSL_Framebuffer::setDimensions(unsigned width,unsigned height)
{
	m_Width = width;
	m_Height = height;
}

bool		OpenGL_GLSL_Framebuffer::bind()
{
	if((m_Framebuffer == 0) || (m_Width == 0) || (m_Height == 0)) return false;
	glFlush();
	glGetIntegerv(GL_VIEWPORT, m_OldViewport);
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_Framebuffer );
	glReadBuffer(m_ReadBuffer);
	glDrawBuffersARB(m_DrawBuffers.size(),&m_DrawBuffers[0]);
	glViewport(0, 0, m_Width, m_Height);
	m_Bounded = true;
	return true;
}

void		OpenGL_GLSL_Framebuffer::unbind()
{
	if(m_Bounded)
	{
		glFlush();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glViewport(m_OldViewport[0],m_OldViewport[1],m_OldViewport[2],m_OldViewport [3]);
		m_Bounded = false;
	}

}

void		OpenGL_GLSL_Framebuffer::attachRenderBuffer(unsigned attach_to,unsigned internalFormat)
{
	GLuint  rb;
	glGenRenderbuffersEXT(1,&rb);
	if(m_Bounded)
	{
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,rb);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,OpenGL_GLSL_Tables::TextureInternalFormat[internalFormat],m_Width,m_Height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],GL_RENDERBUFFER_EXT,rb);
	}
	else
	{
		GLint current;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT,&current);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,m_Framebuffer);

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,rb);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,OpenGL_GLSL_Tables::TextureInternalFormat[internalFormat],m_Width,m_Height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],GL_RENDERBUFFER_EXT,rb);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,current);
	}
	m_RenderBuffers.push_back(rb);
}

void		OpenGL_GLSL_Framebuffer::detachRenderBuffer(unsigned detach_from)
{
	if(m_Bounded)
	{
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[detach_from],GL_RENDERBUFFER_EXT,0);
	}
	else
	{
		GLint current;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT,&current);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,m_Framebuffer);

		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[detach_from],GL_RENDERBUFFER_EXT,0);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,current);
	}

}

void		OpenGL_GLSL_Framebuffer::	attachTexture(unsigned attach_to,const Texture* tex,unsigned level)
{
	unsigned type = tex->getTextureType();
	if(m_Bounded)
	{
		switch(type)
		{
		case TextureType::TEXTURE_2D:
		case TextureType::TEXTURE_RECTANGLE:
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		case TextureType::TEXTURE_1D:
			glFramebufferTexture1DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		}
	}
	else
	{
		GLint current;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT,&current);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,m_Framebuffer);

		switch(type)
		{
		case TextureType::TEXTURE_2D:
		case TextureType::TEXTURE_RECTANGLE:
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		case TextureType::TEXTURE_1D:
			glFramebufferTexture1DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,current);
	}
}

void		OpenGL_GLSL_Framebuffer::	attachTexture(unsigned attach_to,const Texture* tex,unsigned side,unsigned level)
{
	unsigned type = tex->getTextureType();
	if(m_Bounded)
	{
		switch(type)
		{
		case TextureType::TEXTURE_CUBE:
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::CubeTextureSide[side],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		case TextureType::TEXTURE_3D:
			glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level,side);
			break;
		}
	}
	else
	{
		GLint current;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT,&current);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,m_Framebuffer);

		switch(type)
		{
		case TextureType::TEXTURE_CUBE:
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::CubeTextureSide[side],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level);
			break;
		case TextureType::TEXTURE_3D:
			glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT,OpenGL_GLSL_Tables::FramebufferAttachment[attach_to],OpenGL_GLSL_Tables::TextureType[type],static_cast<OpenGL_GLSL_Texture*>(const_cast<Texture*>(tex))->m_Texture,level,side);
			break;
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,current);
	}
}


void		OpenGL_GLSL_Framebuffer::	drawBuffers(unsigned size,unsigned* bufs)
{
	m_DrawBuffers.clear();
	for(unsigned i = 0; i < size; i++)
		m_DrawBuffers.push_back(OpenGL_GLSL_Tables::FramebufferAttachment[bufs[i]]);
}

void		OpenGL_GLSL_Framebuffer::readBuffer(unsigned buf)
{
	m_ReadBuffer = OpenGL_GLSL_Tables::FramebufferAttachment[buf];
}

unsigned		OpenGL_GLSL_Framebuffer::maxColorAttachments() const
{
	return m_MaxColorAttachments;
}

unsigned		OpenGL_GLSL_Framebuffer::status() const
{
	unsigned status;
	if(m_Bounded)
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) - GL_FRAMEBUFFER_COMPLETE_EXT;
	else
	{
		GLint current;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT,&current);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,m_Framebuffer);
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) - GL_FRAMEBUFFER_COMPLETE_EXT;
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,current);
	}
	return status;
}


}
}
}
