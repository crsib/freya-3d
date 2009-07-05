/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/OpenGL_GLSL_Driver_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL_GLSL_ConstantsTables.h"
#include <iostream>
#include <algorithm>
#include "math/vector3d.hpp"
#include "math/matrix4x4.hpp"
#include "math/quaternion.hpp"

#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.h"
#include "renderer/DriverException.h"

#define	assert_extension(name)	if(!GLEW_##name)\
	{\
	clog << "Extension " #name " is unsupported!. Please, update your driver." << endl;\
	throw renderer::DriverException("Hardware does not support " #name " feature");\
	}

using std::clog;
using std::endl;
namespace renderer
{
namespace drivers
{
namespace opengl_glsl_sm3_simple
{
OpenGL_GLSL_Driver::OpenGL_GLSL_Driver()
{
	clog << "Starting OpenGL rendering driver. Shaders are going to be compiled through GLSL" << endl;
	unsigned err = glewInit();
	if(err != GLEW_OK)
	{
		clog << "Failed to start driver. GLEW failed to initialize: " << glewGetErrorString(err) << endl;
		throw  renderer::DriverException("[renderer]: Window system is unsupported");
	}
	//Ok, now, test extensions needed
	if(!GLEW_VERSION_1_3)
	{
		assert_extension(ARB_transpose_matrix);
		assert_extension(ARB_multitexture); //+
		assert_extension(EXT_texture_filter_anisotropic);//+
	}
	assert_extension(ARB_texture_cube_map); //+
	assert_extension(ARB_texture_compression);//+
	assert_extension(ARB_depth_texture);//+
	assert_extension(ARB_vertex_buffer_object);//+
	assert_extension(ARB_shader_objects);//+
	assert_extension(ARB_vertex_shader);//+
	assert_extension(ARB_fragment_shader);//+
	assert_extension(ARB_shading_language_100);
	assert_extension(ARB_pixel_buffer_object);//+

	assert_extension(EXT_texture_compression_s3tc);//+
	assert_extension(EXT_framebuffer_object);//+
	assert_extension(EXT_fog_coord);

	m_Futures = futures::MULTITEXTURE	|
	futures::CUBE_MAP 					|
	futures::COMPRESSED_TEXTURE			|
	futures::S3TC_TEXTURE				|
	futures::DEPTH_TEXTURE				|
	futures::GENERATE_MIPMAPS			|
	futures::ANISOTROPIC_FILTERING		|

	futures::FRAMEBUFFER				|

	futures::VERTEX_BUFFER				|
	futures::TEXTURE_BUFFER				|
	futures::R2VB						|

	futures::VERTEX_SHADER				|
	futures::FRAGMENT_SHADER			|


	futures::FOG_COORD					|
	futures::AUTO_TRANSPOSE_MATIRIX;
}

OpenGL_GLSL_Driver::~OpenGL_GLSL_Driver()
{
	for(TextureListIterator it = m_TextureList.begin();it != m_TextureList.end();it++)
		delete *it;
	for(VertexBufferObjectListIterator it = m_VertexBufferObjectList.begin(); it != m_VertexBufferObjectList.end();it++)
		delete *it;
	for(FramebufferListIterator it = m_FramebufferList.begin();it != m_FramebufferList.end();it++)
		delete *it;
	for(ShaderListIterator it = m_ShaderList.begin(); it != m_ShaderList.end();it++)
		delete *it;
}

EString		OpenGL_GLSL_Driver::id() const
{
	return EString("OpenGL GLSL SM3");
}

EString		OpenGL_GLSL_Driver::getAPIName() const
{
	return EString("OpenGL");
}

EString		OpenGL_GLSL_Driver::getShaderAPIName() const
{
	return EString("GLSL");
}

bool	OpenGL_GLSL_Driver::futuresState(unsigned futures) const
{
	return (m_Futures & futures) == futures;
}

unsigned OpenGL_GLSL_Driver::futures() const
{
	return m_Futures;
}

void		OpenGL_GLSL_Driver::setViewport(unsigned width,unsigned height)
{
	glViewport(0,0,width,height);
}

void		OpenGL_GLSL_Driver::clearColorValue(float r,float g,float b,float a)
{
	glClearColor(r,g,b,a);
}

void		OpenGL_GLSL_Driver::clearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void		OpenGL_GLSL_Driver::setPerspective(float FieldOfView,float Aspect,float Near,float Far)
{
	gluPerspective(FieldOfView*180.0f/math::pi,Aspect,Near,Far);
}

void		OpenGL_GLSL_Driver::setOrtho(unsigned width,unsigned height,float near,float far)
{
	glOrtho(0,width,0,height,near,far);
}

void		OpenGL_GLSL_Driver::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void		OpenGL_GLSL_Driver::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void		OpenGL_GLSL_Driver::clearDepthValue(float val)
{
	glClearDepth(val);
}

void		OpenGL_GLSL_Driver::clearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void		OpenGL_GLSL_Driver::depthFunction(unsigned func)
{
	glDepthFunc(OpenGL_GLSL_Tables::TestFunction[func]);
}

void		OpenGL_GLSL_Driver::enableStencilTest()
{
	glEnable(GL_STENCIL_TEST);
}

void		OpenGL_GLSL_Driver::disableStencilTest()
{
	glDisable(GL_STENCIL_TEST);
}

void		OpenGL_GLSL_Driver::clearStencilValue(int val)
{
	glClearStencil(val);
}

void		OpenGL_GLSL_Driver::clearStencil()
{
	glClear(GL_STENCIL_BUFFER_BIT);
}

void		OpenGL_GLSL_Driver::stencilFunction(unsigned func, int ref, unsigned mask)
{
	glStencilFunc(OpenGL_GLSL_Tables::TestFunction[func],ref,mask);
}

void		OpenGL_GLSL_Driver::stencilOp(unsigned fail,unsigned zfail,unsigned zpass)
{
	glStencilOp(OpenGL_GLSL_Tables::StencilOp[fail],OpenGL_GLSL_Tables::StencilOp[zfail],OpenGL_GLSL_Tables::StencilOp[zpass]);
}

void		OpenGL_GLSL_Driver::enableAlphaTest()
{
	glEnable(GL_ALPHA_TEST);
}

void		OpenGL_GLSL_Driver::disableAlphaTest()
{
	glDisable(GL_ALPHA_TEST);
}

void		OpenGL_GLSL_Driver::alphaTestFunction(unsigned func, float ref)
{
	glAlphaFunc(OpenGL_GLSL_Tables::TestFunction[func],ref);
}

void		OpenGL_GLSL_Driver::enableAlphaBlend()
{
	glEnable(GL_BLEND);
}

void		OpenGL_GLSL_Driver::disableAlphaBlend()
{
	glDisable(GL_BLEND);
}

void		OpenGL_GLSL_Driver::alphaBlendFunction(unsigned sfactor,unsigned dfactor)
{
	glBlendFunc(OpenGL_GLSL_Tables::AlphaFunction[sfactor],OpenGL_GLSL_Tables::AlphaFunction[dfactor]);
}

void		OpenGL_GLSL_Driver::loadMatrix(const math::matrix4x4& mtx)
{
	glLoadTransposeMatrixfARB(/*const_cast<GLfloat*>*/(mtx.mat_linear));
}

void		OpenGL_GLSL_Driver::loadIdentityMatrix()
{
	glLoadIdentity();
}

void		OpenGL_GLSL_Driver::multMatrix(const math::matrix4x4& mtx)
{
	glMultTransposeMatrixfARB(const_cast<GLfloat*>(mtx.mat_linear));
}

void		OpenGL_GLSL_Driver::pushMatrix()
{
	glPushMatrix();
}

void		OpenGL_GLSL_Driver::popMatrix()
{
	glPopMatrix();
}

void		OpenGL_GLSL_Driver::setMatrixMode(unsigned mode)
{
	if(mode < renderer::MatrixMode::TEXTURE0)
	{
		glMatrixMode(OpenGL_GLSL_Tables::MatrixMode[mode]);
	}
	else
	{
		glActiveTextureARB(OpenGL_GLSL_Tables::MatrixMode[mode]);
		glMatrixMode(GL_TEXTURE);
	}
}

void		OpenGL_GLSL_Driver::translate(float x,float y,float z)
{
	glTranslatef(x,y,z);
}

void		OpenGL_GLSL_Driver::translate(const math::vector3d& vec)
{
	glTranslatef(vec.x,vec.y,vec.z);
}

void		OpenGL_GLSL_Driver::rotate(float angle,float x,float y,float z)
{
	glRotatef(angle*180.0f/math::pi,x,y,z);
}

void		OpenGL_GLSL_Driver::rotate(float angle,const math::vector3d& vec)
{
	glRotatef(angle*180.0f/math::pi,vec.x,vec.y,vec.z);
}

void		OpenGL_GLSL_Driver::rotate(const math::quaternion& quat)
{
	math::matrix4x4 mat;
	mat = quat;
	glMultTransposeMatrixfARB(mat.mat_linear);
}

void		OpenGL_GLSL_Driver::scale(float x,float y,float z)
{
	glScalef(x,y,z);
}

Texture*		OpenGL_GLSL_Driver::createTexture()
{
	OpenGL_GLSL_Texture* o = new OpenGL_GLSL_Texture();
	m_TextureList.push_back(o);
	return o;
}

void		OpenGL_GLSL_Driver::	destroyTexture(Texture* texture)
{
	TextureListIterator it = std::find(m_TextureList.begin(),m_TextureList.end(),texture);
	if(m_TextureList.end() == it) return; //No texture
	delete *it;
	m_TextureList.erase(it);
}

void		OpenGL_GLSL_Driver::		enableGeneration(unsigned coord,unsigned mode)
{
	glEnable(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord]);
	glTexGeni(OpenGL_GLSL_Tables::TextureCoord[coord],GL_TEXTURE_GEN_MODE,OpenGL_GLSL_Tables::TextureGenMode[mode]);
}

void		OpenGL_GLSL_Driver::	disableGeneration(unsigned coord)
{
	glDisable(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord]);
}

void		OpenGL_GLSL_Driver::	setEyePlane(unsigned coord,const math::vector3d& n)
{
	glTexGenfv(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord],GL_EYE_PLANE,const_cast<math::vector3d&>(n));
}

void		OpenGL_GLSL_Driver::	setObjectPlane(unsigned coord,const math::vector3d& n)
{
	glTexGenfv(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord],GL_OBJECT_PLANE,const_cast<math::vector3d&>(n));
}

