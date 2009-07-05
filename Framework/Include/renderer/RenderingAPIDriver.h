/*
 * RenderingAPIDriver.h
 *
 *  Created on: 31.08.2008
 *      Author: vedenko
 */

#ifndef RENDERINGAPIDRIVER_H_
#define RENDERINGAPIDRIVER_H_

/*
 *
 */

#include "renderer/3DConstants.h"
#include "core/EString.h"
#include "core/memory/MemoryAllocator.h"
#include <vector>
#include "math/vector3d.hpp"
#include "math/matrix4x4.hpp"
#include "core/drivermodel/Driver.h"

namespace core
{
class EngineCore;
}

namespace math
{
class vector3d;
class matrix4x4;
class quaternion;
}

//!This namespace contains all rendering capable functions
namespace renderer
{

class Texture;
class VertexBufferObject;
class Framebuffer;
class Shader;

//! Per-instance data structure
typedef struct	_InstanceData
{
	//! A 4x4 matrix, usually used for instance transformations
	math::matrix4x4	ModelMatrix;
	//! A 3D vector, usually used as instance color
	math::vector3d	Color;
	//! A scalar value, can be used as alpha, or as some index, or as it is needed by implementation
	float			Alpha;

	_InstanceData& operator = (const _InstanceData& d)
	{
		ModelMatrix = d.ModelMatrix;
		Color = d.Color;
		Alpha = d.Alpha;
		return *this;
	}

	_InstanceData(const _InstanceData& d) : ModelMatrix(d.ModelMatrix), Color(d.Color),Alpha(d.Alpha)
	{
	}
	_InstanceData() : ModelMatrix(), Color(1.0,1.0,1.0), Alpha(1.0)
	{
	}
}	InstanceData; //A per instance data

//! Data type, used to hold instance arrays
typedef std::vector<InstanceData, core::memory::MemoryAllocator<InstanceData> > InstanceArray;

namespace futures
{
enum RenderFutures
{
	//Texturing
	MULTITEXTURE 					= 0x1,
	CUBE_MAP	   					= 0x2,
	RECTANGLE_TEXTURE	 			= 0x4,
	TEXTURE_3D						= 0x8,
	FLOAT_TEXTURE					= 0x10,
	NPOT_TEXTURE					= 0x20,
	COMPRESSED_TEXTURE				= 0x40,
	S3TC_TEXTURE					= 0x80,
	DEPTH_TEXTURE					= 0x100,
	GENERATE_MIPMAPS				= 0x200,
	ANISOTROPIC_FILTERING			= 0x400,

	//Framebuffers
	FRAMEBUFFER						= 0x1000,
	MRT								= 0x2000,
	PACKED_DEPTH_STENCIL			= 0x4000,

	//VBO
	VERTEX_BUFFER					= 0x10000,
	TEXTURE_BUFFER					= 0x20000,
	R2VB							= 0x40000,

	//Shaders
	VERTEX_SHADER					= 0x100000,
	FRAGMENT_SHADER					= 0x200000,
	GEOMETRY_SHADER					= 0x400000,
	SM40							= 0x800000,

	//Misc
	FOG_COORD						= 0x1000000,
	AUTO_TRANSPOSE_MATIRIX			= 0x2000000,

};

}

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
	RenderingAPIDriver()
	{
	}
	virtual ~RenderingAPIDriver()
	{
	}
public:

	//Driver params
	virtual EString id() const = 0;
	virtual EString getAPIName() const = 0;
	virtual EString getShaderAPIName() const = 0;

	//Any combination of render futures
	virtual bool	futuresState(unsigned futures) const = 0;
	virtual unsigned futures() const = 0;

	//Viewport settings
	virtual void setViewport(unsigned width,unsigned height) = 0; //Sets the viewport
	//Clearing
	virtual void clearColorValue(float r,float g,float b,float a) = 0; //Sets the clear color
	virtual void clearColor() = 0;//Clears current color buffer
	//Set perspective
	virtual void setPerspective(float FieldOfView,float Aspect,float Near,float Far) = 0; //Set perspective projection. FOW is in radians.
	virtual void setOrtho(unsigned width,unsigned height,float near = -1.0f,float far = 1.0f) = 0;//Sets orthographic projection
	//Depth test
	virtual void enableDepthTest() = 0;//enables deth test
	virtual void disableDepthTest() = 0;

	virtual void clearDepthValue(float val) = 0;//sets the depth default value
	virtual void clearDepth() = 0;//Clears depth

	virtual void depthFunction(unsigned func) = 0;//Func is described in TestFunction namespace
	//Stencil test
	virtual void enableStencilTest() = 0;
	virtual void disableStencilTest() = 0;

	virtual void clearStencilValue(int val) = 0;
	virtual void clearStencil() = 0;

	virtual void stencilFunction(unsigned func, int ref, unsigned mask) = 0;//func is compared to ref using mask
	virtual void stencilOp(unsigned fail,unsigned zfail,unsigned zpass) = 0;//parameter are decribed in StencilOp namespace
	//Alpha test
	virtual void enableAlphaTest() = 0;
	virtual void disableAlphaTest() = 0;

	virtual void alphaTestFunction(unsigned func, float ref) = 0;
	//Alpha blend
	virtual void enableAlphaBlend() = 0;
	virtual void disableAlphaBlend() = 0;

	virtual void alphaBlendFunction(unsigned sfactor,unsigned dfactor) = 0; //sfactor and dfactor are described in AlphaFunction namespace. for more information refer to openGL specs
	//Culling
	virtual void enableCulling() = 0;
	virtual void disableCulling() = 0;

