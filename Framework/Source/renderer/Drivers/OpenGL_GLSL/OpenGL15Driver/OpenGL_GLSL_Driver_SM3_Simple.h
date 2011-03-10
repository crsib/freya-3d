/*This header was generated from RenderingAPIDriver.h for Freya engine */
#ifndef OPENGL_GLSL_DRIVER3SIMPLE_H
#define OPENGL_GLSL_DRIVER3SIMPLE_H

#include "renderer/RenderingAPIDriver.h"
#include "core/memory/MemoryAllocator.h"

extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}

#include <list>
#include <map>

namespace renderer
{
namespace drivers
{
namespace ids
{
class OpenGL15DriverID;
}

namespace opengl_glsl_15
{
class OpenGL_GLSL_Texture;
class OpenGL_GLSL_VertexBufferObject;
class OpenGL_GLSL_Framebuffer;
class OpenGL_GLSL_Shader;

class	OpenGL_GLSL_Driver : public RenderingAPIDriver
{
	friend class renderer::drivers::ids::OpenGL15DriverID;
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

	//Scissor test
	virtual void		enableScissorTest();
	virtual void		disableScissorTest();
	virtual void		clipArea(float left,float top, float right,float bottom);

	virtual EString id() const;
	virtual EString getAPIName() const;
	virtual EString getShaderAPIName() const;

	virtual EString getRendererName() const;
	virtual EString	getRendererVendor() const;

	//Any combination of render futures
	virtual bool	futuresState(unsigned futures) const;
	virtual unsigned futures() const;

	//Viewport settings
	virtual void 		setViewport(unsigned x, unsigned y,unsigned width,unsigned height); //Sets the viewport
	virtual const unsigned*	 	getViewport() const;

	//Renderer capabilities
	virtual int			maxTextureSize() const;
	virtual int 		maxCubeTextureSize() const;
	virtual int			max3DTextureSize() const;
	virtual int 		numDrawBuffers() const;
	virtual int			numTextureUnits() const;

	//Clearing
	virtual void 		clearColorValue(float r,float g,float b,float a); //Sets the clear color
	virtual void 		clearColor();//Clears current color buffer
	//Depth test
	virtual void 		enableDepthTest();//enables deth test
	virtual void 		disableDepthTest();

	virtual void 		clearDepthValue(float val);//sets the depth default value
	virtual void 		clearDepth();//Clears depth

	virtual void 		depthFunction(renderer::TestFunction::type func);//Func is described in TestFunction namespace
	//Stencil test
	virtual void 		enableStencilTest();
	virtual void 		disableStencilTest();

	virtual void 		clearStencilValue(int val);
	virtual void 		clearStencil();

	virtual void 		stencilFunction(renderer::TestFunction::type func, int ref, unsigned mask);//func is compared to ref using mask
	virtual void 		stencilOp(renderer::StencilOp::type fail,renderer::StencilOp::type  zfail,renderer::StencilOp::type  zpass);//parameter are decribed in StencilOp namespace
	//Alpha test
	virtual void 		enableAlphaTest();
	virtual void 		disableAlphaTest();

	virtual void 		alphaTestFunction(renderer::TestFunction::type func, float ref);
	//Alpha blend
	virtual void 		enableAlphaBlend();
	virtual void 		disableAlphaBlend();

	virtual void 		alphaBlendFunction(renderer::AlphaFunction::type sfactor,renderer::AlphaFunction::type dfactor); //sfactor and dfactor are described in AlphaFunction namespace. for more information refer to openGL specs
	//Culling
	virtual void 		enableCulling();
	virtual void 		disableCulling();

	virtual void 		setFrontFace(renderer::FrontFace::type FrontFace);//As described by FrontFace namespace

	virtual void 		setRenderMode(renderer::RenderSide::type side,renderer::RenderMode::type mode);

	virtual void 		setCullFace(renderer::RenderSide::type Face); //As described by RenderSide namespace
	//Polygon offser
	virtual void 		enablePolygonOffset();
	virtual void 		disablePolygonOffset();

