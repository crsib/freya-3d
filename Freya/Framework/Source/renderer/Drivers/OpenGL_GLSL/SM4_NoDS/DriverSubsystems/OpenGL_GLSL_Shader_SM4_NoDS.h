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
namespace opengl_glsl_sm4_nods
{
class	OpenGL_GLSL_Shader : public Shader
{
	friend class OpenGL_GLSL_Driver;
protected:
	OpenGL_GLSL_Shader();
	virtual ~OpenGL_GLSL_Shader();
public:
	virtual void		addShader(unsigned type,const EString& data);

	virtual void		addShaders(const EString& vdata,const EString& fdata);

	virtual void		addShaders(const EString& vdata,const EString& gdata,const EString& fdata);

	virtual void		link();

	virtual void		bind();

	virtual void		unbind();

	virtual bool		isOk() const;

	virtual unsigned		getUniformLocation(const EString& name);

	virtual void			 setUniform(unsigned location,int val);

	virtual void			 setUniform(const EString& name,int val);

	virtual void			 setUniform(unsigned location,float val);

	virtual void			 setUniform(const EString& name,float val);

	virtual void			 setUniform(unsigned location,int val,int val1);

	virtual void			 setUniform(const EString& name,int val,int val1);

	virtual void			 setUniform(unsigned location,float val,float val1);

	virtual void			 setUniform(const EString& name,float val,float val1);

	virtual void			 setUniform(unsigned location,int val,int val1,int val2);

	virtual void			 setUniform(const EString& name,int val,int val1,int val2);

	virtual void			 setUniform(unsigned location,float val,float val1,float val2);

	virtual void			 setUniform(const EString& name,float val,float val1,float val2);

	virtual void			 setUniform(unsigned location,int val,int val1,int val2,int val3);

	virtual void			 setUniform(const EString& name,int val,int val1,int val2,int val3);

	virtual void			 setUniform(unsigned location,float val,float val1,float val2,float val3);

	virtual void			 setUniform(const EString& name,float val,float val1,float val2,float val3);

	virtual void			 setUniform(unsigned location,const math::vector3d& val);

	virtual void			 setUniform(const EString& name,const math::vector3d& val);

	virtual void			 setUniform(unsigned location,const math::matrix4x4& val);

	virtual void			 setUniform(const EString& name,const math::matrix4x4& val);

	virtual void			 setUniform(unsigned location,const math::quaternion& val);

	virtual void			 setUniform(const EString& name,const math::quaternion& val);

	virtual void			 setUniform(unsigned location,const math::vector3d& val,float val1);

	virtual void			 setUniform(const EString& name,const math::vector3d& val,float val2);

	virtual void			 setUniform(unsigned location,const math::matrix3x3& val);

	virtual void			 setUniform(const EString& name,const math::matrix3x3& val);

	virtual unsigned		getAttributeLocation(const EString& name);

	virtual void			 setAttribute(unsigned location,int val);

	virtual void			 setAttribute(const EString& name,int val);

	virtual void			 setAttribute(unsigned location,float val);

	virtual void			 setAttribute(const EString& name,float val);

	virtual void			 setAttribute(unsigned location,int val,int val1);

	virtual void			 setAttribute(const EString& name,int val,int val1);

	virtual void			 setAttribute(unsigned location,float val,float val1);

	virtual void			 setAttribute(const EString& name,float val,float val1);

	virtual void			 setAttribute(unsigned location,int val,int val1,int val2);

	virtual void			 setAttribute(const EString& name,int val,int val1,int val2);

	virtual void			 setAttribute(unsigned location,float val,float val1,float val2);

	virtual void			 setAttribute(const EString& name,float val,float val1,float val2);

	virtual void			 setAttribute(unsigned location,int val,int val1,int val2,int val3);

	virtual void			 setAttribute(const EString& name,int val,int val1,int val2,int val3);

	virtual void			 setAttribute(unsigned location,float val,float val1,float val2,float val3);

	virtual void			 setAttribute(const EString& name,float val,float val1,float val2,float val3);

	virtual void			 setAttribute(unsigned location,const math::vector3d& val);

	virtual void			 setAttribute(const EString& name,const math::vector3d& val);

	virtual void			 setAttribute(unsigned location,const math::quaternion& val);

	virtual void			 setAttribute(const EString& name,const math::quaternion& val);

	virtual void			 setAttribute(unsigned location,const math::vector3d& val,float val1);

	virtual void			 setAttribute(const EString& name,const math::vector3d& val,float val2);

	virtual void 		 	 setAttributeArrayPointer(unsigned location,unsigned dataType,unsigned numComponents, unsigned normalized, size_t stride,VertexBufferObject* obj);

	virtual void 	 		 setAttributeArrayPointer(const EString& name,unsigned dataType,unsigned numComponents, unsigned normalized, size_t stride,VertexBufferObject* obj);

	virtual void			 enableClientState(unsigned location);

	virtual void			 enableClientState(const EString& name);

	virtual void			 disableClientState(unsigned location);

	virtual void			 disableClientState(const EString& name);

	virtual void			 setGeometryShader(unsigned maxOutVerts,unsigned inType,unsigned outType);

	virtual void		 	 setTexture(unsigned location,Texture* tex);

	virtual void			 setTexture(const EString& name,Texture* tex);

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
