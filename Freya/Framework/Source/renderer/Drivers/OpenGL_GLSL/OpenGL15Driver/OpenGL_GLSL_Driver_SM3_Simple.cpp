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
	std::clog << "Extension " #name " is unsupported!. Please, update your driver." << std::endl;\
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
			renderer::futures::HAS_DEFAULT_PROJECTION_BIND  |
			renderer::futures::HAS_DEFAULT_VIEW_BIND		|
			renderer::futures::HAS_DEFUALT_WORLD_BIND;
	m_VF = NULL;
	m_RendererName = EString(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	m_RendererVendor = EString(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,reinterpret_cast<GLint*>(&m_MaxTextureSize));
	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE,reinterpret_cast<GLint*>(&m_MaxCubeTextureSize));
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE,reinterpret_cast<GLint*>(&m_Max3DTextureSize));
	glGetIntegerv(GL_MAX_DRAW_BUFFERS,reinterpret_cast<GLint*>(&m_NumDrawBuffers));
	glGetIntegerv(GL_MAX_TEXTURE_UNITS,reinterpret_cast<GLint*>(&m_TextureUnits));

	std::clog << "Hardware capabilities: \n\tMaximum size of 2D texture: " << m_MaxTextureSize
			<< " px\n\tMaximum cube texture size: " << m_MaxCubeTextureSize
			<< " px\n\tMaximum 3D texture size: " << m_Max3DTextureSize
			<< " px\n\tNumber of draw buffers: " << m_NumDrawBuffers
			<< " \n\tNumber of texture units: " << m_TextureUnits << std::endl;
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

EString
OpenGL_GLSL_Driver::id() const
{
	return EString("OpenGL 1.5 GLSL");
}

EString
OpenGL_GLSL_Driver::getAPIName() const
{
	return EString("OpenGL 1.5");
}

EString
OpenGL_GLSL_Driver::getShaderAPIName() const
{
	return EString("GLSL_1_10");
}

bool
OpenGL_GLSL_Driver::futuresState(unsigned futures) const
{
	return (m_Futures & futures) == futures;
}

unsigned
OpenGL_GLSL_Driver::futures() const
{
	return m_Futures;
}

void		OpenGL_GLSL_Driver::setViewport(unsigned x, unsigned y,unsigned width,unsigned height)
{
	glViewport(x,y,width,height);
	m_ViewPort[0] = x;
	m_ViewPort[1] = y;
	m_ViewPort[2] = width;
	m_ViewPort[3] = height;
}

void		OpenGL_GLSL_Driver::clearColorValue(float r,float g,float b,float a)
{
	glClearColor(r,g,b,a);
}

void		OpenGL_GLSL_Driver::clearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
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

void		OpenGL_GLSL_Driver::depthFunction(renderer::TestFunction::type func)
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

void		OpenGL_GLSL_Driver::stencilFunction(renderer::TestFunction::type func, int ref, unsigned mask)
{
	glStencilFunc(OpenGL_GLSL_Tables::TestFunction[func],ref,mask);
}

void		OpenGL_GLSL_Driver::stencilOp(renderer::StencilOp::type fail,renderer::StencilOp::type zfail,renderer::StencilOp::type zpass)
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

void		OpenGL_GLSL_Driver::		enableGeneration(renderer::TextureCoord::type coord,renderer::TextureGenMode::type mode)
{
	glEnable(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord]);
	glTexGeni(OpenGL_GLSL_Tables::TextureCoord[coord],GL_TEXTURE_GEN_MODE,OpenGL_GLSL_Tables::TextureGenMode[mode]);
}

void		OpenGL_GLSL_Driver::	disableGeneration(renderer::TextureCoord::type coord)
{
	glDisable(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord]);
}

void		OpenGL_GLSL_Driver::	setEyePlane(renderer::TextureCoord::type coord,const math::vector3d& n)
{
	glTexGenfv(OpenGL_GLSL_Tables::TexGenSwitchEnum[coord],GL_EYE_PLANE,const_cast<math::vector3d&>(n));
}

void		OpenGL_GLSL_Driver::	setObjectPlane(renderer::TextureCoord::type coord,const math::vector3d& n)
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
		//std::cout << "r number of comp: " << (int)num_components[elem->type]  << std::endl;
		//std::cout << "r offset: " << elem->offset << std::endl;

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

void		OpenGL_GLSL_Driver::drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count)
{
	m_VF->enable();
	glDrawArrays(OpenGL_GLSL_Tables::Primitive[primitives],first,count);
	m_VF->disable();
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* buf)
{
	m_VF->enable();
	buf->bind(VBOType::INDEX);
	glDrawElements(OpenGL_GLSL_Tables::Primitive[primitives],count,OpenGL_GLSL_Tables::DataType[type],0);
	buf->unbind();
	m_VF->disable();
}

