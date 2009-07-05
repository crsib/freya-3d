/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoDS/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_NoDS.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL_GLSL_ConstantsTables.h"

namespace renderer
{
namespace drivers
{
namespace opengl_glsl_sm3_nods
{

OpenGL_GLSL_VertexBufferObject::OpenGL_GLSL_VertexBufferObject()
{
	glGenBuffersARB(1,&m_Buffer);
	m_IsBounded = m_IsMapped = false;
	m_DefaultInternal = 0;
	m_DefaultTarget = OpenGL_GLSL_Tables::VBOType[0];
}

OpenGL_GLSL_VertexBufferObject::~OpenGL_GLSL_VertexBufferObject()
{
	glDeleteBuffersARB(1,&m_Buffer);
}

void		OpenGL_GLSL_VertexBufferObject::setTarget(unsigned target)
{
	m_DefaultTarget = OpenGL_GLSL_Tables::VBOType[target];
	m_DefaultInternal = target;
}

void		OpenGL_GLSL_VertexBufferObject::bind()
{
	glBindBufferARB(m_DefaultTarget,m_Buffer);
	m_BoundedTarget = m_DefaultTarget;
	m_BoundedInternal = m_DefaultInternal;
	m_IsBounded	=	true;
}

void		OpenGL_GLSL_VertexBufferObject::bind(unsigned target)
{
	m_BoundedTarget = OpenGL_GLSL_Tables::VBOType[target];
	m_BoundedInternal = target;
	glBindBufferARB(m_BoundedTarget,m_Buffer);
	m_IsBounded = true;
}

void		OpenGL_GLSL_VertexBufferObject::	unbind()
{
	if(m_IsBounded)
	{
		m_IsBounded = false;
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glBindBufferARB(m_BoundedTarget,0);
	}
}

void*		OpenGL_GLSL_VertexBufferObject::map(unsigned access)
{
	GLint active;
	void* addr;
	if(m_IsBounded)
	{
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			addr = glMapBufferARB(m_BoundedTarget,OpenGL_GLSL_Tables::VBOAccess[access]);
		else //What the hell?
		{
			glBindBuffer(m_BoundedTarget,m_Buffer);
			addr = glMapBufferARB(m_BoundedTarget,OpenGL_GLSL_Tables::VBOAccess[access]);
			glBindBuffer(m_BoundedTarget,active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind();
		addr = glMapBufferARB(m_BoundedTarget,OpenGL_GLSL_Tables::VBOAccess[access]);
		unbind();
	}
	if(addr)
		m_IsMapped = true;
	return addr;
}

void		OpenGL_GLSL_VertexBufferObject::   unmap()
{
	GLint active;
	bool addr;
	if(m_IsBounded)
	{
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			addr = glUnmapBufferARB(m_BoundedTarget);
		else //What the hell?
		{
			glBindBuffer(m_BoundedTarget,m_Buffer);
			addr = glUnmapBufferARB(m_BoundedTarget);
			glBindBuffer(m_BoundedTarget,active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind();
		addr = glUnmapBufferARB(m_BoundedTarget);
		unbind();
	}
	m_IsMapped = false;
	if(!addr) throw 0;
}

void		OpenGL_GLSL_VertexBufferObject::setData(unsigned target,unsigned usage,size_t size,void* p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[target],&active);
		if(static_cast<unsigned>(active)  == m_Buffer)
			glBufferDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
		else //What the hell?
		{
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],m_Buffer);
			glBufferDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind(target);
		glBufferDataARB(m_BoundedTarget,size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
		unbind();
	}
}

void		OpenGL_GLSL_VertexBufferObject::setData(unsigned usage,size_t size,void* p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glBufferDataARB(m_BoundedTarget,size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
		else //What the hell?
		{
			glBindBuffer(m_BoundedTarget,m_Buffer);
			glBufferDataARB(m_BoundedTarget,size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
			glBindBuffer(m_BoundedTarget,active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind();
		glBufferDataARB(m_BoundedTarget,size,p,OpenGL_GLSL_Tables::VBOUsage[usage]);
		unbind();
	}
}

void		OpenGL_GLSL_VertexBufferObject::setSubData(unsigned target,size_t offs,size_t size,void *p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[target],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glBufferSubDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],offs,size,p);
		else //What the hell?
		{
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],m_Buffer);
			glBufferSubDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],offs,size,p);
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind(target);
		glBufferSubDataARB(m_BoundedTarget,offs,size,p);
		unbind();
	}
}

void		OpenGL_GLSL_VertexBufferObject::setSubData(size_t offs,size_t size,void* p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glBufferSubDataARB(m_BoundedTarget,offs,size,p);
		else //What the hell?
		{
			glBindBuffer(m_BoundedTarget,m_Buffer);
			glBufferSubDataARB(m_BoundedTarget,offs,size,p);
			glBindBuffer(m_BoundedTarget,active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind();
		glBufferSubDataARB(m_BoundedTarget,offs,size,p);
		unbind();
	}
}

void		OpenGL_GLSL_VertexBufferObject::getSubData(unsigned target,size_t offs,size_t size,void *p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[target],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glGetBufferSubDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],offs,size,p);
		else //What the hell?
		{
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],m_Buffer);
			glGetBufferSubDataARB(OpenGL_GLSL_Tables::GetVBOBinding[target],offs,size,p);
			glBindBuffer(OpenGL_GLSL_Tables::GetVBOBinding[target],active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind(target);
		glGetBufferSubDataARB(m_BoundedTarget,offs,size,p);
		unbind();
	}
}

void		OpenGL_GLSL_VertexBufferObject::getSubData(size_t offs,size_t size,void* p)
{
	if(m_IsBounded)
	{
		GLint active;
		glGetIntegerv(OpenGL_GLSL_Tables::GetVBOBinding[m_BoundedInternal],&active);
		if(static_cast<unsigned>(active) == m_Buffer)
			glGetBufferSubDataARB(m_BoundedTarget,offs,size,p);
		else //What the hell?
		{
			glBindBuffer(m_BoundedTarget,m_Buffer);
			glGetBufferSubDataARB(m_BoundedTarget,offs,size,p);
			glBindBuffer(m_BoundedTarget,active);
			m_IsBounded = false;
		}
	}
	else
	{
		bind();
		glGetBufferSubDataARB(m_BoundedTarget,offs,size,p);
		unbind();
	}
}


}
}
}