	virtual void setFrontFace(unsigned FrontFace) = 0;//As described by FrontFace namespace

	virtual void setCullFace(unsigned Face) = 0; //As described by RenderSide namespace
	//Polygon offser
	virtual void enablePolygonOffset() = 0;
	virtual void disablePolygonOffset() = 0;

	virtual void setPolygonOffset(float factor,float units) = 0;
	//Matricies
	virtual void loadMatrix(const math::matrix4x4& mtx) = 0;//Loades matrix in column form

	virtual void loadIdentityMatrix() = 0;
	//Multiplies current matrix in row form
	virtual void multMatrix(const math::matrix4x4& mtx) = 0;//Multiplies current matrix in column form

	virtual void pushMatrix() = 0; //Pushes matrix
	virtual void popMatrix() = 0;  //Pops matrix

	virtual void setMatrixMode(unsigned mode) = 0; //Sets the matrix mode. Corresponding constants are in enum MatrixMode
	//Standart transformations
	//diplacements
	virtual void translate(float x,float y,float z) = 0; //translates by (x,y,z)
	virtual void translate(const math::vector3d& vec) = 0; //translates by vec
	//rotation
	virtual void rotate(float angle,float x,float y,float z) = 0; //Rotates by angle (in radians) round (x,y,z)
	virtual void rotate(float angle,const math::vector3d& vec) = 0;//Rotates by angle (in radians) round vec
	virtual void rotate(const math::quaternion& quat) = 0; //Rotates by quaternion (seems to be really slow,but who really cares)
	//Scaling
	virtual void scale(float x,float y,float z) = 0; //Scales by x,y,z
	//Textures
	virtual Texture*	createTexture() = 0; //Creates the texture object. Preferably called by the texture manager
	virtual void		destroyTexture(Texture* texture) = 0;//Destroys the texture. NB, as always, all allocated objects are freed on driver destroy
	//Auto generatio
	virtual void 		enableGeneration(unsigned coord,unsigned mode) = 0; //enables generation for coord described by TextureCoord with mode descripbed by TextureGenMode
	virtual void		disableGeneration(unsigned coord) = 0;
	virtual void		setEyePlane(unsigned coord,const math::vector3d& n) = 0;//Sets the eye plane normal
	virtual void		setObjectPlane(unsigned coord,const math::vector3d& n) = 0;//Sets the object plane
	//VBO (all said above is applicable to functions from this section
	virtual VertexBufferObject*	createVertexBufferObject() = 0;
	virtual void				destroyVertexBufferObject(VertexBufferObject*	buf) = 0;
	//Rendering commands (all using vbo as data source)
	virtual void	drawPrimitive(unsigned primitives,unsigned first,unsigned count) = 0;//Render non-idexed primitive assembled as {primitves},starting from element {first} with count of elements (vertices)
	virtual void	drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf) = 0;//Type is described by DataType
	//Same as two above,but with instancing
	virtual void	drawPrimitive(unsigned primitives,unsigned first,unsigned count,const InstanceArray& instances) = 0;
	virtual void	drawIndexedPrimitive(unsigned primitives,unsigned count,unsigned type,VertexBufferObject* buf,const InstanceArray& instances) = 0;
	//Enabling client states (e.g. what array types are supportes
	virtual void	enableClientState(unsigned state) = 0;//Enable client state described in ClientState namespace
	virtual void    disableClientState(unsigned state) = 0;

	virtual void	enableTextureCoordState(unsigned unit) = 0;
	virtual void	disableTextureCoordState(unsigned unit) = 0;
	//setting pointer for commands above. stride is an offset between data. Client state must be managed by program
	//dataType is described by DataType enum. numComponenets is number of componenet per data unit
	//buf - is a valid VBO
	virtual void	colorPointer(unsigned dataType,unsigned numComponents,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;
	virtual void 	colorIndexPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;

	virtual void	normalPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;

	virtual void	textureCoordPointer(unsigned unit,unsigned dataType,unsigned numComponenets,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;//Unit is a texture unit

	virtual void	vertexPointer(unsigned dataType,unsigned numComponenets,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;

	virtual void	fogCoordPointer(unsigned dataType,unsigned stride,VertexBufferObject*	buf,unsigned offset = 0) = 0;
	//Render mode: side is described by RenderSide namespace. mode is described by RenderMode namespace
	virtual void	setRenderMode(unsigned side,unsigned mode) = 0;
	//Fog settings (most of this functions are emulated by shader. Nevertheless, they give access to standart fog uniforms
	virtual void	enableFog() = 0;
	virtual void    disableFog() = 0;

	virtual void	setFogFunction(unsigned func) = 0;//As described by FogFunction namespace

	virtual void	setLinearFogBoundaries(float start,float end) = 0;
	virtual void	setFogDensity(float density) = 0;

	virtual void	setFogColor(float r,float g,float b,float a) = 0;
	//Frame buffers
	virtual Framebuffer*	createFramebuffer() = 0; //Creates a framebuffer
	virtual void			destroyFramebuffer(Framebuffer* buf) = 0;
	//Shaders
	virtual Shader*			createShader() = 0;
	virtual void			destroyShader(Shader* shad) = 0;
	//Write modes
	virtual void			setColorWrite(bool r,bool g,bool b,bool a) = 0;
	virtual void			setDepthWrite(bool d) = 0;
};


}

#endif /* RENDERINGAPIDRIVER_H_ */
