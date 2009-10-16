/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/OpenGL_GLSL_Driver_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/OpenGL_15_ConstantsTables.h"
#include <iostream>
#include <algorithm>
#include "math/vector3d.hpp"
#include "math/matrix4x4.hpp"
#include "math/quaternion.hpp"

#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_VertexBufferObject_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Framebuffer_SM3_Simple.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.h"
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
namespace opengl_glsl_15
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

	m_Futures =
			renderer::futures::MULTITEXTURE					|
			renderer::futures::CUBE_MAP 					|
			renderer::futures::COMPRESSED_TEXTURE			|
			renderer::futures::S3TC_TEXTURE					|
			renderer::futures::DEPTH_TEXTURE				|
			renderer::futures::GENERATE_MIPMAPS				|
			renderer::futures::ANISOTROPIC_FILTERING		|
			renderer::futures::FRAMEBUFFER					|
			renderer::futures::VERTEX_BUFFER				|
			renderer::futures::TEXTURE_BUFFER				|
			renderer::futures::R2VB							|
			renderer::futures::VERTEX_SHADER				|
			renderer::futures::FRAGMENT_SHADER				|
			renderer::futures::AUTO_TRANSPOSE_MATIRIX;
	m_VF = NULL;
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
	return EString("OpenGL 1.5 GLSL");
		}

EString		OpenGL_GLSL_Driver::getAPIName() const
		{
	return EString("OpenGL 1.5");
		}

EString		OpenGL_GLSL_Driver::getShaderAPIName() const
		{
	return EString("GLSL_1_10");
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

void		OpenGL_GLSL_Driver::setStreamSource(unsigned sourceID,VertexBufferObject* dataSource,unsigned offset,unsigned stride)
{
	StreamSource*	stream = m_Streams + sourceID;
	stream->buffer = dataSource;
	stream->offset = offset;
	stream->stride = stride;
}

OpenGL_GLSL_Driver::VertexFormat::VertexFormat(renderer::VertexElement* format,StreamSource*	streams)
: EngineSubsystem()
  {
	m_Format = format;
	m_Streams = streams;
	bool end = false;
	m_Length = m_Size = 0;
	while(!end)
	{
		VertexElement* fmt = format + m_Length;
		if(fmt->usage != renderer::VertexFormat::UNUSED)
		{
			static unsigned char num_components[8] =
			{
					1,2,3,4,1,4,2,4
			};
			static unsigned char size_of_component[8] =
			{
					4,4,4,4,4,1,2,2
			};
			m_Size += num_components[fmt->type]*size_of_component[fmt->type];
			m_Length++;
		}
		else end = true;
	}

  }

void	OpenGL_GLSL_Driver::VertexFormat::enable()
{
	static unsigned char num_components[8] =
	{
			1,2,3,4,4,4,2,4
	};
	static unsigned  type_of_component[8] =
	{
			GL_FLOAT,GL_FLOAT,GL_FLOAT,GL_FLOAT,GL_UNSIGNED_BYTE,GL_UNSIGNED_BYTE,GL_SHORT,GL_SHORT
	};

	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

	int lastStream = m_Format[0].streamID;
	m_Streams[lastStream].buffer->bind();
	for(unsigned i = 0; i < m_Length; i ++)
	{
		VertexElement*	elem = m_Format + i;
		if(lastStream != elem->streamID)
		{
			m_Streams[lastStream].buffer->unbind();
			lastStream = elem->streamID;
			m_Streams[lastStream].buffer->bind();
		}
		switch(elem->usage)
		{
		case renderer::VertexFormat::POSITION:
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(num_components[elem->type],type_of_component[elem->type],m_Streams[lastStream].stride,(void*)(m_Streams[lastStream].offset + elem->offset));
			break;
		case renderer::VertexFormat::COLOR:
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(num_components[elem->type],type_of_component[elem->type],m_Streams[lastStream].stride,(void*)(m_Streams[lastStream].offset + elem->offset));
			break;
		case renderer::VertexFormat::NORMAL:
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(type_of_component[elem->type],m_Streams[lastStream].stride,(void*)(m_Streams[lastStream].offset + elem->offset));
			break;
		default:
			if(elem->usage < renderer::VertexFormat::UNUSED)
			{
				glClientActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[elem->usage - renderer::VertexFormat::TEXT_COORD]);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(num_components[elem->type],type_of_component[elem->type],m_Streams[lastStream].stride,(void*)(m_Streams[lastStream].offset + elem->offset));
			}
			break;
		}
	}
	m_Streams[lastStream].buffer->unbind();
}

