/*
 * Shader.h
 *
 *  Created on: 07.09.2008
 *      Author: vedenko
 */

#ifndef SHADER_H_
#define SHADER_H_

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
#include "core/EngineSubsystem.h"
#include "core/EString.h"

#include "math/math.hpp"

#include "renderer/3DConstants.h"

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
	virtual void addShader(renderer::ShaderType::type type,const EString& data) = 0;//adds a compiled from data source shader of type {type} (described by ShaderType namespace)
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


	//Geometry shader
	//! Set geometry shader parameter
	/*!
	 * Sets geometry shader parameters
	 *\param maxOutVerts is a maximum number of vertices to be emitted
	 *\param inType is a type of input primitive described by Primitive
	 *\param outType is a type of output primitive described by Primitive
	 */
	virtual void	 setGeometryShader(unsigned maxOutVerts,renderer::Primitive::type inType,renderer::Primitive::type outType) = 0;//inType and outType are decribed by Primitives namespace

	//Samplers (are uniforms)
	//! Set the texture to shader
	/*!
	 * Sets the texture to shader
	 * \param location is an ID of sampler parameter
	 * \param tex is sampler id.
	 */
	virtual void	 setTexture(unsigned location,renderer::TextureUnit::type unit) = 0;
	//! Set the texture to shader (overloaded version)
	/*!
	 * Sets the texture to shader
	 * \param name is name string of sampler parameter
	 * \param tex is pointer to Texture object
	 */
	virtual void 	 setTexture(const EString& name,renderer::TextureUnit::type unit) = 0;
};

}

#endif /* SHADER_H_ */
