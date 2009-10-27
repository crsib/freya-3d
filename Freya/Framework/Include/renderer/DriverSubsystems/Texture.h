/*
 * Texture.h
 *
 *  Created on: 06.09.2008
 *      Author: vedenko
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

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
#include "renderer/3DConstants.h"

namespace renderer
{
class VertexBufferObject;
//! Texture abstraction
/*!
 * This class provides API independent abstraction of texture concept.
 */
class Texture: virtual public ::EngineSubsystem
{
public:
	//! Load texture from data to accelerator (1D,2D,rectangle textures <STRONG>only</STRONG>)
	/*!
	 * This function loads either 1D, either 2D, either rectangle texture (i.e. textures with unclamped texture coordinates).
	 * The texture could be compressed (in most cases only 2D textures could be compressed).
	 * If the pointer to data is NULL, than texture is created without data, which can be set later using corresponding VBO or some render-to-texture method.
	 * \param textureType is a type of texture to be loaded (see the remark above) described by TextureType
	 * \param level is a mip level of a texture to be loaded.
	 * \param textureInternalFormat is a format of internal (e.g. VRAM) texture representation. Described by TextureInternalFormat.
	 * \param textureStorageFormat  is a format of in RAM texture representation (described by TextureFormat). The value is not significant if the texture is compressed(e.g. textureInternalFormat is >= renderer::TextureInternalFormat::COMPRESSED). (Engine limitation: compressed textures ought to be stored inside RAM in compressed form, despite some API could compress texture by them self)
	 * \param textureStorage is a data format of each texture component required by textureStorageFormat (described by TextureStorage). The value is not significant if the texture is compressed.
	 * \param width is a width of texture
	 * \param height is a height of texture
	 * \param data is a pointer to data to be loaded. Could be NULL
	 * \throw renderer::DriverException on any error occured (mostly the incorrect format errors)
	 */
	virtual void loadTexture(renderer::TextureType::type textureType,unsigned level,renderer::TextureInternalFormat::type textureInternalFormat,renderer::TextureFormat::type textureStorageFormat,renderer::TextureStorage::type textureStorage,unsigned width,unsigned height,void* data) = 0;
	//! Load texture from data to accelerator (3D and cube textures <STRONG>only</STRONG>)
	/*!
	 * This function loads either 3D, either cube texture.
	 * The texture could be compressed (in most cases only cube textures could be compressed).
	 * VBO's for each texture level/side are generated on the fly when needed
	 * If the pointer to data is NULL, than texture is created without data, which can be set later using corresponding VBO or some render-to-texture method.
	 * \param textureType is a type of texture to be loaded (see the remark above) described by TextureType
	 * \param level is a mip level of a texture to be loaded.
	 * \param textureInternalFormat is a format of internal (e.g. VRAM) texture representation. Described by TextureInternalFormat.
	 * \param textureStorageFormat  is a format of in RAM texture representation (described by TextureFormat). The value is not significant if the texture is compressed(e.g. textureInternalFormat is >= renderer::TextureInternalFormat::COMPRESSED). (Engine limitation: compressed textures ought to be stored inside RAM in compressed form, despite some API could compress texture by them self)
	 * \param textureStorage is a data format of each texture component required by textureStorageFormat (described by TextureStorage). The value is not significant if the texture is compressed.
	 * \param width is a width of texture
	 * \param height is a height of texture
	 * \param side_or_depth is either a cube texture side described by CubeTextureSide or a depth level for 3D texture
	 * \param data is a pointer to data to be loaded. Could be NULL
	 * \throw renderer::DriverException on any error occured (mostly the incorrect format errors)
	 */
	virtual void loadTexture(renderer::TextureType::type textureType,unsigned level,renderer::TextureInternalFormat::type textureInternalFormat,renderer::TextureFormat::type textureStorageFormat,renderer::TextureStorage::type textureStorage,unsigned width,unsigned height,unsigned side_or_depth,void* data) = 0;
	//! Retrieve the texture type (as set by previous functions)
	/*!
	 *  Returns the type of current texture.
	 *  \return Type of current texture as one of TextureType constants
	 */
	virtual renderer::TextureType::type getTextureType() const = 0 ;

