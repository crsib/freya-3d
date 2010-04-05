/*
 * RenderingAPIDriver.h
 *
 *  Created on: 31.08.2008
 *      Author: vedenko
 */

#ifndef RENDERINGAPIDRIVER_H_
#define RENDERINGAPIDRIVER_H_

#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
extern void* (*Allocate)(size_t,unsigned);
extern void  (*Free)(void*,unsigned);
}
}
#endif
/*
 *
 */

#include "renderer/3DConstants.h"
#include "core/EString.h"
#include "core/memory/MemoryAllocator.h"
#include <vector>
#include "core/drivermodel/Driver.h"
#include "math/math.hpp"

namespace core
{
class EngineCore;
}

//!This namespace contains all rendering capable functions
namespace renderer
{

class Texture;
class VertexBufferObject;
class Framebuffer;
class Shader;

namespace futures
{
enum RenderFutures
{
	//Texturing
			MULTITEXTURE 					= 0x1,  // bit 1
			CUBE_MAP	   					= 0x2,  // bit 2
			RECTANGLE_TEXTURE	 			= 0x4,  // bit 3
			TEXTURE_3D						= 0x8,  // bit 4
			FLOAT_TEXTURE					= 0x10,  // bit 5
			NPOT_TEXTURE					= 0x20,  // bit 6
			COMPRESSED_TEXTURE				= 0x40,  // bit 7
			S3TC_TEXTURE					= 0x80,  // bit 8
			DEPTH_TEXTURE					= 0x100,  // bit 9
			GENERATE_MIPMAPS				= 0x200,  // bit 10
			ANISOTROPIC_FILTERING			= 0x400,  // bit 11
			TEXTURE_ARRAY					= 0x800,  // bit 12

			//Framebuffers
			FRAMEBUFFER						= 0x1000,  // bit 13
			MRT								= 0x2000,  // bit 14
			PACKED_DEPTH_STENCIL			= 0x4000,  // bit 15

			//VBO
			VERTEX_BUFFER					= 0x10000,  // bit 17
			TEXTURE_BUFFER					= 0x20000,  // bit 18
			PIXEL_BUFFER					= TEXTURE_BUFFER,
			R2VB							= 0x40000,  // bit 19

			//Shaders
			VERTEX_SHADER					= 0x100000,  // bit 21
			FRAGMENT_SHADER					= 0x200000,  // bit 22
			GEOMETRY_SHADER					= 0x400000,  // bit 23
			SM40							= 0x800000,  // bit 24

			//Matricies
			HAS_DEFAULT_VIEW_BIND			= 0x1000000, // bit 25
			HAS_DEFUALT_WORLD_BIND			= 0x2000000, // bit 26
			HAS_DEFAULT_PROJECTION_BIND		= 0x4000000, // bit 27
};

}

#define	MAX_STREAM_SOURCES 32

struct VertexElement : public EngineSubsystem
{
	VertexElement(unsigned sid,renderer::VertexFormat::USAGE usg,renderer::VertexFormat::TYPE tp,unsigned off)
	: streamID(sid),usage(usg),type(tp),offset(off){}
	VertexElement(){}
	unsigned				streamID;
	VertexFormat::USAGE		usage;
	VertexFormat::TYPE		type;
	unsigned 				offset;
};
#define FREYA_DECLARATION(sid,usg,tp,off) renderer::VertexElement(sid,usg,tp,off)
#define FREYA_LAST_DECLARATION() renderer::VertexElement((unsigned)-1,renderer::VertexFormat::UNUSED,renderer::VertexFormat::DWORD,0)

//! The abstraction class for generally used rendering commands
/*!
 * This class provides an abstraction of generally used rendering commands, to provide an API independent way of programming 3D graphics.
 * It is actually separated into 5 parts. The first 4 parts are represented as subsystems and provide access for framebuffer (renderer::Framebuffer),
 * shader (renderer::Shader), texture (renderer::Texture) and VBO (renderer::VertexBufferObject) in a simple, clearly looking way.
 * All commands, that do not belong to any of those subsystems are represented inside this class, among with commands for managing described above subsystems.
 * Please note, as said in the very first draft specification, only this class can be used to create/destroy any subsystem. Memory management is done mostly automatically,
 * e.g. RenderingAPIDriver will gracefully destroy all subsystems, that were not destroyed manually at the time it will be destructed itself
 */
class RenderingAPIDriver: public core::drivermodel::Driver
{
	friend class core::EngineCore;
protected:
	virtual ~RenderingAPIDriver()
	{
	}
public:

	//Driver params
	virtual EString id() const = 0;
	virtual EString getAPIName() const = 0;
	virtual EString getShaderAPIName() const = 0;

	virtual EString getRendererName() const = 0;
	virtual EString	getRendererVendor() const = 0;

	//Any combination of render futures
	virtual bool	futuresState(unsigned futures) const = 0;
	virtual unsigned futures() const = 0;

	//Viewport settings
	virtual void 		setViewport(unsigned x, unsigned y,unsigned width,unsigned height) = 0; //Sets the viewport
	virtual const unsigned*	 	getViewport() const = 0;

	//Renderer capabilities
	virtual int			maxTextureSize() const = 0;
	virtual int 		maxCubeTextureSize() const = 0;
	virtual int			max3DTextureSize() const = 0;
	virtual int 		numDrawBuffers() const = 0;
	virtual int			numTextureUnits() const = 0;

