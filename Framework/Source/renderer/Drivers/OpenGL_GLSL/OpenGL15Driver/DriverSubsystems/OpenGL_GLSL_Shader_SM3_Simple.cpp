/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Shader_SM3_Simple.h"
#include "renderer/3DConstants.h"
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/OpenGL_15_ConstantsTables.h"
#include "renderer/DriverSubsystems/ShaderException.h"
#include "renderer/DriverSubsystems/VertexBufferObject.h"
#include <iostream>

using std::clog;
using std::endl;

#include "math/math.hpp"
#include "math/quaternion.hpp"
#include "math/vector3d.hpp"
#include "math/matrix3x3.hpp"
#include "math/matrix4x4.hpp"

namespace renderer
{
namespace drivers
{
namespace opengl_glsl_15
{
OpenGL_GLSL_Shader::OpenGL_GLSL_Shader()
{
	m_ShaderObject = glCreateProgramObjectARB();
	m_Bounded = 0;
	m_Linked = 0;
}

OpenGL_GLSL_Shader::~OpenGL_GLSL_Shader()
{
	glDeleteObjectARB(m_ShaderObject);
	for(unsigned i = 0; i < m_ShaderList.size(); i++)
		glDeleteObjectARB(m_ShaderList[i]);
	m_UniformMap.clear();
	m_AttributeMap.clear();
	m_ShaderList.clear();
}

void		OpenGL_GLSL_Shader::addShader(renderer::ShaderType::type type,const EString& data)
{
	GLhandleARB		shader;
	//Create a correct object to hold our shader
	switch(type)
	{
	case ShaderType::VERTEX:
		shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		break;
	case ShaderType::GEOMETRY:
		throw renderer::ShaderException();
		break;
	case ShaderType::FRAGMENT:
		shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		break;
	}
	if(shader == 0) return;

	GLcharARB*	source =  static_cast<GLcharARB*>(const_cast<char*>(data.c_str()));
	GLint		length = data.length();

	GLint err,compileStatus;
	//Now, load and try to compile that f******g shader
	glShaderSourceARB(shader,1,const_cast<const GLcharARB**>(&source),&length);
	glCompileShaderARB(shader);

	err = glGetError();
	if(err != GL_NO_ERROR) //Ecks, seems to be internal OpnGL error
	{
		clog << "Internal OpenGL error: " << gluErrorString(err) << endl;
		throw renderer::ShaderException(type);
	}

	glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);

