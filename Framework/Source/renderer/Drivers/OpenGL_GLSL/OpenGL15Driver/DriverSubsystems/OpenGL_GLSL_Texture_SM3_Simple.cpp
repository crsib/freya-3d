/*This file was generated for Freya engine*/
#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/DriverSubsystems/OpenGL_GLSL_Texture_SM3_Simple.h"


#include "renderer/Drivers/OpenGL_GLSL/OpenGL15Driver/OpenGL_15_ConstantsTables.h"


namespace renderer
{
namespace drivers
{
namespace opengl_glsl_15
{
OpenGL_GLSL_Texture::OpenGL_GLSL_Texture()
{
	glGenTextures(1,&m_Texture);
	m_Bounded = false;
	m_DefaultUnit = TextureUnit::TEXTURE0;
	m_IsCompressed = false;
	m_Target = GL_TEXTURE_2D;
}

OpenGL_GLSL_Texture::~OpenGL_GLSL_Texture()
{
	glDeleteTextures(1,&m_Texture);
	//VBO is auto-cleaned
}

void		OpenGL_GLSL_Texture::loadTexture(renderer::TextureType::type TextureType,unsigned level,renderer::TextureInternalFormat::type TextureInternalFormat,renderer::TextureFormat::type TextureStorageFormat,renderer::TextureStorage::type TextureStorage,unsigned width,unsigned height,void* data)
{
	m_Target = OpenGL_GLSL_Tables::TextureType[TextureType];
	m_InternalTarget = TextureType;
	m_SourceStorage  = OpenGL_GLSL_Tables::TextureStorage[TextureStorage];
	m_SourceFormat   = OpenGL_GLSL_Tables::TextureFormat[TextureStorageFormat];
/*
	std::pair<unsigned,unsigned> ind = make_index(level,0);
	{
		m_VBO[ind] = core::CoreInstance->getRenderingDriver()->createVertexBufferObject();
		m_VBO[ind].setWidth(width);
		m_VBO[ind].setHeight(height);
		m_VBO[ind].setComponentSize(OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat]);
		m_VBO[ind]->setTarget(VBOType::TEXTURE);
	}

	*/

	if(TextureInternalFormat < TextureInternalFormat::COMPRESSED) //Uncompressed texture
	{
		//m_VBO[ind]->bind();
		//m_VBO[ind]->setData(VBOUsage::STATIC_DRAW,width*height*OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat],data);
		glBindTexture(m_Target,m_Texture);
		glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
		switch(TextureType)
		{
		case TextureType::TEXTURE_1D:
			glTexImage1D(m_Target,level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,0,m_SourceFormat,m_SourceStorage,data);
			break;
		case TextureType::TEXTURE_2D:
		case TextureType::TEXTURE_RECTANGLE:
			glTexImage2D(m_Target,level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,height,0,m_SourceFormat,m_SourceStorage,data);
			break;
		default: throw renderer::DriverException("Invalid texture type");
		}
		//m_VBO[ind]->unbind();
		glBindTexture(m_Target,0);
	}
	else //Compressed texture mode
	{
		m_IsCompressed = true;
		//Compression is only available for 2D textures (and cube maps, but this case is not capable of creating cube maps).
		if(TextureType != TextureType::TEXTURE_2D) throw renderer::DriverException("Invalid texture type"); //No, no, no way
		if((width < 4) || (height < 4) ) throw renderer::DriverException("Invalid texture size");//Not enough is not enough ))
		//m_VBO[ind]->bind();
		unsigned block_size;
		//chose size
		switch(TextureInternalFormat)
		{
		case TextureInternalFormat::RGB_DXT1:
		case TextureInternalFormat::RGBA_DXT1:
			block_size = 8;
			break;
		default:
			block_size = 16;
		}
		//m_VBO[ind]->setData(VBOUsage::STATIC_DRAW,width*height*block_size/16,data);

		glBindTexture(m_Target,m_Texture);
		glCompressedTexImage2DARB(m_Target,level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,height,0,block_size*width*height/16,data);
		glBindTexture(m_Target,0);
		//m_VBO[ind]->unbind();
	}
	//Free VBO
	//core::CoreInstance->getRenderingDriver()->destroyVertexBufferObject(m_VBO[ind]);
	//m_VBO[ind].setVBO(NULL);
}


void		OpenGL_GLSL_Texture::loadTexture(renderer::TextureType::type TextureType,unsigned level,renderer::TextureInternalFormat::type TextureInternalFormat,renderer::TextureFormat::type TextureStorageFormat,renderer::TextureStorage::type TextureStorage,unsigned width,unsigned height,unsigned side_or_depth,void* data)
{
	m_SourceStorage  = OpenGL_GLSL_Tables::TextureStorage[TextureStorage];
	m_SourceFormat   = OpenGL_GLSL_Tables::TextureFormat[TextureStorageFormat];
	m_Target = OpenGL_GLSL_Tables::TextureType[TextureType];
	m_InternalTarget = TextureType;
	/*
	std::pair<unsigned,unsigned> ind;
	if(TextureType == TextureType::TEXTURE_3D)
		ind = make_index(level,0);
	else
		ind = make_index(level,side_or_depth);

	{
		m_VBO[ind] = core::CoreInstance->getRenderingDriver()->createVertexBufferObject();
		m_VBO[ind].setWidth(width);
		m_VBO[ind].setHeight(height);
		m_VBO[ind].setComponentSize(OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat]);
		m_VBO[ind]->setTarget(VBOType::TEXTURE);
	}
	*/
	if(TextureType == TextureType::TEXTURE_3D)
	{
		if(TextureInternalFormat >= TextureInternalFormat::COMPRESSED) //Compression is unsupported
			throw renderer::DriverException("Invalid texture internal format");
		//m_VBO[ind].setDepth(side_or_depth);
		//m_VBO[ind]->bind();
		//m_VBO[ind]->setData(VBOUsage::STATIC_DRAW,side_or_depth*width*height*OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat],data);
		//m_VBO[ind].setComponentSize(side_or_depth*OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat]);
		glBindTexture(m_Target,m_Texture);
		glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

		glTexImage3D(m_Target,level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,height,side_or_depth,0,OpenGL_GLSL_Tables::TextureFormat[TextureStorageFormat],OpenGL_GLSL_Tables::TextureStorage[TextureStorage],data);

		glBindTexture(m_Target,0);
		//m_VBO[ind]->unbind();
	}
	else if(TextureType == TextureType::TEXTURE_CUBE)
	{
		//generate additional PBO's. (if needed)
		if(side_or_depth > CubeTextureSide::Z_NEGATIVE) throw renderer::DriverException("Invalid cube texture side");

		if(TextureInternalFormat < TextureInternalFormat::COMPRESSED) //Uncompressed texture
		{
		//	m_VBO[ind]->bind();
		//	m_VBO[ind]->setData(VBOUsage::STATIC_DRAW,width*height*OpenGL_GLSL_Tables::TextureStorageSize[TextureStorage]*OpenGL_GLSL_Tables::TextureComponentsNumber[TextureStorageFormat],data);

			glBindTexture(m_Target,m_Texture);
			glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

			glTexImage2D(OpenGL_GLSL_Tables::CubeTextureSide[side_or_depth],level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,height,0,OpenGL_GLSL_Tables::TextureFormat[TextureStorageFormat],OpenGL_GLSL_Tables::TextureStorage[TextureStorage],data);

			glBindTexture(m_Target,0);
			//m_VBO[ind]->unbind();
		}
		else //Compressed texture mode
		{
			m_IsCompressed = true;
			if((width < 4) || (height < 4) ) throw renderer::DriverException("Invalid texture size");//Not enough is not enough ))
			//m_VBO[ind]->bind();
			unsigned block_size;
			//chose size
			switch(TextureInternalFormat)
			{
			case TextureInternalFormat::RGB_DXT1:
			case TextureInternalFormat::RGBA_DXT1:
				block_size = 8;
				break;
			default:
				block_size = 16;
			}
			//m_VBO[ind]->setData(VBOUsage::STATIC_DRAW,width*height*block_size/16,data);
			glBindTexture(m_Target,m_Texture);
			glCompressedTexImage2DARB(OpenGL_GLSL_Tables::CubeTextureSide[side_or_depth],level,OpenGL_GLSL_Tables::TextureInternalFormat[TextureInternalFormat],width,height,0,block_size*width*height/16,data);
			glBindTexture(m_Target,0);
			//m_VBO[ind]->unbind();
		}
	}
	else throw renderer::DriverException("Invalid texture format");//*/
	//Free VBO
//	core::CoreInstance->getRenderingDriver()->destroyVertexBufferObject(m_VBO[ind]);
//	m_VBO[ind].setVBO(NULL);
}

renderer::TextureType::type		OpenGL_GLSL_Texture::getTextureType() const
{
	return m_InternalTarget;
}

renderer::TextureUnit::type 	OpenGL_GLSL_Texture::getTextureUnit() const
{
	return m_Bounded ? m_BoundedUnit : m_DefaultUnit;
}

void*		OpenGL_GLSL_Texture::map(unsigned level,unsigned side)
{

	if((side > CubeTextureSide::Z_NEGATIVE) | (m_IsCompressed != false)) throw renderer::DriverException("Mapping failed");
	if(m_InternalTarget != TextureType::TEXTURE_CUBE)
		side = 0;
	std::pair<unsigned,unsigned> ind = make_index(level,side);
	m_VBO[ind] = core::CoreInstance->getRenderingDriver()->createVertexBufferObject();
	VertexBufferObject* obj = m_VBO[ind];
	obj->setTarget(VBOType::R2VB);
	obj->setData(VBOUsage::STATIC_DRAW,m_VBO[ind].getWidth()*m_VBO[ind].getHeight()*m_VBO[ind].getComponentSize(),NULL);
	obj->bind();
	bind();
	switch(m_InternalTarget)
	{
	case TextureType::TEXTURE_1D:
	case TextureType::TEXTURE_2D:
	case TextureType::TEXTURE_3D:
	case TextureType::TEXTURE_RECTANGLE:
		glGetTexImage(m_Target,level,m_SourceFormat,m_SourceStorage,NULL);
		break;
	case TextureType::TEXTURE_CUBE:
		glGetTexImage(OpenGL_GLSL_Tables::CubeTextureSide[side],level,m_SourceFormat,m_SourceStorage,NULL);
		break;
	}
	unbind();
	obj->unbind();
	return obj->map(VBOAccess::READ_WRITE);//*/
}

void		OpenGL_GLSL_Texture:: unmap(unsigned level,unsigned side)
{
	if((side > CubeTextureSide::Z_NEGATIVE) | (m_IsCompressed != false)) throw renderer::DriverException("Mapping failed");

	if(m_InternalTarget != TextureType::TEXTURE_CUBE)
		side = 0;
	std::pair<unsigned,unsigned> ind = make_index(level,side);
	VertexBufferObject* obj = m_VBO[ind];
	obj->unmap();
	obj->setTarget(VBOType::TEXTURE);
	obj->bind();
	bind();
	switch(m_InternalTarget)
	{
	case TextureType::TEXTURE_1D:
		glTexSubImage1D(m_Target,level,0,m_VBO[ind].getWidth(),m_SourceFormat,m_SourceStorage,NULL);
		break;
	case TextureType::TEXTURE_2D:
	case TextureType::TEXTURE_RECTANGLE:
		glTexSubImage2D(m_Target,level,0,0,m_VBO[ind].getWidth(),m_VBO[ind].getHeight(),m_SourceFormat,m_SourceStorage,NULL);
		break;
	case TextureType::TEXTURE_3D:
		glTexSubImage3D(m_Target,level,0,0,0,m_VBO[ind].getWidth(),m_VBO[ind].getHeight(),m_VBO[ind].getDepth(),m_SourceFormat,m_SourceStorage,NULL);
		break;

	case TextureType::TEXTURE_CUBE:
		glTexSubImage2D(OpenGL_GLSL_Tables::CubeTextureSide[side],level,0,0,m_VBO[ind].getWidth(),m_VBO[ind].getHeight(),m_SourceFormat,m_SourceStorage,NULL);
		break;
	}
	unbind();
	obj->unbind();
	core::CoreInstance->getRenderingDriver()->destroyVertexBufferObject(obj);
	m_VBO[ind].setVBO(NULL);
}

void		OpenGL_GLSL_Texture:: setUnit(renderer::TextureUnit::type unit)
{
	m_DefaultUnit = unit;
}

void		OpenGL_GLSL_Texture:: bind()
{
	m_Bounded = true;
	m_BoundedUnit = m_DefaultUnit;
	glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[m_BoundedUnit]);
	//glEnable(m_Target);
	glBindTexture(m_Target,m_Texture);
	glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[TextureUnit::TEXTURE0]);
}

void		OpenGL_GLSL_Texture:: bind(renderer::TextureUnit::type unit)
{
	m_Bounded = true;
	m_BoundedUnit = unit;
	glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[m_BoundedUnit]);
	//glEnable(m_Target);
	glBindTexture(m_Target,m_Texture);
	glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[TextureUnit::TEXTURE0]);
}