VertexBufferObject*		OpenGL_GLSL_Driver::createVertexBufferObject()
{
	OpenGL_GLSL_VertexBufferObject* obj = new OpenGL_GLSL_VertexBufferObject();
	m_VertexBufferObjectList.push_back(obj);
	return obj;
}

void					OpenGL_GLSL_Driver::destroyVertexBufferObject(VertexBufferObject*	buf)
{
	VertexBufferObjectListIterator it = std::find(m_VertexBufferObjectList.begin(),m_VertexBufferObjectList.end(),buf);
	if(m_VertexBufferObjectList.end() == it) return; //VBO
	delete *it;
	m_VertexBufferObjectList.erase(it);
}

void		OpenGL_GLSL_Driver::drawPrimitive(unsigned primitives,unsigned first,unsigned count)
{
	glDrawArrays(OpenGL_GLSL_Tables::Primitive[primitives],first,count);
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf)
{
	buf->bind(VBOType::INDEX);
	glDrawElements(OpenGL_GLSL_Tables::Primitive[primitives],count,OpenGL_GLSL_Tables::DataType[type],0);
	buf->unbind();
}

void		OpenGL_GLSL_Driver::drawPrimitive(unsigned primitives,unsigned first,unsigned count,const InstanceArray& instances)
{
	unsigned prim = OpenGL_GLSL_Tables::Primitive[primitives];
	for(unsigned i = 0; i < instances.size(); i++)
	{
		glColor4f(instances[i].Color[0],instances[i].Color[1],instances[i].Color[2],instances[i].Alpha);
		GLint	current;
		glGetIntegerv(GL_MATRIX_MODE,&current);
		GLint   currentM;
		glGetIntegerv(GL_ACTIVE_TEXTURE,&currentM);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glMatrixMode(GL_TEXTURE);
		glLoadTransposeMatrixfARB(static_cast<float*>(const_cast<math::matrix4x4&>(instances[i].ModelMatrix)));
		glMatrixMode(current);
		glActiveTextureARB(currentM);
		glDrawArrays(prim,first,count);
	}
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf,const InstanceArray& instances)
{
	unsigned prim = OpenGL_GLSL_Tables::Primitive[primitives];
	for(unsigned i = 0; i < instances.size(); i++)
	{
		glColor4f(instances[i].Color[0],instances[i].Color[1],instances[i].Color[2],instances[i].Alpha);
		GLint	current;
		glGetIntegerv(GL_MATRIX_MODE,&current);
		//glActiveTextureARB
		GLint   currentM;
		glGetIntegerv(GL_ACTIVE_TEXTURE,&currentM);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glMatrixMode(GL_TEXTURE);

		glLoadTransposeMatrixfARB(static_cast<float*>(const_cast<math::matrix4x4&>(instances[i].ModelMatrix)));
		glMatrixMode(current);
		glActiveTextureARB(currentM);
		buf->bind(VBOType::INDEX);
		glDrawElements(prim,count,OpenGL_GLSL_Tables::DataType[type],0);
		buf->unbind();
	}
}

