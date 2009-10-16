/*
 * 3DConstants.h
 *
 *  Created on: 03.09.2008
 *      Author: vedenko
 */

#ifndef _3DCONSTANTS_H_
#define _3DCONSTANTS_H_

namespace renderer
{
//Matrix mode

//!Matrix mode constants
namespace MatrixMode
{
enum TYPE
{
	//!Model matrix
	MODEL,WORLD = MODEL, //View/modelview matricies
	//!Modelview matrix (same as projection now)
	MODELVIEW,
	//!Projection matrix
	PROJECTION,//Projection matricies
	//!Matrix for texture unit 0
	TEXTURE0, //Texture matricies on following unit
	//!Matrix for texture unit 1
	TEXTURE1,
	//!Matrix for texture unit 2
	TEXTURE2,
	//!Matrix for texture unit 3
	TEXTURE3,
	//!Matrix for texture unit 4
	TEXTURE4,
	//!Matrix for texture unit 5
	TEXTURE5,
	//!Matrix for texture unit 6
	TEXTURE6,
	//!Matrix for texture unit 7
	TEXTURE7,
	//!Matrix for texture unit 8
	TEXTURE8,
	//!Matrix for texture unit 9
	TEXTURE9,
	//!Matrix for texture unit 10
	TEXTURE10,
	//!Matrix for texture unit 11
	TEXTURE11,
	//!Matrix for texture unit 12
	TEXTURE12,
	//!Matrix for texture unit 13
	TEXTURE13,
	//!Matrix for texture unit 14
	TEXTURE14,
	//!Matrix for texture unit 15
	TEXTURE15,
	//!Matrix for texture unit 16
	TEXTURE16,
	//!Matrix for texture unit 17
	TEXTURE17,
	//!Matrix for texture unit 18
	TEXTURE18,
	//!Matrix for texture unit 19
	TEXTURE19,
	//!Matrix for texture unit 20
	TEXTURE20,
	//!Matrix for texture unit 21
	TEXTURE21,
	//!Matrix for texture unit 22
	TEXTURE22,
	//!Matrix for texture unit 23
	TEXTURE23,
	//!Matrix for texture unit 24
	TEXTURE24,
	//!Matrix for texture unit 25
	TEXTURE25,
	//!Matrix for texture unit 26
	TEXTURE26,
	//!Matrix for texture unit 27
	TEXTURE27,
	//!Matrix for texture unit 28
	TEXTURE28,
	//!Matrix for texture unit 29
	TEXTURE29,
	//!Matrix for texture unit 30
	TEXTURE30,
	//!Matrix for texture unit 31
	TEXTURE31
};
}

//Texture constants
//!Texture unit constants
namespace TextureUnit
{
enum TYPE
{
	//! Texture unit 0
	TEXTURE0, //Texture unit
	//! Texture unit 1
	TEXTURE1,
	//! Texture unit 2
	TEXTURE2,
	//! Texture unit 3
	TEXTURE3,
	//! Texture unit 4
	TEXTURE4,
	//! Texture unit 5
	TEXTURE5,
	//! Texture unit 6
	TEXTURE6,
	//! Texture unit 7
	TEXTURE7,
	//! Texture unit 8
	TEXTURE8,
	//! Texture unit 9
	TEXTURE9,
	//! Texture unit 10
	TEXTURE10,
	//! Texture unit 11
	TEXTURE11,
	//! Texture unit 12
	TEXTURE12,
	//! Texture unit 13
	TEXTURE13,
	//! Texture unit 14
	TEXTURE14,
	//! Texture unit 15
	TEXTURE15,
	//! Texture unit 16
	TEXTURE16,
	//! Texture unit 17
	TEXTURE17,
	//! Texture unit 18
	TEXTURE18,
	//! Texture unit 19
	TEXTURE19,
	//! Texture unit 20
	TEXTURE20,
	//! Texture unit 21
	TEXTURE21,
	//! Texture unit 22
	TEXTURE22,
	//! Texture unit 23
	TEXTURE23,
	//! Texture unit 24
	TEXTURE24,
	//! Texture unit 25
	TEXTURE25,
	//! Texture unit 26
	TEXTURE26,
	//! Texture unit 27
	TEXTURE27,
	//! Texture unit 28
	TEXTURE28,
	//! Texture unit 29
	TEXTURE29,
	//! Texture unit 30
	TEXTURE30,
	//! Texture unit 31
	TEXTURE31
};
}
//!Texture type constants
namespace TextureType
{
enum TYPE
{
	//!1D texture
	TEXTURE_1D, //1d textures
	//!2D texture
	TEXTURE_2D, //2d textures
	//!3D texture
	TEXTURE_3D, //3d textures
	//!Cube texture
	TEXTURE_CUBE, //Cube textures
	//!Rectangle texture
	TEXTURE_RECTANGLE//Rectangle texture
};
}
//! Internal texture formats (the way texture is represented inside accelerator)
namespace TextureInternalFormat
{
enum TYPE
{
	//! 4-bit alpha channel
	ALPHA4,
	//! 8-bit alpha channel
	ALPHA8,
	//! 12-bit alpha channel
	ALPHA12,
	//! 16-bit alpha channel
	ALPHA16,
	//! 4-bit luminance (available via R channel)
	LUMINANCE4,
	//! 8-bit luminance (available via R channel)
	LUMINANCE8,
	//! 12-bit luminance (available via R channel)
	LUMINANCE12,
	//! 16-bit luminance (available via R channel)
	LUMINANCE16,
	//! 4-bit luminance + 4-bit alpha
	LUMINANCE4_ALPHA4,
	//! 6-bit luminance + 2-bit alpha
	LUMINANCE6_ALPHA2,
	//! 8-bit luminance + 8-bit alpha
	LUMINANCE8_ALPHA8,
	//! 12-bit luminance + 4-bit alpha
	LUMINANCE12_ALPHA4,
	//! 12-bit luminance + 12-bit alpha
	LUMINANCE12_ALPHA12,
	//! 16-bit luminance + 16-bit alpha
	LUMINANCE16_ALPHA16,
	//! 4-bit intensity (accessible via any channel)
	INTENSITY4,
	//! 8-bit intensity (accessible via any channel)
	INTENSITY8,
	//! 12-bit intensity (accessible via any channel)
	INTENSITY12,
	//! 16-bit intensity (accessible via any channel)
	INTENSITY16,
	//! 3-bit R + 3-bit G + 2-bit B (represented as RGB in vram)
	R3_G3_B2,
	//! 4-bit R + 4-bit G + 4-bit B (represented as RGB in vram)
	RGB4,
	//! 5-bit R + 5-bit G + 5-bit B (represented as RGB in vram)
	RGB5,
	//! 8-bit R + 8-bit G + 8-bit B (represented as RGB in vram)
	RGB8,
	//! 10-bit R + 10-bit G + 10-bit B (represented as RGB in vram)
	RGB10,
	//! 12-bit R + 12-bit G + 12-bit B (represented as RGB in vram)
	RGB12,
	//! 3-bit R + 3-bit G + 2-bit B (represented as RGB in vram)
	RGB16,
	//! 2-bit R + 2-bit G + 2-bit B + 2-bit A (represented as RGBA in vram)
	RGBA2,
	//! 4-bit R + 4-bit G + 4-bit B + 4-bit A (represented as RGBA in vram)
	RGBA4,
	//! 5-bit R + 5-bit G + 5-bit B + 1-bit A (represented as RGBA in vram)
	RGB5_A1,
	//! 8-bit R + 8-bit G + 8-bit B + 8-bit A (represented as RGBA in vram)
	RGBA8,
	//! 10-bit R + 10-bit G + 10-bit B + 2-bit A (represented as RGBA in vram)
	RGB10_A2,
	//! 12-bit R + 12-bit G + 12-bit B + 12-bit A (represented as RGBA in vram)
	RGBA12,
	//! 16-bit R + 16-bit G + 16-bit B + 16-bit A (represented as RGBA in vram)
	RGBA16,
	//Floating point formats
	//! 32-bit float R + 32-bit float G + 32-bit float B + 32-bit float A (represented as RGBA in vram, no clamping)
	RGBA32F,
	//! 16-bit float R + 16-bit float G + 16-bit float B + 16-bit float A (represented as RGBA in vram, no clamping)
	RGBA16F,
	//! 32-bit float R + 32-bit float G + 32-bit float B (represented as RGB in vram, no clamping)
	RGB32F,
	//! 16-bit float R + 16-bit float G + 16-bit float B (represented as RGB in vram, no clamping)
	RGB16F,
	//! 32-bit float intensity (accessible via any channel)
	INTENSITY32F,
	//! 16-bit float intensity (accessible via any channel)
	INTENSITY16F,
	//! 32-bit float alpha
	ALPHA32F,
	//! 16-bit float alpha
	ALPHA16F,
	//! 32-bit float luminance (accessible by R)
	LUMINANCE32F,
	//! 16-bit float luminance (accessible by R)
	LUMINANCE16F,
	//! 32-bit float luminance (accessible by R) + 32-bit float alpha
	LUMINANCE_ALPHA32F,
	//! 16-bit float luminance (accessible by R) + 16-bit float alpha
	LUMINANCE_ALPHA16F,
	//Frame buffer
	//! 16-bit depth
	DEPTH16,
	//! 24-bit depth
	DEPTH24,
	//! 32-bit depth
	DEPTH32,
	//! 1-bit stencil
	STENCIL1,
	//! 4-bit stencil
	STENCIL4,
	//! 8-bit stencil
	STENCIL8,
	//! 16-bit stencil
	STENCIL16,
	//! 24-bit depth + 8-bit stencil (if supported only, otherwise treated as DEPTH24. Depth channel is accessible in usual way)
	DEPTH24_STENCIL8,
	//Compressed textures
	//! Starting value for compressed texture formats
	COMPRESSED,
	//S3TC
	//! RGB DXT1
	RGB_DXT1 = COMPRESSED,
	//! RGBA DXT1
	RGBA_DXT1,
	//! DXT3
	RGBA_DXT3,
	//! DXT5
	RGBA_DXT5
};
}
//! Texture external storage format
namespace TextureStorage
{
enum TYPE
{
	//! Components stored as unsigned byte
	UNSIGNED_BYTE,
	//! Components stored as signed byte
	BYTE,
	//! Components stored as unsigned short
	UNSIGNED_SHORT,
	//! Components stored as signed short
	SHORT,
	//! Components stored as unsigned int
	UNSIGNED_INT,
	//! Components stored as signed int
	INT,
	//! Components stored as 32-bit float
	FLOAT
};

}
//! External texture representation format
namespace TextureFormat
{
enum TYPE
{
	//! Stored value is an index to palet (left for compatibility only)
	COLOR_INDEX,
	//! Stored value is a single R component
	RED,
	//! Stored value is a single G component
	GREEN,
	//! Stored value is a single B component
	BLUE,
	//! Stored value is a single A component
	ALPHA,
	//! Stored value is a RGB triplet
	RGB,
	//! Stored value is a RGBA quadlet
	RGBA,
	//! Stored value is a single luminance value
	LUMINANCE,
	//! Stored value is a luminance alpha pair
	LUMINANCE_ALPHA,
	//! Stored value is a single depth component
	DEPTH,
	//! Stored value is a depth stencil pair (if supported, otherwise is treated as DEPTH)
	DEPTH_STENCIL
};
}
//! Texture filtering modes
namespace TextureFiltering
{
enum TYPE
{
	//! Filtering is disabled
	NEAREST,
	//! Filtering is linear
	LINEAR,
	//! Filtering is 1.5-linear (lerp via two nearest fragments of different mip-levels. Only for use with min filter)
	NEAREST_MIPMAP_NEAREST,
	//! Filtering is 1.5-linear (lerp via nearest fragment of first level and lerp'ed value from another one. Only for use with min filter)
	NEAREST_MIPMAP_LINEAR,
	//! Filtering is 1.5-linear (lerp via lerp'ed value of first level and nearest fragment from another one. Only for use with min filter)
	LINEAR_MIPMAP_NEAREST,
	//! Filtering is bi-linear (sometimes called three linear. Only for use with min filter)
	LINEAR_MIPMAP_LINEAR
};
}
//! Texture clamping modes
namespace TextureClamping
{
enum TYPE
{
	//! Clamp texture coordinates to [0,1]
	CLAMP,
	//! Clamp texture coordinates to [0,1] using info about edges
	CLAMP_TO_EDGE,
	//! Clamp texture coordinates to [0,1] using info about borders (usefull with cubemapping)
	CLAMP_TO_BORDER,
	//! Repeat texture coordinates
	REPEAT
};
}
//! Sides of cube textures (NOTE: to resolve cross-api portability the default coordinate system is treated in OpenGL way. E.g. the right triplet)
namespace CubeTextureSide
{
enum TYPE
{
	//!Positive x (e.g. right) side
	X_POSITIVE,
	//!Negative x (e.g. left) side
	X_NEGATIVE,
	//!Positive y (e.g. top) side
	Y_POSITIVE,
	//!Negative y (e.g. bottom) side
	Y_NEGATIVE,
	//!Positive z (e.g. front) side
	Z_POSITIVE,
	//!Negative z (e.g. back) side
	Z_NEGATIVE
};
}
//! Texture coordinates
namespace TextureCoord
{
enum TYPE
{
	//!S coordinate
	S,
	//!T coordinate
	T,
	//!R (a.k.a P) coordinate
	R,
	//!Q coordinate
	Q
};
}
//! Texture generation modes
namespace TextureGenMode
{
enum TYPE
{
	//! Generate with respect to object
	OBJECT_LINEAR,
	//! Generate with respect to watcher
	EYE_LINEAR,
	//! Generate spherically
	SPHERE,
	//! Generate for reflection usage
	REFLECTION,
	//! Generate using normal values
	NORMAL
};
}
//VBO constants

//! Vertex buffer object target (e.g. how the vertex buffer will be threated)
namespace VBOType //Type of a buffer
{
enum TYPE
{
	//! Buffer is a normal vertex buffer
	VERTEX,//Vertex buffer
	//! Buffer is to be used for indexing another vertex buffer
	INDEX, //Index buffer
	//! Buffer will be treaded as a render target for vertex data
	R2VB,  //Texture, associated with buffer is treated as vertex buffer
	//! Buffer is used for fast texture data exchange beetween ram and vram
	TEXTURE//Buffer is used to exchange texture data
};
}

//! Alias for VBOType
namespace VBOTarget = VBOType;
//!
namespace VBOUsage	//Comment for video driver on how to use buffer data
{
enum TYPE
{
	//! Buffer data is changed rarely and used mostly for drawing
	STREAM_DRAW, //As described in VBO OpenGL spec
	//! Buffer data is changed rarely and used mostly for data exchange
	STREAM_COPY,
	//! Buffer data is changed rarely and used mostly for data reading from CPU
	STREAM_READ,
	//! Buffer data is changed frequently and used mostly for drawing
	DYNAMIC_DRAW,
	//! Buffer data is changed frequently and used mostly for data exchange
	DYNAMIC_COPY,
	//! Buffer data is changed frequently and used mostly for data reading
	DYNAMIC_READ,
	//! Buffer data is constant and used mostly for drawing
	STATIC_DRAW,
	//! Buffer data is constant and used mostly for reading
	STATIC_READ,
	//! Buffer data is constant and used mostly for data exchange
	STATIC_COPY
};
}

//! VBO access modes to mapped memory
namespace VBOAccess //The way in which buffer is mapped into the client memory
{
enum TYPE
{
	//! Access is read only
	READ_ONLY,
	//! Access is write only (mapped memory area does not correspond to buffer data)
	WRITE_ONLY,
	//! Bidirectional access
	READ_WRITE
};
}

//Primitive types
//! The type of primitives for rendering
namespace Primitive
{
enum TYPE
{
	//! Each vertex is treated as a single point
	POINTS,
	//! The two successive vertices are treated as line endings
	LINES,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	LINES_ADJACENCY,
	//! Successive vertices are connected with lines
	LINE_STRIP,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	LINE_STRIP_ADJACENCY,
	//! Successive verticies are connected with lines. Last vertex is connect with first
	LINES_LOOP,
	//! Vertices triplets are used to create triangle
	TRIANGLES,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	TRIANGLES_ADJACENCY,
	//! Triangles are constructed as following (with correction for bypass direction) (1,2,3),(2,3,4),(3,4,5)...
	TRIANGLE_STRIP,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	TRIANGLE_STRIP_ADJACENCY,
	//! Triangles are constructed as following (with correction for bypass direction) (1,2,3),(1,3,4),(1,4,5)...
	TRIANGLE_FAN,
};
}
//Render and culling types
// Render side modes (for various culling routines etc)
namespace RenderSide
{
enum TYPE
{
	//! Front side
	FRONT,
	//! Back side
	BACK,
	//! Both sides
	FRONT_AND_BACK
};
}

//Render mode
//! The way the rendering is performed
namespace RenderMode
{
enum TYPE
{
	//! Render all vertices as points
	POINT,
	//! Render all in wire-frame mode
	LINE,
	//! Render all in a normal way
	FILL
};
}
//! Type used for data storage
namespace DataType
{
enum TYPE
{
	//! Data is represented by bytes
	BYTE,
	//! Data is represented by unsigned bytes
	UNSIGNED_BYTE,
	//! Data is represented by short int's
	SHORT,
	//! Data is represented by unsigned short int's
	UNSIGNED_SHORT,
	//! Data is represented by int's
	INT,
	//! Data is represented by unsiged int's
	UNSIGNED_INT,
	//! Data is represented by 32-bit floats
	FLOAT,
	//! Data is represented by 64-bit floats
	DOUBLE
};
}
//! Represent state of client application data pointers (mostly for OpenGL compatibility)
namespace ClientState
{
enum TYPE
{
	//! Pointer to color index buffer
	COLOR_INDEX_ARRAY,
	//! Pointer to vertex buffer
	VERTEX_ARRAY,
	//! Pointer to normal buffer
	NORMAL_ARRAY,
	//! Pointer to color buffer
	COLOR_ARRAY,
	//! Pointer to fog coordinates buffer
	FOG_COORD_ARRAY
};
}
//Test functions constants
//! Constants to various test functions
namespace TestFunction
{
enum TYPE
{
	//! return false
	NEVER,
	//! return \f$a<b\f$
	LESS,
	//! return \f$a>b\f$
	GREATER,
	//! return \f$a=b\f$
	EQUAL,
	//! return \f$a \ge b\f$
	GREATER_EQUAL,
	//! return \f$a \le b\f$
	LESS_EQUAL,
	//! return \f$a \ne b\f$
	NOT_EQUAL,
	//! return true
	ALWAYS
};
}

//Stencil
//! Stencil test operations
namespace StencilOp
{
enum TYPE
{
	//! Keep
	KEEP,
	//! Flush to 0
	ZERO,
	//! Replace
	REPLACE,
    //! Increment
	INCREMENT,
	//! Decrement
	DECREMENT,
	//! Invert
	INVERT
};
}
//! Alpha functions
/*!
 * All colors are referred as clamped to [0,1]
 * Blend operator is always + (as blending is mostly left compatibility)
 * \f$ dest = source*f_s + dest*f_d, (x_1,x_2,x_3,x_4) (y_1,y_2,y_3,y_4) = (x_1 y_1,x_2 y_2,x_3 y_3, x_4 y_4)  \f$
 */
namespace AlphaFunction
{

enum TYPE
{
	//! \f$ f_i = (0,0,0,0) \f$
	ZERO,
	//! \f$ f_i = (1,1,1,1) \f$
	ONE,
	//! \f$ f_i = (r_d,g_d,b_d,a_d) \f$
	DST_COLOR,
	//! \f$ f_i = (1,1,1,1) - (r_d,g_d,b_d,a_d) \f$
	ONE_MINUS_DST_COLOR,
	//! \f$ f_i = (a_d,a_d,a_d,a_d) \f$
	DST_ALPHA,
	//! \f$ f_i = (1,1,1,1) - (a_d,a_d,a_d,a_d) \f$
	ONE_MINUS_DST_ALPHA,
	//! \f$ f_i = (r_s,g_s,b_s,a_s) \f$
	SRC_COLOR,
	//! \f$ f_i = (1,1,1,1)-(r_s,g_s,b_s,a_s) \f$
	ONE_MINUS_SRC_COLOR,
	//! \f$ f_i = (a_s,a_s,a_s,a_s) \f$
	SRC_ALPHA,
	//! \f$ f_i = (1,1,1,1)-(a_s,a_s,a_s,a_s) \f$
	ONE_MINUS_SRC_ALPHA,
	//! \f$ f_i = (a,a,a,a), a = \min (a_s,1-a_s)\f$
	SRC_ALPHA_SATURATE
};
}

//! Fog functions (for compatibility only)
/*!
 * c - is a distance to processing fragment from viewer <BR>
 * start, end - linear fog ranges (respectively to viewer)) <BR>
 * density - fog density
 */
namespace FogFunction
{
enum TYPE
{
	//! \f$ f=\frac{end - c}{end-start}\f$
	LINEAR,
	//! \f$ f= e^{-density \cdot c} \f$
	EXP,
	//! \f$ f= e^{-(density \cdot c)^2} \f$
	EXP2
};
}
//Culling
//! The bypass direction for front face
namespace FrontFace
{
enum TYPE
{
	//! Clock wise bypass identifies front face
	CLOCK_WISE,
	//! Counter clock wise bypass identifies front face (default)
	COUNTER_CLOCK_WISE
};
}

//FBO
//!Framebuffer attachments
namespace FramebufferAttachment
{
enum TYPE
{
	//! Color attachment 0
	COLOR_ATTACHMENT0,
	//! Color attachment 1
	COLOR_ATTACHMENT1,
	//! Color attachment 2
	COLOR_ATTACHMENT2,
	//! Color attachment 3
	COLOR_ATTACHMENT3,
	//! Color attachment 4
	COLOR_ATTACHMENT4,
	//! Color attachment 5
	COLOR_ATTACHMENT5,
	//! Color attachment 6
	COLOR_ATTACHMENT6,
	//! Color attachment 7
	COLOR_ATTACHMENT7,
	//! Color attachment 8
	COLOR_ATTACHMENT8,
	//! Color attachment 9
	COLOR_ATTACHMENT9,
	//! Color attachment 10
	COLOR_ATTACHMENT10,
	//! Color attachment 11
	COLOR_ATTACHMENT11,
	//! Color attachment 12
	COLOR_ATTACHMENT12,
	//! Color attachment 13
	COLOR_ATTACHMENT13,
	//! Color attachment 14
	COLOR_ATTACHMENT14,
	//! Color attachment 15
	COLOR_ATTACHMENT15,
	//! Depth attachment
	DEPTH_ATTACHMENT,
	//! Stencil attachment
	STENCIL_ATTACHMENT
};
}
//! Status of framebuffer
namespace FramebufferStatus
{
enum TYPE
{
	//! Everything is ok
	FRAMEBUFFER_COMPLETE,
	//! There is (are) incomplete attachment(s)
	FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	//! There are no attachments
	FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	//! Attachments have different dimensions
	FRAMEBUFFER_INCOMPLETE_DIMENSIONS,
	//! Attachments have different BPP format
	FRAMEBUFFER_INCOMPLETE_FORMATS,
	//! Not enough color attachments for all draw buffers
	FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	//! Not enough color attachments for read buffer
	FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	//! Format combinations are not supported by hardware
	FRAMEBUFFER_UNSUPPORTED
};
}


//! Types of shader sources
namespace ShaderType
{
enum TYPE
{
	//! Vertex shader source
	VERTEX,
	//! Geometry shader source
	GEOMETRY,
	//! Fragment (pixel) shader source
	FRAGMENT,
	//! Alias for above
	PIXEL = FRAGMENT
};
}


namespace VertexFormat
{
	enum USAGE
	{
		POSITION,
		NORMAL,
		COLOR,
		TEXT_COORD,
		TEXT_COORD0 = TEXT_COORD,
		TEXT_COORD1,
		TEXT_COORD2,
		TEXT_COORD3,
		TEXT_COORD4,
		TEXT_COORD5,
		TEXT_COORD6,
		TEXT_COORD7,
		TEXT_COORD8,
		TEXT_COORD9,
		TEXT_COORD10,
		TEXT_COORD11,
		TEXT_COORD12,
		TEXT_COORD13,
		TEXT_COORD14,
		TEXT_COORD15,
		TEXT_COORD16,
		TEXT_COORD17,
		TEXT_COORD18,
		TEXT_COORD19,
		TEXT_COORD20,
		TEXT_COORD21,
		TEXT_COORD22,
		TEXT_COORD23,
		TEXT_COORD24,
		TEXT_COORD25,
		TEXT_COORD26,
		TEXT_COORD27,
		TEXT_COORD28,
		TEXT_COORD29,
		TEXT_COORD30,
		TEXT_COORD31,
		UNUSED
	};

	enum TYPE
	{
		FLOAT1,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		DWORD,
		UBYTE4,
		SHORT2,
		SHORT4,
	};
}

}//end of renderer namespace
#endif  // 3DCONSTANTS_H_