	if(compileStatus == 0) //Whoa, this shader is not compiled. Ats a good idea to generate exception )))
	{
		GLint       logLength     = 0;
		GLsizei     charsWritten  = 0;
		glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
		if((glGetError() == GL_NO_ERROR)&&(logLength > 0))//GL has something to say
		{
			GLcharARB*  log = static_cast<GLcharARB*>(core::memory::Allocate(logLength,core::memory::GENERIC_POOL));
			glGetInfoLogARB (shader, logLength, &charsWritten, log); //Get shader log.
			clog << "Shader compilation failed: " << log << endl;
			core::memory::Free(log,core::memory::GENERIC_POOL);
			throw renderer::ShaderException(type);;
		}
	}
	//Yeah, shader is compiled
	glAttachObjectARB(m_ShaderObject,shader);
	m_ShaderList.push_back(shader);
	//Linkage needed
	m_Linked = 0;
}

void		OpenGL_GLSL_Shader::addShaders(const EString& vdata,const EString& fdata)
{
	//Ok, now, lets call previos code twice.
	try
	{
		addShader(ShaderType::VERTEX,vdata);
		addShader(ShaderType::FRAGMENT,fdata);
	}
	catch(renderer::ShaderException& exception)
	{
		clog << "Failed to add shaders " << exception.message() << endl;
		throw;
	}
}

void		OpenGL_GLSL_Shader::addShaders(const EString& vdata,const EString& gdata,const EString& fdata)
{
	//And again, but three times now
	try
	{
		addShader(ShaderType::VERTEX,vdata);
		addShader(ShaderType::GEOMETRY,gdata);
		addShader(ShaderType::FRAGMENT,fdata);
	}
	catch(renderer::ShaderException& exception)
	{
		clog << "Failed to add shaders " << exception.message() << endl;
		throw;
	}
}

void		OpenGL_GLSL_Shader::link()
{
	//Finaly,let's link it
	GLint   linked;
	glLinkProgramARB(m_ShaderObject);
	GLint err;
	err = glGetError();
	if(err != GL_NO_ERROR) //Ecks, seems to be internal OpnGL error
	{
		clog << "Internal OpenGL error: " << gluErrorString(err) << endl;
		throw renderer::ShaderException();
	}

	glGetObjectParameterivARB(m_ShaderObject, GL_OBJECT_LINK_STATUS_ARB, &linked);

	if(linked == 0)
	{
		GLint       logLength     = 0;
		GLsizei     charsWritten  = 0;
		glGetObjectParameterivARB(m_ShaderObject, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
		if((glGetError() == GL_NO_ERROR)&&(logLength > 0))//GL has something to say
		{
			GLcharARB*  log = static_cast<GLcharARB*>(core::memory::Allocate(logLength,core::memory::GENERIC_POOL));
			glGetInfoLogARB (m_ShaderObject, logLength, &charsWritten, log); //Get shader log.
			clog << "Shader linkage failed: " << log << endl;
			core::memory::Free(log,core::memory::GENERIC_POOL);
			throw renderer::ShaderException();
		}
	}

	//Everything is ok
	m_Linked = true;

}

void		OpenGL_GLSL_Shader::bind()
{
	glUseProgramObjectARB(m_ShaderObject);
	m_Bounded = true;
}

void		OpenGL_GLSL_Shader::unbind()
{
	if(m_Bounded)
	{
		glUseProgramObjectARB(0);
		m_Bounded = false;
	}
}

bool		OpenGL_GLSL_Shader::isOk() const
{
	return m_Linked != 0;
}

unsigned		OpenGL_GLSL_Shader::getUniformLocation(const EString& name)
{
	LocationMapIterator	it = m_UniformMap.find(name);
	if(it == m_UniformMap.end())
	{
		int loc;
		loc = glGetUniformLocationARB(m_ShaderObject,name.c_str());

		if(loc < 0)
			throw  renderer::ShaderException();
		m_UniformMap[name] = static_cast<unsigned>(loc);
		it = m_UniformMap.find(name);
	}
	return it->second;
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,int val)
{
	if(m_Bounded)
	{
		glUniform1iARB(location,val);
	}
	else
	{
		bind();
		glUniform1iARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,int val)
{
	setUniform(getUniformLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,float val)
{
	if(m_Bounded)
	{
		glUniform1fARB(location,val);
	}
	else
	{
		bind();
		glUniform1fARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,float val)
{
	setUniform(getUniformLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,int val,int val1)
{
	if(m_Bounded)
	{
		glUniform2iARB(location,val,val1);
	}
	else
	{
		bind();
		glUniform2iARB(location,val,val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,int val,int val1)
{
	setUniform(getUniformLocation(name),val,val1);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,float val,float val1)
{
	if(m_Bounded)
	{
		glUniform2fARB(location,val,val1);
	}
	else
	{
		bind();
		glUniform2fARB(location,val,val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,float val,float val1)
{
	setUniform(getUniformLocation(name),val,val1);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,int val,int val1,int val2)
{
	if(m_Bounded)
	{
		glUniform3iARB(location,val,val1,val2);
	}
	else
	{
		bind();
		glUniform3iARB(location,val,val1,val2);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,int val,int val1,int val2)
{
	setUniform(getUniformLocation(name),val,val1,val2);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,float val,float val1,float val2)
{
	if(m_Bounded)
	{
		glUniform3fARB(location,val,val1,val2);
	}
	else
	{
		bind();
		glUniform3fARB(location,val,val1,val2);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,float val,float val1,float val2)
{
	setUniform(getUniformLocation(name),val,val1,val2);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,int val,int val1,int val2,int val3)
{
	if(m_Bounded)
	{
		glUniform4iARB(location,val,val1,val2,val3);
	}
	else
	{
		bind();
		glUniform4iARB(location,val,val1,val2,val3);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,int val,int val1,int val2,int val3)
{
	setUniform(getUniformLocation(name),val,val1,val2,val3);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,float val,float val1,float val2,float val3)
{
	if(m_Bounded)
	{
		glUniform4fARB(location,val,val1,val2,val3);
	}
	else
	{
		bind();
		glUniform4fARB(location,val,val1,val2,val3);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,float val,float val1,float val2,float val3)
{
	setUniform(getUniformLocation(name),val,val1,val2,val3);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,const math::vector3d& val)
{
	if(m_Bounded)
	{
		glUniform3fvARB(location,1,val);
	}
	else
	{
		bind();
		glUniform3fvARB(location,1,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,const math::vector3d& val)
{
	setUniform(getUniformLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,const math::matrix4x4& val)
{
	if(m_Bounded)
	{
		glUniformMatrix4fvARB(location,1,true,val);
	}
	else
	{
		bind();
		glUniformMatrix4fvARB(location,1,true,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,const math::matrix4x4& val)
{
	setUniform(getUniformLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,const math::quaternion& val)
{
	if(m_Bounded)
	{
		glUniform4fvARB(location,1,val);
	}
	else
	{
		bind();
		glUniform4fvARB(location,1,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,const math::quaternion& val)
{
	setUniform(getUniformLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,const math::vector3d& val,float val1)
{
	if(m_Bounded)
	{
		glUniform4fARB(location,val[0],val[1],val[2],val1);
	}
	else
	{
		bind();
		glUniform4fARB(location,val[0],val[1],val[2],val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,const math::vector3d& val,float val2)
{
	setUniform(getUniformLocation(name),val,val2);
}

void		OpenGL_GLSL_Shader::	 setUniform(unsigned location,const math::matrix3x3& val)
{
	float m[3][3] = {val._11,val._12,val._13,
					val._21,val._22,val._23,
					val._31,val._32,val._33};
	if(m_Bounded)
	{
		glUniformMatrix3fvARB(location,1,true,&m[0][0]);
	}
	else
	{
		bind();
		glUniformMatrix3fvARB(location,1,true,&m[0][0]);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setUniform(const EString& name,const math::matrix3x3& val)
{
	setUniform(getUniformLocation(name),val);
}

unsigned		OpenGL_GLSL_Shader::getAttributeLocation(const EString& name)
{
	LocationMapIterator	it = m_AttributeMap.find(name);
	if(it == m_AttributeMap.end())
	{
		int loc;
		loc = glGetAttribLocationARB(m_ShaderObject,name.c_str());
		if(loc < 0)
			throw  renderer::ShaderException();
		m_AttributeMap[name] = static_cast<unsigned>(loc);
		it = m_AttributeMap.find(name);
	}
	return it->second;
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,int val)
{
	if(m_Bounded)
	{
		glVertexAttrib1sARB(location,val);
	}
	else
	{
		bind();
		glVertexAttrib1sARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,int val)
{
	setAttribute(getAttributeLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,float val)
{
	if(m_Bounded)
	{
		glVertexAttrib1fARB(location,val);
	}
	else
	{
		bind();
		glVertexAttrib1fARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,float val)
{
	setAttribute(getAttributeLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,int val,int val1)
{
	if(m_Bounded)
	{
		glVertexAttrib2sARB(location,val,val1);
	}
	else
	{
		bind();
		glVertexAttrib2sARB(location,val,val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,int val,int val1)
{
	setAttribute(getAttributeLocation(name),val,val1);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,float val,float val1)
{
	if(m_Bounded)
	{
		glVertexAttrib2fARB(location,val,val1);
	}
	else
	{
		bind();
		glVertexAttrib2fARB(location,val,val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,float val,float val1)
{
	setAttribute(getAttributeLocation(name),val,val1);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,int val,int val1,int val2)
{
	if(m_Bounded)
	{
		glVertexAttrib3sARB(location,val,val1,val2);
	}
	else
	{
		bind();
		glVertexAttrib3sARB(location,val,val1,val2);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,int val,int val1,int val2)
{
	setAttribute(getAttributeLocation(name),val,val1,val2);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,float val,float val1,float val2)
{
	if(m_Bounded)
	{
		glVertexAttrib3fARB(location,val,val1,val2);
	}
	else
	{
		bind();
		glVertexAttrib3fARB(location,val,val1,val2);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,float val,float val1,float val2)
{
	setAttribute(getAttributeLocation(name),val,val1,val2);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,int val,int val1,int val2,int val3)
{
	if(m_Bounded)
	{
		glVertexAttrib4sARB(location,val,val1,val2,val3);
	}
	else
	{
		bind();
		glVertexAttrib4sARB(location,val,val1,val2,val3);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,int val,int val1,int val2,int val3)
{
	setAttribute(getAttributeLocation(name),val,val1,val2,val3);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,float val,float val1,float val2,float val3)
{
	if(m_Bounded)
	{
		glVertexAttrib4fARB(location,val,val1,val2,val3);
	}
	else
	{
		bind();
		glVertexAttrib4fARB(location,val,val1,val2,val3);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,float val,float val1,float val2,float val3)
{
	setAttribute(getAttributeLocation(name),val,val1,val2,val3);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,const math::vector3d& val)
{
	if(m_Bounded)
	{
		glVertexAttrib3fvARB(location,val);
	}
	else
	{
		bind();
		glVertexAttrib3fvARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,const math::vector3d& val)
{
	setAttribute(getAttributeLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,const math::quaternion& val)
{
	if(m_Bounded)
	{
		glVertexAttrib4fvARB(location,val);
	}
	else
	{
		bind();
		glVertexAttrib4fvARB(location,val);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,const math::quaternion& val)
{
	setAttribute(getAttributeLocation(name),val);
}

void		OpenGL_GLSL_Shader::	 setAttribute(unsigned location,const math::vector3d& val,float val1)
{
	if(m_Bounded)
	{
		glVertexAttrib4fARB(location,val[0],val[1],val[2],val1);
	}
	else
	{
		bind();
		glVertexAttrib4fARB(location,val[0],val[1],val[2],val1);
		unbind();
	}
}

void		OpenGL_GLSL_Shader::	 setAttribute(const EString& name,const math::vector3d& val,float val2)
{
	setAttribute(getAttributeLocation(name),val,val2);
}

void		OpenGL_GLSL_Shader:: setGeometryShader(unsigned maxOutVerts,renderer::Primitive::type inType,renderer::Primitive::type outType)
{
	glProgramParameteriEXT(m_ShaderObject,GL_GEOMETRY_VERTICES_OUT_EXT,maxOutVerts);
	glProgramParameteriEXT(m_ShaderObject,GL_GEOMETRY_INPUT_TYPE_EXT,inType);
	glProgramParameteriEXT(m_ShaderObject,GL_GEOMETRY_OUTPUT_TYPE_EXT,outType);
}

void		OpenGL_GLSL_Shader:: setTexture(unsigned location,renderer::TextureUnit::type unit)
{
	setUniform(location,(int)unit);
}

void		OpenGL_GLSL_Shader::	 setTexture(const EString& name,renderer::TextureUnit::type unit)
{
	setUniform(name,(int)unit);
}

}
}
}