void		OpenGL_GLSL_Driver::enableClientState(unsigned state)
{
	glEnableClientState(OpenGL_GLSL_Tables::ClientState[state]);
}

void		OpenGL_GLSL_Driver::disableClientState(unsigned state)
{
	glDisableClientState(OpenGL_GLSL_Tables::ClientState[state]);
}

void		OpenGL_GLSL_Driver::enableTextureCoordState(unsigned unit)
{
	glClientActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[unit]);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void		OpenGL_GLSL_Driver::disableTextureCoordState(unsigned unit)
{
	glClientActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[unit]);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void		OpenGL_GLSL_Driver::colorPointer(unsigned dataType,unsigned numComponents,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	buf->bind(VBOType::VERTEX);
	glColorPointer(numComponents,OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
}

void		OpenGL_GLSL_Driver::	colorIndexPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	buf->bind(VBOType::VERTEX);
	glIndexPointer(OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
}

void		OpenGL_GLSL_Driver::normalPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	buf->bind(VBOType::VERTEX);
	glNormalPointer(OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
}

void		OpenGL_GLSL_Driver::textureCoordPointer(unsigned unit,unsigned dataType,unsigned numComponents,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	glClientActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[unit]);
	buf->bind(VBOType::VERTEX);
	glTexCoordPointer(numComponents,OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
	glClientActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[TextureUnit::TEXTURE0]);
}

