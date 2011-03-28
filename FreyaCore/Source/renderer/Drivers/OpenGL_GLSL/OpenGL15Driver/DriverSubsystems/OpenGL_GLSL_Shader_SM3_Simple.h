/*This header was generated from Shader.h for Freya engine */
#ifndef OPENGL_GLSL_SHADER_H
#define OPENGL_GLSL_SHADER_H

#include "renderer/DriverSubsystems/Shader.h"

#include "core/memory/MemoryAllocator.h"
#include "core/EString.h"
#include <vector>
#include <map>
extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}
#include "renderer/DriverSubsystems/Texture.h"
namespace renderer
{
namespace drivers
{
namespace opengl_glsl_15
{
class	OpenGL_GLSL_Shader : public Shader
{
	friend class OpenGL_GLSL_Driver;
protected:
	OpenGL_GLSL_Shader();
	virtual ~OpenGL_GLSL_Shader();
public:
	//Attaches (and compiles)
	//! Add one shader source to shader
	/*!
	 * Compiles and adds a one shader source to shader object. Shader linkage is not done.
	 * \param type is a type of shader source to be added (described by ShaderType)
	 * \param data is a string, containing shader source
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShader(renderer::ShaderType::type type,const EString& data);//adds a compiled from data source shader of type {type} (described by ShaderType namespace)
	//! Add sources for vertex and fragment (pixel) shader
	/*!
	 * Compiles and adds source for both vertex and fragment (pixel) shaders. Linkage is not done.
	 * \param vdata contains source for vertex shader
	 * \param fdata contains source for fragment (pixel) shader
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShaders(const EString& vdata,const EString& fdata);//adds both vertex and fragment shader
	//! Add sources for vertex, geometry fragment (pixel) shader
	/*!
	 * Compiles and adds source for vertex, geometry(if supported by hardware) and fragment (pixel) shaders. Linkage is not done.
	 * \param vdata contains source for vertex shader
	 * \param gdata contains source for geometry shader
	 * \param fdata contains source for fragment (pixel) shader
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void addShaders(const EString& vdata,const EString& gdata,const EString& fdata);//Adds all three shaders
	//Link attached shader
	//! Link compiled shader sources into shader object
	/*!
	 * Link previously compiled shader sources of various types into one shader object
	 * \throw ShaderException on any error occurred (detailed description is written to log)
	 */
	virtual void link(); //Links shaders
	//Binding
	//! Bind shader to rendering pipeline
	/*
	 * Binds a linked shader to rendering pipeline
	 */
	virtual void bind();
	//! Un bind shader from rendering pipeline
	/*!
	 * Returns pipeline to fixed functionality state
	 */
	virtual void unbind();
	//Checks shader status
	//! Check shader status
	/*!
	 * Checks current shader status
	 * \return true if shader is correctly linked, false otherwise
	 */
	virtual bool isOk() const;//Returns true, if all stages passed successfully
	//Uniform/attribute settings
	//Uniform
	//! Retrieve uniform parameter location by its name
	/*!
	 * Retrieves uniform parameter location by its name
	 * \param name is a name of uniform location
	 * \return API depended uniform ID
	 */
	virtual unsigned getUniformLocation(const EString& name);

		virtual void 	 setUniform(unsigned location,int val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,int val);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,float val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,float val);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,int val,int val1);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,int val,int val1);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,float val,float val1);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,float val,float val1);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,int val,int val1,int val2);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,int val,int val1,int val2);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,float val,float val1,float val2);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,float val,float val1,float val2);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,int val,int val1,int val2,int val3);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,int val,int val1,int val2,int val3);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,float val,float val1,float val2,float val3);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,float val,float val1,float val2,float val3);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,const math::vector3d& val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,const math::vector3d& val);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,const math::matrix4x4& val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,const math::matrix4x4& val);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,const math::quaternion& val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,const math::quaternion& val);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,const math::vector3d& val,float val1);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,const math::vector3d& val,float val2);//!< An overloaded version of setUniform

		virtual void 	 setUniform(unsigned location,const math::matrix3x3& val);//!< An overloaded version of setUniform
		virtual void 	 setUniform(const EString& name,const math::matrix3x3& val);//!< An overloaded version of setUniform

		//attributes
		//! Retrieve attribute parameter location by its name
		/*!
		 * Retrieves attribute parameter location by its name
		 * \param name is a name of attribute location
		 * \return API depended attribute ID
		 */
		virtual unsigned getAttributeLocation(const EString& name);

		virtual void 	 setAttribute(unsigned location,int val);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,int val);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,float val);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,float val);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,int val,int val1);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,int val,int val1);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,float val,float val1);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,float val,float val1);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,int val,int val1,int val2);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,int val,int val1,int val2);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,float val,float val1,float val2);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,float val,float val1,float val2);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,int val,int val1,int val2,int val3);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,int val,int val1,int val2,int val3);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,float val,float val1,float val2,float val3);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,float val,float val1,float val2,float val3);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,const math::vector3d& val);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,const math::vector3d& val);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,const math::quaternion& val);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,const math::quaternion& val);//!< An overloaded version of setAttribute

		virtual void 	 setAttribute(unsigned location,const math::vector3d& val,float val1);//!< An overloaded version of setAttribute
		virtual void 	 setAttribute(const EString& name,const math::vector3d& val,float val2);//!< An overloaded version of setAttribute


	//Geometry shader
	//! Set geometry shader parameter
	/*!
	 * Sets geometry shader parameters
	 *\param maxOutVerts is a maximum number of vertices to be emitted
	 *\param inType is a type of input primitive described by Primitive
	 *\param outType is a type of output primitive described by Primitive
	 */
	virtual void	 setGeometryShader(unsigned maxOutVerts,renderer::Primitive::type inType,renderer::Primitive::type outType);//inType and outType are decribed by Primitives namespace

	//Samplers (are uniforms)
	//! Set the texture to shader
	/*!
	 * Sets the texture to shader
	 * \param location is an ID of sampler parameter
	 * \param tex is pointer to Texture object
	 */
	virtual void	 setTexture(unsigned location,renderer::TextureUnit::type unit);
	//! Set the texture to shader (overloaded version)
	/*!
	 * Sets the texture to shader
	 * \param name is name string of sampler parameter
	 * \param tex is pointer to Texture object
	 */
	virtual void 	 setTexture(const EString& name,renderer::TextureUnit::type unit);

private:

	GLhandleARB				m_ShaderObject;

	typedef std::vector<GLhandleARB,core::memory::MemoryAllocator<GLhandleARB> > ShaderList;
	typedef std::map<EString,int,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,int> > > LocationMap;
	typedef std::map<EString,int,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,int> > >::iterator LocationMapIterator;

	ShaderList				m_ShaderList;
	LocationMap				m_UniformMap;
	LocationMap				m_AttributeMap;

	unsigned				m_Linked;
	unsigned				m_Bounded;
};
}
}
}
#endif /* OPENGL_GLSL_SHADER_H */
