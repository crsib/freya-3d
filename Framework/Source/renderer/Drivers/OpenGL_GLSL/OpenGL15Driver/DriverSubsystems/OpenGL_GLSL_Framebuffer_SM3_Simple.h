/*This header was generated from Framebuffer.h for Freya engine */
#ifndef OPENGL_GLSL_FRAMEBUFFER_H
#define OPENGL_GLSL_FRAMEBUFFER_H

#include "renderer/DriverSubsystems/Framebuffer.h"

#include "core/memory/MemoryAllocator.h"
#include <list>
#include <vector>
extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}

#include "renderer/DriverSubsystems/Texture.h"

namespace renderer
{
namespace drivers
{
namespace opengl_glsl_15
{
class	OpenGL_GLSL_Framebuffer : public Framebuffer
{
	friend class OpenGL_GLSL_Driver;
protected:
	OpenGL_GLSL_Framebuffer();
	virtual ~OpenGL_GLSL_Framebuffer();
public:

	typedef std::list<GLuint,core::memory::MemoryAllocator<GLuint> > RenderBufferList;
	typedef std::list<GLuint,core::memory::MemoryAllocator<GLuint> >::iterator RenderBufferListIterator;

	typedef std::vector<GLuint,core::memory::MemoryAllocator<GLuint> > DrawBufferVector;

	virtual void		setDimensions(unsigned width,unsigned height);

	virtual bool		bind();

	virtual void		unbind();

	virtual void		attachRenderBuffer(renderer::FramebufferAttachment::type attach_to,renderer::TextureInternalFormat::type internalFormat);

	virtual void		detachRenderBuffer(renderer::FramebufferAttachment::type detach_from);

	virtual void		attachTexture(renderer::FramebufferAttachment::type attach_to,const Texture* tex,unsigned level = 0);

	virtual void		attachTexture(renderer::FramebufferAttachment::type attach_to,const Texture* tex,unsigned side,unsigned level = 0);

	virtual void		drawBuffers(unsigned size,renderer::FramebufferAttachment::type * bufs);

	virtual void		readBuffer(renderer::FramebufferAttachment::type buf);

	virtual unsigned	maxColorAttachments() const;

	virtual unsigned	status() const;

private:
	GLuint				m_Framebuffer;

	unsigned			m_Bounded;

	unsigned			m_Width;
	unsigned			m_Height;

	RenderBufferList	m_RenderBuffers;

	DrawBufferVector	m_DrawBuffers;

	unsigned			m_ReadBuffer;

	GLint				m_MaxColorAttachments;

	GLint				m_OldViewport[4];
};
}
}
}
#endif /* OPENGL_GLSL_FRAMEBUFFER_H */