	//! Retrieve a unit to which texture is bound
	virtual renderer::TextureUnit::type getTextureUnit() const = 0;

	//! Map a memory region with texture data to RAM for both reading and writing
	/*!
	 * Maps a memory region for demanded texture level to memory for RW access. Please note, this command possibly wont block texture object from using. All changes are committed only after calling Texture::unmap method.
	 * The operation is pretty slow, so try to avoid it.
	 * \param level is mip level of texture to map
	 * \param side  is a cube texture side (described by CubeTextureSide) for cube texture or forced to 0 for other texture types
	 * \return Pointer to a mapped memory region
	 * \throw  renderer::DriverException on any error
	 */
	virtual void* map(unsigned level = 0,unsigned side = 0) = 0;//Maps texture memory to client, memory is rw
	//! Unmap memory region and commit changes to accelerator
	/*!
	 * Unmaps previously mapped memory region and commit changes done to accelerator.
	 * <STRONG> Only this method could be used to unmap a memory region. Pointer for mapped region becomes invalid </STRONG>
	 * The operation is pretty slow, so try to avoid it.
	 * \param level is mip level of texture to map
	 * \param side  is a cube texture side (described by CubeTextureSide) for cube texture or forced to 0 for other texture types
	 * \throw  renderer::DriverException on any error
	 */
	virtual void  unmap(unsigned level = 0,unsigned side = 0) = 0;//Unmaps texture memory from client

	//Filtering
	//! Set minifying filter
	/*!
	 * Set the minifying filter.
	 * The	texture	minifying filter is used whenever
	 *	    the	pixel being textured maps to an	area greater
	 *	    than one texture element.
	 * \param filter is minifying filter. Could be any of TextureFilter constants
	 */
	virtual void  setMinFilter(renderer::TextureFiltering::type filter) = 0;//filter described by TextureFilter namespace
    //! Set the magnification filter
	/*!
	 * Sets the magnification filter.
	 *   The	texture	magnification filter is used when
	 *	    the	pixel being textured maps to an	area less than
	 *	    or equal to	one texture element.
	 * \param filter is magnification filter. Could be TextureFilter::NEAREST or TextureFilter::LINEAR
	 */
	virtual void  setMagFilter(renderer::TextureFiltering::type filter) = 0;
	//! Set anisotropy value
	/*!
	 *  Sets the tangent of anisotropy angle
	 *  \param val is a tangent of anisotropy angle. Should be greater or equal to one.
	 */
	virtual void  setAnisotropy(float val) = 0;
	//Auto mip-map
	//! Force mipmap genderation
	/*!
	 *  Forces the device to generate all sufficient mipmap levels
	 */
	virtual void  generateMipMaps() = 0;//Sets the mip map auto generation

	//clamping
	//! Set the texture clamping mode for S coordinate
	/*!
	 *  Sets the texture clamping mode for S coordinate.
	 *  \param clamp is a clamping mode described by TextureClamping
	 */
	virtual void    clampS(renderer::TextureClamping::type clamp) = 0;//Clamping is described by TextureClamping enum
	//! Set the texture clamping mode for T coordinate
	/*!
	 *  Sets the texture clamping mode for T coordinate.
	 *  \param clamp is a clamping mode described by TextureClamping
	 */
	virtual void    clampT(renderer::TextureClamping::type clamp) = 0;//Clamping is described by TextureClamping enum
	//! Set the texture clamping mode for R(P) coordinate (if supported)
	/*!
	 *  Sets the texture clamping mode for R(P) coordinate.
	 *  \param clamp is a clamping mode described by TextureClamping
	 */
	virtual void    clampR(renderer::TextureClamping::type clamp) = 0;//Clamping is described by TextureClamping enum
	//! Set the texture clamping mode for Q coordinate (if supported)
	/*!
	 *  Sets the texture clamping mode for Q coordinate.
	 *  \param clamp is a clamping mode described by TextureClamping
	 */
	virtual void    clampQ(renderer::TextureClamping::type clamp) = 0;//Clamping is described by TextureClamping enum
};

}

#endif /* TEXTURE_H_ */