void		OpenGL_GLSL_Driver::drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData)
{
	OpenGL_GLSL_Driver::VertexFormat*	instd = new OpenGL_GLSL_Driver::VertexFormat(instanceDeclaration,m_Streams);
	m_VF->enable();
	for(unsigned i = 0; i < numInstances; i++)
	{
		instd->enableImmediate(i,instanceData);
		glDrawArrays(OpenGL_GLSL_Tables::Primitive[primitives],first,count);
	}
	m_VF->disable();
	delete instd;
}

void		OpenGL_GLSL_Driver::drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* indexBuffer,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData)
{
	OpenGL_GLSL_Driver::VertexFormat*	instd = new OpenGL_GLSL_Driver::VertexFormat(instanceDeclaration,m_Streams);
	m_VF->enable();
	indexBuffer->bind(VBOType::INDEX);
	for(unsigned i = 0; i < numInstances; i++)
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


void 		OpenGL_GLSL_Driver::setRenderMode(renderer::RenderSide::type side,renderer::RenderMode::type mode)
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

void		OpenGL_GLSL_Driver::setCullFace(renderer::RenderSide::type face)
{
	glCullFace(OpenGL_GLSL_Tables::RenderSide[face]);
}

void		OpenGL_GLSL_Driver::setFrontFace(renderer::FrontFace::type FrontFace)
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

const unsigned*
OpenGL_GLSL_Driver::getViewport() const
{
	return m_ViewPort;
}

//Renderer capabilities
int
OpenGL_GLSL_Driver::maxTextureSize() const
{
	return m_MaxTextureSize;
}
int
OpenGL_GLSL_Driver::maxCubeTextureSize() const
{
	return m_MaxCubeTextureSize;
}

int
OpenGL_GLSL_Driver::max3DTextureSize() const
{
	return m_Max3DTextureSize;
}

int
OpenGL_GLSL_Driver::numDrawBuffers() const
{
	return m_NumDrawBuffers;
}

int
OpenGL_GLSL_Driver::numTextureUnits() const
{
	return m_TextureUnits;
}

void		OpenGL_GLSL_Driver::setTexture(renderer::TextureUnit::type unit, Texture* tex)
{
	if(tex)
		static_cast<OpenGL_GLSL_Texture*>(tex)->bind(unit);
}

void 		OpenGL_GLSL_Driver::setMatrix(renderer::Matrix::type mode,const math::matrix4x4& mtx)
{
	if(mode == renderer::Matrix::VIEW)
	{
		glActiveTextureARB(GL_TEXTURE0);
		glMatrixMode(GL_TEXTURE);
	}
	else if(mode < renderer::Matrix::TEXTURE0)
	{
		glMatrixMode(OpenGL_GLSL_Tables::MatrixMode[mode]);
	}
	else
	{
		glActiveTextureARB(OpenGL_GLSL_Tables::MatrixMode[mode]);
		glMatrixMode(GL_TEXTURE);
	}

	//glLoadTransposeMatrixfARB(const_cast<GLfloat*>((const float*)mtx));
	glLoadMatrixf(math::transposed(mtx));
	glActiveTextureARB(GL_TEXTURE0);
	m_Matricies[mode] = mtx;
}

void 		OpenGL_GLSL_Driver::enableAlphaBlend()
{
	glEnable(GL_BLEND);
}

void 		OpenGL_GLSL_Driver::disableAlphaBlend()
{
	glDisable(GL_BLEND);
}

void 		OpenGL_GLSL_Driver::alphaBlendFunction(renderer::AlphaFunction::type sfactor,renderer::AlphaFunction::type dfactor) //sfactor and dfactor are described in AlphaFunction namespace. for more information refer to openGL specs
{
	glBlendFunc(OpenGL_GLSL_Tables::AlphaFunction[sfactor],OpenGL_GLSL_Tables::AlphaFunction[dfactor]);
}

void 		OpenGL_GLSL_Driver::alphaTestFunction(renderer::TestFunction::type func, float ref)
{
	glAlphaFunc(OpenGL_GLSL_Tables::TestFunction[func],ref);
}

EString
OpenGL_GLSL_Driver::getRendererName() const
{
	return m_RendererName;
}

EString
OpenGL_GLSL_Driver::getRendererVendor() const
{
	return m_RendererVendor;
}

//Scissor test
void		OpenGL_GLSL_Driver::enableScissorTest()
{
	glEnable(GL_SCISSOR_TEST);
}

void		OpenGL_GLSL_Driver::disableScissorTest()
{
	glDisable(GL_SCISSOR_TEST);
}

void		OpenGL_GLSL_Driver::clipArea(float left,float top, float right,float bottom)
{
	glScissor(left,top,math::abs(right - left), math::abs(top - bottom));
}

const math::matrix4x4 OpenGL_GLSL_Driver::getMatrix(renderer::Matrix::type mtx) const
		{
	return m_Matricies[mtx];
		}

}
}
}
