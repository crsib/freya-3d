/*This header was generated from VertexBufferObject.h for Freya engine */
#ifndef OPENGL_GLSL_VERTEX_BUFFER_OBJECT_H
#define OPENGL_GLSL_VERTEX_BUFFER_OBJECT_H

#include "renderer/DriverSubsystems/VertexBufferObject.h"

extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}



namespace renderer
{
namespace drivers
{
namespace opengl_glsl_sm3_nomrt
{
class	OpenGL_GLSL_VertexBufferObject : public VertexBufferObject
{
	friend class OpenGL_GLSL_Driver;
protected:
	OpenGL_GLSL_VertexBufferObject();
	virtual ~OpenGL_GLSL_VertexBufferObject();
public:
	virtual void		setTarget(unsigned target);

	virtual void		bind();

	virtual void		bind(unsigned target);

	virtual void		unbind();

	virtual void*		map(unsigned access);

	virtual void		unmap();

	virtual void		setData(unsigned target,unsigned usage,size_t size,void* p);

	virtual void		setData(unsigned usage,size_t size,void* p);

	virtual void		setSubData(unsigned target,size_t offs,size_t size,void *p);

	virtual void		setSubData(size_t offs,size_t size,void* p);

	virtual void		getSubData(unsigned target,size_t offs,size_t size,void *p);

	virtual void		getSubData(size_t offs,size_t size,void* p);

private:
	unsigned			m_DefaultTarget;	//In OpenGL format
	unsigned			m_BoundedTarget;    //In OpenGL format
	unsigned			m_DefaultInternal; //Same, but in engine internal format
	unsigned			m_BoundedInternal;

	unsigned			m_IsBounded;
	unsigned			m_IsMapped;

	GLuint				m_Buffer;

};
}
}
}
#endif /* OPENGL_GLSL_VERTEX_BUFFER_OBJECT_H */
