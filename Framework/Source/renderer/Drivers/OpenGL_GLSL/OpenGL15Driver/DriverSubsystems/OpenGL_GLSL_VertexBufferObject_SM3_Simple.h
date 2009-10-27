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
namespace opengl_glsl_15
{
class	OpenGL_GLSL_VertexBufferObject : public VertexBufferObject
{
	friend class OpenGL_GLSL_Driver;
protected:
	OpenGL_GLSL_VertexBufferObject();
	virtual ~OpenGL_GLSL_VertexBufferObject();
public:
	virtual void		setTarget(renderer::VBOTarget::type target);

	virtual void		bind();

	virtual void		bind(renderer::VBOTarget::type target);

	virtual void		unbind();

	virtual void*		map(renderer::VBOAccess::type access);

	virtual void		unmap();

	virtual void		setData(renderer::VBOTarget::type target,renderer::VBOUsage::type usage,size_t size,void* p);

	virtual void		setData(renderer::VBOUsage::type usage,size_t size,void* p);

	virtual void		setSubData(renderer::VBOTarget::type target,size_t offs,size_t size,void *p);

	virtual void		setSubData(size_t offs,size_t size,void* p);

	virtual void		getSubData(renderer::VBOTarget::type target,size_t offs,size_t size,void *p);

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