void		OpenGL_GLSL_Driver::vertexPointer(unsigned dataType,unsigned numComponents,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	buf->bind(VBOType::VERTEX);
	glVertexPointer(numComponents,OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
}

void		OpenGL_GLSL_Driver::fogCoordPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset)
{
	buf->bind(VBOType::VERTEX);
	glFogCoordPointerEXT(OpenGL_GLSL_Tables::DataType[dataType],stride, reinterpret_cast<void*>(offset) );
	buf->unbind();
}

void		OpenGL_GLSL_Driver::enableFog()
{
	glEnable(GL_FOG);
}

void		OpenGL_GLSL_Driver::   disableFog()
{
	glDisable(GL_FOG);
}

void		OpenGL_GLSL_Driver::setFogFunction(unsigned func)
{
	glFogi(GL_FOG_MODE,OpenGL_GLSL_Tables::FogFunction[func]);
}

void		OpenGL_GLSL_Driver::setLinearFogBoundaries(float start,float end)
{
	glFogi(GL_FOG_START,start);
	glFogi(GL_FOG_END,end);
}

void		OpenGL_GLSL_Driver::setFogDensity(float density)
{
	glFogf(GL_FOG_DENSITY,density);
}

void		OpenGL_GLSL_Driver::setFogColor(float r,float g,float b,float a)
{
	float arr[] = {r,g,b,a};
	glFogfv(GL_FOG_COLOR,arr);
}

Framebuffer*		OpenGL_GLSL_Driver::createFramebuffer()
{
	OpenGL_GLSL_Framebuffer* frmb = new OpenGL_GLSL_Framebuffer();
	m_FramebufferList.push_back(frmb);
	return frmb;
}

void				OpenGL_GLSL_Driver::destroyFramebuffer(Framebuffer* buf)
{
	FramebufferListIterator it = std::find(m_FramebufferList.begin(),m_FramebufferList.end(),buf);
	if(m_FramebufferList.end() == it) return;
	delete *it;
	m_FramebufferList.erase(it);
}

Shader*		OpenGL_GLSL_Driver::createShader()
{
	OpenGL_GLSL_Shader* shdr = new OpenGL_GLSL_Shader();
	m_ShaderList.push_back(shdr);
	return shdr;
}

void		OpenGL_GLSL_Driver::destroyShader(Shader* shad)
{
	ShaderListIterator it = std::find(m_ShaderList.begin(),m_ShaderList.end(),shad);
	if(m_ShaderList.end() == it) return;
	delete *it;
	m_ShaderList.erase(it);
}


void		OpenGL_GLSL_Driver::setRenderMode(unsigned side,unsigned mode)
{
	glPolygonMode(OpenGL_GLSL_Tables::RenderSide[side],OpenGL_GLSL_Tables::RenderMode[mode]);
}


void		OpenGL_GLSL_Driver::setColorWrite(bool r,bool g,bool b,bool a)
{
	glColorMask(r,g,b,a);
}

void		OpenGL_GLSL_Driver::setDepthWrite(bool d)
{
	glDepthMask(d);
}

void		OpenGL_GLSL_Driver::enableCulling()
{
	glEnable(GL_CULL_FACE);
}

void		OpenGL_GLSL_Driver::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void		OpenGL_GLSL_Driver::setCullFace(unsigned face)
{
	glCullFace(OpenGL_GLSL_Tables::RenderSide[face]);
}

void		OpenGL_GLSL_Driver::setFrontFace(unsigned FrontFace)
{
	glFrontFace(OpenGL_GLSL_Tables::FrontFace[FrontFace]);
}

void		OpenGL_GLSL_Driver::enablePolygonOffset()
{
	glEnable(GL_POLYGON_OFFSET_POINT);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glEnable(GL_POLYGON_OFFSET_FILL);
}

void		OpenGL_GLSL_Driver::disablePolygonOffset()
{
	glDisable(GL_POLYGON_OFFSET_POINT);
	glDisable(GL_POLYGON_OFFSET_LINE);
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void		OpenGL_GLSL_Driver::setPolygonOffset(float factor,float units)
{
	glPolygonOffset(factor,units);
}

}
}
}