void	OpenGL_GLSL_Driver::VertexFormat::enableImmediate(unsigned inst, void* data)
{
	static unsigned char num_components[8] =
	{
			1,2,3,4,4,4,2,4
	};
	static unsigned  type_of_component[8] =
	{
			GL_FLOAT,GL_FLOAT,GL_FLOAT,GL_FLOAT,GL_UNSIGNED_BYTE,GL_UNSIGNED_BYTE,GL_SHORT,GL_SHORT
	};

	for(unsigned i = 0; i < m_Length; i ++)
	{
		VertexElement*	elem = m_Format + i;
		switch(elem->usage)
		{
		case renderer::VertexFormat::COLOR:
			switch(type_of_component[elem->type])
			{
			case GL_FLOAT:
				switch(num_components[elem->type])
				{
				case 3:
					glColor3fv((GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
					break;
				case 4:
					glColor4fv((GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
					break;
				}
				break;
				case GL_UNSIGNED_BYTE:
					switch(num_components[elem->type])
					{
					case 3:
						glColor3ubv((GLubyte*)((char*)data)[elem->offset + inst*m_Size]);
						break;
					case 4:
						glColor4ubv((GLubyte*)((char*)data)[elem->offset + inst*m_Size]);
						break;
					}
					break;

					case GL_SHORT:
						switch(num_components[elem->type])
						{
						case 3:
							glColor3sv((GLshort*)((char*)data)[elem->offset + inst*m_Size]);
							break;
						case 4:
							glColor4sv((GLshort*)((char*)data)[elem->offset + inst*m_Size]);
							break;
						}
						break;
			}
			break;
			default:
				if(elem->usage < renderer::VertexFormat::UNUSED)
				{

					switch(type_of_component[elem->type])
					{
					case GL_FLOAT:
						switch(num_components[elem->type])
						{
						case 1:
							glMultiTexCoord1fv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
							break;

						case 2:
							glMultiTexCoord2fv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
							break;

						case 3:
							glMultiTexCoord3fv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
							break;
						case 4:
							glMultiTexCoord4fv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLfloat*)((char*)data)[elem->offset + inst*m_Size]);
							break;
						}
						break;

						case GL_SHORT:
							switch(num_components[elem->type])
							{
							case 1:
								glMultiTexCoord1sv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLshort*)((char*)data)[elem->offset + inst*m_Size]);
								break;

							case 2:
								glMultiTexCoord2sv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLshort*)((char*)data)[elem->offset + inst*m_Size]);
								break;

							case 3:
								glMultiTexCoord3sv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLshort*)((char*)data)[elem->offset + inst*m_Size]);
								break;
							case 4:
								glMultiTexCoord4sv(GL_TEXTURE0 + elem->type - renderer::VertexFormat::TEXT_COORD,(GLshort*)((char*)data)[elem->offset + inst*m_Size]);
								break;
							}
							break;
					}
				}
				break;
		}
	}
}

void OpenGL_GLSL_Driver::VertexFormat::disable()
{
	glPopClientAttrib();
}

void		OpenGL_GLSL_Driver::setVertexFormat(VertexElement*    element)
{
	delete m_VF;
	m_VF = new OpenGL_GLSL_Driver::VertexFormat(element,m_Streams);
}

void		OpenGL_GLSL_Driver::beginScene()
{
	//Do nothing in OpenGL driver
}
void		OpenGL_GLSL_Driver::endScene()
{
	//Do nothing in OpenGL driver
}

void		OpenGL_GLSL_Driver::drawPrimitive(unsigned primitives,unsigned first,unsigned count)
{
	m_VF->enable();
	glDrawArrays(OpenGL_GLSL_Tables::Primitive[primitives],first,count);
	m_VF->disable();
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf)
{
	m_VF->enable();
	buf->bind(VBOType::INDEX);
	glDrawElements(OpenGL_GLSL_Tables::Primitive[primitives],count,OpenGL_GLSL_Tables::DataType[type],0);
	buf->unbind();
	m_VF->disable();
}

void		OpenGL_GLSL_Driver::drawPrimitive(unsigned primitives,unsigned first,unsigned count,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData)
{
	OpenGL_GLSL_Driver::VertexFormat*	instd = new OpenGL_GLSL_Driver::VertexFormat(instanceDeclaration,m_Streams);
	m_VF->enable();
	for(int i = 0; i < numInstances; i++)
	{
		instd->enableImmediate(i,instanceData);
		glDrawArrays(OpenGL_GLSL_Tables::Primitive[primitives],first,count);
	}
	m_VF->disable();
	delete instd;
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* indexBuffer,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData)
{
	OpenGL_GLSL_Driver::VertexFormat*	instd = new OpenGL_GLSL_Driver::VertexFormat(instanceDeclaration,m_Streams);
	m_VF->enable();
	indexBuffer->bind(VBOType::INDEX);
	for(int i = 0; i < numInstances; i++)
	{
		instd->enableImmediate(i,instanceData);
		glDrawElements(OpenGL_GLSL_Tables::Primitive[primitives],count,OpenGL_GLSL_Tables::DataType[type],0);
	}
	indexBuffer->unbind();
	m_VF->disable();
	delete instd;
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
