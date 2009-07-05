/*
 * Shader.h
 *
 *  Created on: 07.09.2008
 *      Author: vedenko
 */

#ifndef SHADER_H_
#define SHADER_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "core/EString.h"

namespace math
{
class vector3d;
class matrix4x4;
class matrix3x3;
class quaternion;
}

namespace renderer
{
class VertexBufferObject;
class Texture;
//! Shader abstraction
/*!
 * This class provides an API independent abstraction of shader concept
 * Instance of this class can only be created by RenderingAPIDriver
 * The main idea of this abstraction is to provide API independent way for loading, binding and setting the shader parameters.
 * Currently, there are two main types of shader parameters - uniform, which is constant among all time the shader is bound,
 * and attribute, that can possibly change from vertex to vertex. A location of the parameter can be determined either by name, either by some unsigned (and API dependent) ID
 * There are various overloaded versions of Shader::setUniform and Shader::setAttribute. They are divided into to groups: setting value by name and by ID.
 * They will be documented only briefly.
 */
class Shader: virtual public ::EngineSubsystem
{
public:
	//Attaches (and compiles)
	//! Add one shader source to shader
	/*!
	 * Compiles and adds a one shader source to shader object. Shader linkage is not done.
	 * \param type is a type of shader source to be added (described by ShaderType)
	 * \param data is a string, containing shader source
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShader(unsigned type,const EString& data) = 0;//adds a compiled from data source shader of type {type} (described by ShaderType namespace)
	//! Add sources for vertex and fragment (pixel) shader
	/*!
	 * Compiles and adds source for both vertex and fragment (pixel) shaders. Linkage is not done.
	 * \param vdata contains source for vertex shader
	 * \param fdata contains source for fragment (pixel) shader
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShaders(const EString& vdata,const EString& fdata) = 0;//adds both vertex and fragment shader
	//! Add sources for vertex, geometry fragment (pixel) shader
	/*!
	 * Compiles and adds source for vertex, geometry(if supported by hardware) and fragment (pixel) shaders. Linkage is not done.
	 * \param vdata contains source for vertex shader
	 * \param gdata contains source for geometry shader
	 * \param fdata contains source for fragment (pixel) shader
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShaders(const EString& vdata,const EString& gdata,const EString& fdata) = 0;//Adds all three shaders
	//Link attached shader
	//! Link compiled shader sources into shader object
	/*!
	 * Link previously compiled shader sources of various types into one shader object
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void link() = 0; //Links shaders
	//Binding
	//! Bind shader to rendering pipeline
	/*
	 * Binds a linked shader to rendering pipeline
	 */
	virtual void bind() = 0;
	//! Un bind shader from rendering pipeline
	/*!
	 * Returns pipeline to fixed functionality state
	 */
	virtual void unbind() = 0;
	//Checks shader status
	//! Check shader status
	/*!
	 * Checks current shader status
	 * \return true if shader is correctly linked, false otherwise
	 */
	virtual bool isOk() const = 0;//Returns true, if all stages passed successfully
	//Uniform/attribute settings
	//Uniform
	//! Retrieve uniform parameter location by its name
	/*!
	 * Retrieves uniform parameter location by its name
	 * \param name is a name of uniform location
	 * \return API depended uniform ID
	 */
	virtual unsigned getUniformLocation(const EString& name) = 0;