	//Clearing
	virtual void 		clearColorValue(float r,float g,float b,float a) = 0; //Sets the clear color
	virtual void 		clearColor() = 0;//Clears current color buffer
	//Depth test
	virtual void 		enableDepthTest() = 0;//enables deth test
	virtual void 		disableDepthTest() = 0;

	virtual void 		clearDepthValue(float val) = 0;//sets the depth default value
	virtual void 		clearDepth() = 0;//Clears depth

	virtual void 		depthFunction(renderer::TestFunction::type func) = 0;//Func is described in TestFunction namespace
	//Scissor test
	virtual void		enableScissorTest() = 0;
	virtual void		disableScissorTest() = 0;
	virtual void		clipArea(float left,float top, float right,float bottom) = 0;

	//Stencil test
	virtual void 		enableStencilTest() = 0;
	virtual void 		disableStencilTest() = 0;

	virtual void 		clearStencilValue(int val) = 0;
	virtual void 		clearStencil() = 0;

	virtual void 		stencilFunction(renderer::TestFunction::type func, int ref, unsigned mask) = 0;//func is compared to ref using mask
	virtual void 		stencilOp(renderer::StencilOp::type fail,renderer::StencilOp::type  zfail,renderer::StencilOp::type  zpass) = 0;//parameter are decribed in StencilOp namespace
	//Alpha test
	virtual void 		enableAlphaTest() = 0;
	virtual void 		disableAlphaTest() = 0;

	virtual void 		alphaTestFunction(renderer::TestFunction::type func, float ref) = 0;
	//Alpha blend
	virtual void 		enableAlphaBlend() = 0;
	virtual void 		disableAlphaBlend() = 0;

	virtual void 		alphaBlendFunction(renderer::AlphaFunction::type sfactor,renderer::AlphaFunction::type dfactor) = 0; //sfactor and dfactor are described in AlphaFunction namespace. for more information refer to openGL specs
	//Culling
	virtual void 		enableCulling() = 0;
	virtual void 		disableCulling() = 0;

	virtual void 		setFrontFace(renderer::FrontFace::type FrontFace) = 0;//As described by FrontFace namespace

	virtual void 		setCullFace(renderer::RenderSide::type Face) = 0; //As described by RenderSide namespace
	//Polygon offser
	virtual void 		enablePolygonOffset() = 0;
	virtual void 		disablePolygonOffset() = 0;

	virtual void 		setPolygonOffset(float factor,float units) = 0;
	//Matricies
	virtual void 		setMatrix(renderer::Matrix::type,const math::matrix4x4& mtx) = 0;//Loades matrix in row-major form
	virtual const math::matrix4x4 getMatrix(renderer::Matrix::type) const = 0;
	//Auto generation of texture coordinates
	virtual void 		enableGeneration(renderer::TextureCoord::type coord,renderer::TextureGenMode::type mode) = 0; //enables generation for coord described by TextureCoord with mode descripbed by TextureGenMode
	virtual void		disableGeneration(renderer::TextureCoord::type coord) = 0;
	virtual void		setEyePlane(renderer::TextureCoord::type coord,const math::vector3d& n) = 0;//Sets the eye plane normal
	virtual void		setObjectPlane(renderer::TextureCoord::type coord,const math::vector3d& n) = 0;//Sets the object plane

	virtual void		setStreamSource(unsigned sourceID,VertexBufferObject* dataSource,unsigned offset,unsigned stride) = 0;
	virtual void		setVertexFormat(VertexElement*    element) = 0;

	virtual void		beginScene() = 0;
	virtual void		endScene() 	 = 0;

	//Rendering commands (all using vbo as data source)
	virtual void		drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count) = 0;//Render non-idexed primitive assembled as {primitves},starting from element {first} with count of elements (vertices)
	virtual void		drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* indexBuffer, ptrdiff_t offset = 0) = 0;//Type is described by DataType

	virtual void		drawPrimitive(renderer::Primitive::type primitives,unsigned first,unsigned count,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData) = 0;//Render non-idexed primitive assembled as {primitves},starting from element {first} with count of elements (vertices)
	virtual void		drawIndexedPrimitive(renderer::Primitive::type primitives,unsigned count,renderer::DataType::type type,VertexBufferObject* indexBuffer,ptrdiff_t offset,VertexElement* instanceDeclaration,unsigned numInstances,void* instanceData) = 0;//Type is described by DataType

	virtual void 		setRenderMode(renderer::RenderSide::type side,renderer::RenderMode::type mode) = 0;

	//VBO (all said above is applicable to functions from this section
	virtual VertexBufferObject*
						createVertexBufferObject() = 0;
	virtual void		destroyVertexBufferObject(VertexBufferObject*	buf) = 0;
	//Frame buffers
	virtual Framebuffer*	createFramebuffer() = 0; //Creates a framebuffer
	virtual void			destroyFramebuffer(Framebuffer* buf) = 0;
	//Shaders
	virtual Shader*			createShader() = 0;
	virtual void			destroyShader(Shader* shad) = 0;
	//Write modes
	virtual void			setColorWrite(bool r,bool g,bool b,bool a) = 0;
	virtual void			setDepthWrite(bool d) = 0;

	//Textures
	virtual Texture*	createTexture() = 0; //Creates the texture object. Preferably called by the texture manager
	virtual void		destroyTexture(Texture* texture) = 0;//Destroys the texture. NB, as always, all allocated objects are freed on driver destroy
	virtual void		setTexture(renderer::TextureUnit::type unit, Texture* tex) = 0;
};


}

#endif /* RENDERINGAPIDRIVER_H_ */