	virtual void 		setPolygonOffset(float factor,float units);
	//Matricies
	virtual void 		setMatrix(renderer::Matrix::type,const math::matrix4x4& mtx);//Loades matrix in row-major form
	virtual const math::matrix4x4 getMatrix(renderer::Matrix::type) const;
	//Auto generation of texture coordinates
	virtual void 		enableGeneration(renderer::TextureCoord::type coord,renderer::TextureGenMode::type mode); //enables generation for coord described by TextureCoord with mode descripbed by TextureGenMode
	virtual void		disableGeneration(renderer::TextureCoord::type coord);
	virtual void		setEyePlane(renderer::TextureCoord::type coord,const math::vector3d& n);//Sets the eye plane normal
	virtual void		setObjectPlane(renderer::TextureCoord::type coord,const math::vector3d& n);//Sets the object plane

	virtual void		setStreamSource(unsigned sourceID,VertexBufferObject* dataSource,unsigned offset,unsigned stride);
	virtual void		setVertexFormat(VertexElement*    element);

	virtual void		beginScene();
	virtual void		endScene() 	;

	//Rendering commands (all using vbo as data source)
	virtual void		drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count);//Render non-idexed primitive assembled as {primitves},starting from element {first} with count of elements (vertices)
	virtual void		drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* indexBuffer,ptrdiff_t offset);//Type is described by DataType

	virtual void		drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData);//Render non-idexed primitive assembled as {primitves},starting from element {first} with count of elements (vertices)
	virtual void		drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* indexBuffer,ptrdiff_t offset,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData);//Type is described by DataType

	//VBO (all said above is applicable to functions from this section
	virtual VertexBufferObject*
						createVertexBufferObject();
	virtual void		destroyVertexBufferObject(VertexBufferObject*	buf);
	//Frame buffers
	virtual Framebuffer*	createFramebuffer(); //Creates a framebuffer
	virtual void			destroyFramebuffer(Framebuffer* buf);
	//Shaders
	virtual Shader*			createShader();
	virtual void			destroyShader(Shader* shad);
	//Write modes
	virtual void			setColorWrite(bool r,bool g,bool b,bool a);
	virtual void			setDepthWrite(bool d);

	//Textures
	virtual Texture*	createTexture(); //Creates the texture object. Preferably called by the texture manager
	virtual void		destroyTexture(Texture* texture);//Destroys the texture. NB, as always, all allocated objects are freed on driver destroy
	virtual void		setTexture(renderer::TextureUnit::type unit, Texture* tex);

private:
	//Geometry shader support
	unsigned				m_Futures;
	//Objects management
	TextureList				m_TextureList;
	VertexBufferObjectList	m_VertexBufferObjectList;
	FramebufferList			m_FramebufferList;
	ShaderList				m_ShaderList;

	struct  StreamSource : public EngineSubsystem
	{
		VertexBufferObject*	buffer;
		unsigned			offset;
		unsigned			stride;
		StreamSource() : buffer(NULL),offset(0),stride(0){}
	};

	StreamSource		m_Streams[MAX_STREAM_SOURCES];

	class  VertexFormat: public EngineSubsystem
	{
		unsigned 		m_Size;
		unsigned		m_Length;
		VertexElement*	m_Format;
		StreamSource*	m_Streams;
	public:
		VertexFormat(VertexElement* format,StreamSource*	streams);
		void enable();
		void enableImmediate(unsigned inst,void* data);
		void disable();
	};

	VertexFormat*		m_VF;
	unsigned			m_ViewPort[4];
	EString				m_RendererName;
	EString				m_RendererVendor;
	int					m_MaxTextureSize;
	int					m_MaxCubeTextureSize;
	int					m_Max3DTextureSize;
	int					m_NumDrawBuffers;
	int					m_TextureUnits;
	math::matrix4x4		m_Matricies[renderer::Matrix::LAST_MATRIX];
};
}
}
}
#endif /* OPENGL_GLSL_DRIVER_H */
