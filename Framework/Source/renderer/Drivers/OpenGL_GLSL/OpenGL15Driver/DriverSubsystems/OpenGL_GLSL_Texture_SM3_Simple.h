/*This header was generated from Texture.h for Freya engine */
#ifndef OPENGL_GLSL_TEXTURE_H
#define OPENGL_GLSL_TEXTURE_H

#include "renderer/DriverSubsystems/Texture.h"
#include "core/memory/MemoryAllocator.h"
#include <map>
#include "core/PluginCore.h"
#include "renderer/DriverException.h"
#include "renderer/RenderingAPIDriver.h"
extern "C"
{
#include "renderer/Drivers/OpenGL_GLSL/GLEW/glew.h"
}

#include "renderer/DriverSubsystems/VertexBufferObject.h"

namespace renderer
{
namespace drivers
{
namespace opengl_glsl_15
{
class	OpenGL_GLSL_Texture : public Texture
{
	friend class OpenGL_GLSL_Driver;
	friend class OpenGL_GLSL_Framebuffer;
protected:
	OpenGL_GLSL_Texture();
	virtual ~OpenGL_GLSL_Texture();
public:
	virtual void		loadTexture(renderer::TextureType::type textureType,unsigned level,renderer::TextureInternalFormat::type textureInternalFormat,renderer::TextureFormat::type textureStorageFormat,renderer::TextureStorage::type textureStorage,unsigned width,unsigned height,void* data);

	virtual void		loadTexture(renderer::TextureType::type textureType,unsigned level,renderer::TextureInternalFormat::type textureInternalFormat,renderer::TextureFormat::type textureStorageFormat,renderer::TextureStorage::type textureStorage,unsigned width,unsigned height,unsigned side_or_depth,void* data);

	virtual renderer::TextureType::type		getTextureType() const;

	virtual renderer::TextureUnit::type		getTextureUnit() const;

	virtual void*		map(unsigned level = 0,unsigned side = 0);

	virtual void		 unmap(unsigned level = 0,unsigned side = 0);

	virtual void		 setUnit(renderer::TextureUnit::type unit);

	virtual void		 bind();

	virtual void		 bind(renderer::TextureUnit::type unit);

	virtual void		 unbind();

	virtual void		 setMinFilter(renderer::TextureFiltering::type filter);

	virtual void		 setMagFilter(renderer::TextureFiltering::type filter);

	virtual void		 setAnisotropy(float val);

	virtual void		 generateMipMaps();

	virtual void		   clampS(renderer::TextureClamping::type clamp);

	virtual void		   clampT(renderer::TextureClamping::type clamp);

	virtual void		   clampR(renderer::TextureClamping::type clamp);

	virtual void		   clampQ(renderer::TextureClamping::type clamp);
private:
	GLuint					m_Texture;

	TextureUnit::type				m_DefaultUnit;
	TextureUnit::type				m_BoundedUnit;

	unsigned				m_Target; //OpenGL
	TextureType::type		m_InternalTarget;

	unsigned				m_Bounded;

	unsigned				m_SourceStorage; //INTERNAL OPENGL FORMAT
	unsigned				m_SourceFormat; //INTERNAL OPENGL FORMAT
	unsigned				m_IsCompressed;

	class VBOWrap : public EngineSubsystem
	{
	public:
		VBOWrap()
		:m_VBO(NULL)
		{
		}

		VBOWrap(renderer::VertexBufferObject *o)
		:m_VBO(o)
		{
		}

		VBOWrap(const VBOWrap & o)
		:m_VBO(o.m_VBO)
		{
			m_Width = o.m_Width;
			m_Height = o.m_Height;
			m_Depth = o.m_Depth;
			m_ComponentSize=o.m_ComponentSize;
		}

		VBOWrap & operator =(const VBOWrap & o)
		{
			m_VBO = o.m_VBO;
			m_Width = o.m_Width;
			m_Height = o.m_Height;
			m_Depth = o.m_Depth;
			m_ComponentSize=o.m_ComponentSize;
			return *this;
		}

		VBOWrap & operator =(renderer::VertexBufferObject *o)
		{
			m_VBO = o;
			return *this;
		}
		~VBOWrap()
		{
			if(m_VBO)
				core::CoreInstance->getRenderingDriver()->destroyVertexBufferObject(m_VBO);
		}
		operator renderer::VertexBufferObject*()
		{
			return m_VBO;
		}

		operator renderer::VertexBufferObject*() const
		{
			return m_VBO;
		}

		operator const renderer::VertexBufferObject*() const
		{
			return m_VBO;
		}

		renderer::VertexBufferObject *operator ->()
		{
			return m_VBO;
		}

	private:
		renderer::VertexBufferObject *m_VBO;
		unsigned m_Width;
		unsigned m_Height;
		unsigned m_ComponentSize;
		unsigned m_Depth;
	public:
		renderer::VertexBufferObject *getVBO() const
		{
			return m_VBO;
		}

		void setVBO(renderer::VertexBufferObject *m_VBO)
		{
			this->m_VBO = m_VBO;
		}

		unsigned getWidth() const
		{
			return m_Width;
		}

		void setWidth(unsigned  m_Width)
		{
			this->m_Width = m_Width;
		}

		unsigned getHeight() const
		{
			return m_Height;
		}

		void setHeight(unsigned  m_Height)
		{
			this->m_Height = m_Height;
		}

		unsigned getComponentSize() const
		{
			return m_ComponentSize;
		}

		void setComponentSize(unsigned  m_ComponentSize)
		{
			this->m_ComponentSize = m_ComponentSize;
		}

		unsigned getDepth() const
		{
			return m_Depth;
		}

		void setDepth(unsigned depth)
		{
			m_Depth = depth;
		}

	};

	std::pair<unsigned,unsigned> make_index(unsigned l,unsigned s)
	{
		return std::make_pair(l,s);
	}
	typedef std::map< std::pair<unsigned,unsigned>, VBOWrap , std::less<std::pair<unsigned,unsigned> >, core::memory::MemoryAllocator<std::pair<const std::pair<unsigned,unsigned>, VBOWrap> > > TextureVBOType; //OMFG, what a type
	TextureVBOType			m_VBO;
};
}
}
}
#endif /* OPENGL_GLSL_TEXTURE_H */
