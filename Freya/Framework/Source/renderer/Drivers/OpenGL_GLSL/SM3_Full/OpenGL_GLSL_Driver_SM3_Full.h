/*This header was generated from RenderingAPIDriver.h for Freya engine */
#ifndef OPENGL_GLSL_DRIVER3_H
#define OPENGL_GLSL_DRIVER3_H

#include "renderer/RenderingAPIDriver.h"
#include "core/memory/MemoryAllocator.h"

extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}

#include <list>

namespace renderer
{
namespace drivers
{
namespace ids
{
class OpenGL_GLSL_SM3_FULL;
}

namespace opengl_glsl_sm3_full
{
class OpenGL_GLSL_Texture;
class OpenGL_GLSL_VertexBufferObject;
class OpenGL_GLSL_Framebuffer;
class OpenGL_GLSL_Shader;

class	OpenGL_GLSL_Driver : public RenderingAPIDriver
{
	friend class renderer::drivers::ids::OpenGL_GLSL_SM3_FULL;
protected:
	OpenGL_GLSL_Driver();
	virtual ~OpenGL_GLSL_Driver();
public:
	typedef std::list<OpenGL_GLSL_Texture*,core::memory::MemoryAllocator<OpenGL_GLSL_Texture*> > TextureList;
	typedef std::list<OpenGL_GLSL_VertexBufferObject*,core::memory::MemoryAllocator<OpenGL_GLSL_VertexBufferObject*> > VertexBufferObjectList;
	typedef std::list<OpenGL_GLSL_Framebuffer*,core::memory::MemoryAllocator<OpenGL_GLSL_Framebuffer*> > FramebufferList;
	typedef std::list<OpenGL_GLSL_Shader*,core::memory::MemoryAllocator<OpenGL_GLSL_Shader*> > ShaderList;

	typedef std::list<OpenGL_GLSL_Texture*,core::memory::MemoryAllocator<OpenGL_GLSL_Texture*> >::iterator TextureListIterator;
	typedef std::list<OpenGL_GLSL_VertexBufferObject*,core::memory::MemoryAllocator<OpenGL_GLSL_VertexBufferObject*> >::iterator VertexBufferObjectListIterator;
	typedef std::list<OpenGL_GLSL_Framebuffer*,core::memory::MemoryAllocator<OpenGL_GLSL_Framebuffer*> >::iterator FramebufferListIterator;
	typedef std::list<OpenGL_GLSL_Shader*,core::memory::MemoryAllocator<OpenGL_GLSL_Shader*> >::iterator ShaderListIterator;

	virtual EString		id() const;

	virtual EString		getAPIName() const;

	virtual EString		getShaderAPIName() const;

	virtual bool	futuresState(unsigned futures) const;

	virtual unsigned futures() const;

	virtual void		setViewport(unsigned width,unsigned height);

	virtual void		clearColorValue(float r,float g,float b,float a);

	virtual void		clearColor();

	virtual void		setPerspective(float FieldOfView,float Aspect,float Near,float Far);

	virtual void		setOrtho(unsigned width,unsigned height,float near = -1.0f,float far = 1.0f);

	virtual void		enableDepthTest();

	virtual void		disableDepthTest();

	virtual void		clearDepthValue(float val);

	virtual void		clearDepth();

	virtual void		depthFunction(unsigned func);

	virtual void		enableStencilTest();

	virtual void		disableStencilTest();

	virtual void		clearStencilValue(int val);

	virtual void		clearStencil();

	virtual void		stencilFunction(unsigned func, int ref, unsigned mask);

	virtual void		stencilOp(unsigned fail,unsigned zfail,unsigned zpass);

	virtual void		enableAlphaTest();

	virtual void		disableAlphaTest();

	virtual void		alphaTestFunction(unsigned func, float ref);

	virtual void		enableAlphaBlend();

	virtual void		disableAlphaBlend();

	virtual void		alphaBlendFunction(unsigned sfactor,unsigned dfactor);

	virtual void		loadMatrix(const math::matrix4x4& mtx);

	virtual void 		loadIdentityMatrix();

	virtual void		multMatrix(const math::matrix4x4& mtx);

	virtual void		pushMatrix();

	virtual void		popMatrix();

	virtual void		setMatrixMode(unsigned mode);

	virtual void		translate(float x,float y,float z);

	virtual void		translate(const math::vector3d& vec);

	virtual void		rotate(float angle,float x,float y,float z);

	virtual void		rotate(float angle,const math::vector3d& vec);

	virtual void		rotate(const math::quaternion& quat);

	virtual void		scale(float x,float y,float z);

	virtual Texture*	createTexture();

	virtual void		destroyTexture(Texture* texture);

	virtual void		enableGeneration(unsigned coord,unsigned mode);

	virtual void		disableGeneration(unsigned coord);

	virtual void		setEyePlane(unsigned coord,const math::vector3d& n);

	virtual void		setObjectPlane(unsigned coord,const math::vector3d& n);

	virtual VertexBufferObject*		createVertexBufferObject();

	virtual void					destroyVertexBufferObject(VertexBufferObject*	buf);

	virtual void		drawPrimitive(unsigned primitives,unsigned first,unsigned count);

	virtual void		drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf);

	virtual void		drawPrimitive(unsigned primitives,unsigned first,unsigned count,const InstanceArray& instances);

	virtual void		drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf,const InstanceArray& instances);


	virtual void		enableClientState(unsigned state);

	virtual void		disableClientState(unsigned state);

	virtual void		enableTextureCoordState(unsigned unit);

	virtual void		disableTextureCoordState(unsigned unit);

	virtual void		colorPointer(unsigned dataType,unsigned numComponents,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		colorIndexPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		normalPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		textureCoordPointer(unsigned unit,unsigned dataType,unsigned numComponenets,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		vertexPointer(unsigned dataType,unsigned numComponenets,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		fogCoordPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0);

	virtual void		setRenderMode(unsigned side,unsigned mode);

	virtual void		enableFog();

	virtual void		disableFog();

	virtual void		setFogFunction(unsigned func);

	virtual void		setLinearFogBoundaries(float start,float end);

	virtual void		setFogDensity(float density);

	virtual void		setFogColor(float r,float g,float,float b);

	virtual Framebuffer*		createFramebuffer();

	virtual void				destroyFramebuffer(Framebuffer* buf);

	virtual Shader*				createShader();

	virtual void		destroyShader(Shader* shad);

	virtual void			setColorWrite(bool r,bool g,bool b,bool a);

	virtual void			setDepthWrite(bool d);

	virtual void enableCulling();

	virtual void disableCulling();

	virtual void setFrontFace(unsigned FrontFace);//As described by FrontFace namespace

	virtual void setCullFace(unsigned Face); //As described by RenderSide namespace

	virtual void enablePolygonOffset();

	virtual void disablePolygonOffset();

	virtual void setPolygonOffset(float factor,float units);
private:
	//Geometry shader support
	unsigned				m_Futures;
	//Objects management
	TextureList				m_TextureList;
	VertexBufferObjectList	m_VertexBufferObjectList;
	FramebufferList			m_FramebufferList;
	ShaderList				m_ShaderList;

};
}
}
}
#endif /* OPENGL_GLSL_DRIVER_H */