void		OpenGL_GLSL_Texture:: unbind()
{
	if(m_Bounded)
	{
		glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[m_BoundedUnit]);
		//glDisable(m_Target);
		glBindTexture(m_Target,0);
		glActiveTextureARB(OpenGL_GLSL_Tables::TextureUnit[TextureUnit::TEXTURE0]);
		m_Bounded = false;
	}
}

void		OpenGL_GLSL_Texture:: setMinFilter(renderer::TextureFiltering::type filter)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	if(m_InternalTarget == TextureType::TEXTURE_RECTANGLE) return;
	glTexParameteri(m_Target,GL_TEXTURE_MIN_FILTER,OpenGL_GLSL_Tables::TextureFiltering[filter]);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture:: setMagFilter(renderer::TextureFiltering::type filter)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	if(m_InternalTarget == TextureType::TEXTURE_RECTANGLE) return;
	glTexParameteri(m_Target,GL_TEXTURE_MIN_FILTER,OpenGL_GLSL_Tables::TextureFiltering[filter]);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture:: setAnisotropy(float val)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	if(m_InternalTarget == TextureType::TEXTURE_RECTANGLE) return;
	glTexParameterf(m_Target,GL_TEXTURE_MAX_ANISOTROPY_EXT,val);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture:: generateMipMaps()
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	if(m_InternalTarget == TextureType::TEXTURE_RECTANGLE) return;
	//glTexParameteri(m_Target,GL_GENERATE_MIPMAP_SGIS,val);
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture::   clampS(renderer::TextureClamping::type clamp)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	glTexParameteri(m_Target,GL_TEXTURE_WRAP_S,OpenGL_GLSL_Tables::TextureClamping[clamp]);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture::   clampT(renderer::TextureClamping::type clamp)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	glTexParameteri(m_Target,GL_TEXTURE_WRAP_T,OpenGL_GLSL_Tables::TextureClamping[clamp]);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture::   clampR(renderer::TextureClamping::type clamp)
{
	unsigned wasBounded = !m_Bounded;
	if(wasBounded)
		bind();
	//glBindTexture(m_Target,m_Texture);
	glTexParameteri(m_Target,GL_TEXTURE_WRAP_R,OpenGL_GLSL_Tables::TextureClamping[clamp]);
	//glBindTexture(m_Target,0);
	if(wasBounded)
		unbind();
}

void		OpenGL_GLSL_Texture::   clampQ(renderer::TextureClamping::type clamp)
{
	//glTexParameteri(m_Target,GL_TEXTURE_WRAP_Q,OpenGL_GLSL_Tables::TextureClamping[clamp]);
}

}
}
}