	virtual void 	 setUniform(unsigned location,int val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,int val) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,float val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,float val) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,int val,int val1) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,int val,int val1) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,float val,float val1) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,float val,float val1) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,int val,int val1,int val2) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,int val,int val1,int val2) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,float val,float val1,float val2) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,float val,float val1,float val2) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,int val,int val1,int val2,int val3) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,int val,int val1,int val2,int val3) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,float val,float val1,float val2,float val3) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,float val,float val1,float val2,float val3) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,const math::vector3d& val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,const math::vector3d& val) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,const math::matrix4x4& val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,const math::matrix4x4& val) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,const math::quaternion& val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,const math::quaternion& val) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,const math::vector3d& val,float val1) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,const math::vector3d& val,float val2) = 0;//!< An overloaded version of setUniform

	virtual void 	 setUniform(unsigned location,const math::matrix3x3& val) = 0;//!< An overloaded version of setUniform
	virtual void 	 setUniform(const EString& name,const math::matrix3x3& val) = 0;//!< An overloaded version of setUniform

	//attributes
	//! Retrieve attribute parameter location by its name
	/*!
	 * Retrieves attribute parameter location by its name
	 * \param name is a name of attribute location
	 * \return API depended attribute ID
	 */
	virtual unsigned getAttributeLocation(const EString& name) = 0;

	virtual void 	 setAttribute(unsigned location,int val) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,int val) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,float val) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,float val) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,int val,int val1) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,int val,int val1) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,float val,float val1) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,float val,float val1) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,int val,int val1,int val2) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,int val,int val1,int val2) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,float val,float val1,float val2) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,float val,float val1,float val2) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,int val,int val1,int val2,int val3) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,int val,int val1,int val2,int val3) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,float val,float val1,float val2,float val3) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,float val,float val1,float val2,float val3) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,const math::vector3d& val) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,const math::vector3d& val) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,const math::quaternion& val) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,const math::quaternion& val) = 0;//!< An overloaded version of setAttribute

	virtual void 	 setAttribute(unsigned location,const math::vector3d& val,float val1) = 0;//!< An overloaded version of setAttribute
	virtual void 	 setAttribute(const EString& name,const math::vector3d& val,float val2) = 0;//!< An overloaded version of setAttribute

	//! Set the pointer to attribute array
	/*!
	 * Set the pointer for attributes array to be used as data source inside shader. This pointer is set in per shader basis (and preferably each time shader is bound to the context to eliminate
	 * API specific behavior). This pointer can be used with various DrawPrimitive/DrawIndexedPrimitive commands.
	 * \param location is API specific id of vertex attribute to set
	 * \param dataType is type of data,representing attributes. Described by DataType
	 * \param numComponents is a number of components associated with one vertex. Could be from 1 to 4
	 * \param normalized specifies whether fixed-point data values should be normalized (1) or converted directly as fixed-point values (0) when they are accessed
	 * \param stride is an offset in bytes between each vertex attribute data
	 * \param obj is a VBO, that holds attribute data
	 */
	virtual void 	 setAttributeArrayPointer(unsigned location,unsigned dataType,unsigned numComponents, unsigned normalized, size_t stride,VertexBufferObject* obj) = 0;
	//! Set the pointer to attribute array (overloaded version)
	/*!
	 * Set the pointer for attributes array to be used as data source inside shader. This pointer is set in per shader basis (and preferably each time shader is bound to the context to eliminate
	 * API specific behavior). This pointer can be used with various DrawPrimitive/DrawIndexedPrimitive commands.
	 * \param name is name of attribute location
	 * \param dataType is type of data,representing attributes. Described by DataType
	 * \param numComponents is a number of components associated with one vertex. Could be from 1 to 4
	 * \param normalized specifies whether fixed-point data values should be normalized (1) or converted directly as fixed-point values (0) when they are accessed
	 * \param stride is an offset in bytes between each vertex attribute data
	 * \param obj is a VBO, that holds attribute data
	 */
	virtual void 	 setAttributeArrayPointer(const EString& name,unsigned dataType,unsigned numComponents, unsigned normalized, size_t stride,VertexBufferObject* obj) = 0;
	//! Enable attribute array client state (to make it valid for DP/DIP)
	/*!
	 * Set client state for using attribute arrays on location specified
	 * \param location is API specific id of vertex attribute to use attribute array as data source
	 */
	virtual void	enableClientState(unsigned location) = 0;
	//! Enable attribute array client state (to make it valid for DP/DIP) (overloaded version)
	/*!
	 * Set client state for using attribute arrays on location specified
	 * \param name is name of vertex attribute to use attribute array as data source
	 */
	virtual void	enableClientState(const EString& name) = 0;
	//! Disable attribute array client state
	/*!
	 * Disable using attribute arrays as data source on specified attribute
	 * \param location is API specific id of vertex attribute
	 */
	virtual void	disableClientState(unsigned location) = 0;
	//! Disable attribute array client state (overloaded version)
	/*!
	 * Disable using attribute arrays as data source on specified attribute
	 * \param name is name of vertex attribute
	 */
	virtual void	disableClientState(const EString& name) = 0;
	//Geometry shader
	//! Set geometry shader parameter
	/*!
	 * Sets geometry shader parameters
	 *\param maxOutVerts is a maximum number of vertices to be emitted
	 *\param inType is a type of input primitive described by Primitive
	 *\param outType is a type of output primitive described by Primitive
	 */
	virtual void	 setGeometryShader(unsigned maxOutVerts,unsigned inType,unsigned outType) = 0;//inType and outType are decribed by Primitives namespace

	//Samplers (are uniforms)
	//! Set the texture to shader
	/*!
	 * Sets the texture to shader
	 * \param location is an ID of sampler parameter
	 * \param tex is pointer to Texture object
	 */
	virtual void	 setTexture(unsigned location,Texture* tex) = 0;
	//! Set the texture to shader (overloaded version)
	/*!
	 * Sets the texture to shader
	 * \param name is name string of sampler parameter
	 * \param tex is pointer to Texture object
	 */
	virtual void 	 setTexture(const EString& name,Texture* tex) = 0;
};

}

#endif /* SHADER_H_ */
