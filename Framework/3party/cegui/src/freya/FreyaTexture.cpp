#include "freya/FreyaTexture.h"

namespace CEGUI
{
namespace freya
{
FreyaTexture::FreyaTexture()
: m_TextureSize(0,0), m_DataSize(0,0), m_Scaling(1,1)
  {
	m_Texture = core::EngineCore::getRenderingDriver()->createTexture();
  }

FreyaTexture::~FreyaTexture()
{
	if(m_Texture)
		core::EngineCore::getRenderingDriver()->destroyTexture(m_Texture);
}

const Size&
FreyaTexture::getSize() const
{
	return m_TextureSize;
}

const Size&
FreyaTexture::getOriginalDataSize() const
{
	return m_DataSize;
}

const Vector2&
FreyaTexture::getTexelScaling() const
{
	return m_Scaling;
}

void FreyaTexture::loadFromFile(const String& filename, const String& resourceGroup)
{
	// get and check existence of CEGUI::System object
	System* sys = System::getSingletonPtr();
	if (!sys)
		throw RendererException("FreyaTexture::loadFromFile: CEGUI::System object has not been created!");

	// load file to memory via resource provider
	RawDataContainer texFile;
	sys->getResourceProvider()->loadRawDataContainer(filename, texFile, resourceGroup);
	Texture *res = sys->getImageCodec().load(texFile, this);
	// unload file data buffer
	sys->getResourceProvider()->unloadRawDataContainer(texFile);
	// throw exception if data was load loaded to texture.
	if(!res)
		throw RendererException("FreyaTexture::loadFromFile: " + sys->getImageCodec().getIdentifierString() + " failed to load image '" + filename + "'.");

}
void FreyaTexture::loadFromMemory(const void *buffer, const Size & buffer_size, PixelFormat pixel_format)
{
	//Upscale to the next power of 2
	size_t size = buffer_size.d_width;
	if((size & (size - 1)) || !size){
		int log = 0;
		// get integer log of 'size' to base 2
		while(size >>= 1)
			++log;

		// use log to calculate value to use as size.
		size = (2 << log);
	}
	size_t xs = size;
	size = buffer_size.d_width;
	if((size & (size - 1)) || !size){
		int log = 0;
		// get integer log of 'size' to base 2
		while(size >>= 1)
			++log;

		// use log to calculate value to use as size.
		size = (2 << log);
	}
	size_t ys = size;
	if(!m_Texture)
		throw RendererException("FreyaTexture::loadFromMemory: failed to create texture object");

	if(buffer)
	{
		//Check the texture format
		void *mb = core::memory::Allocate(buffer_size.d_width * buffer_size.d_height * 4, core::memory::GENERIC_POOL);
		if(pixel_format == PF_RGB){
			for(size_t i = 0;i < buffer_size.d_width * buffer_size.d_height;i++){
				((uint8*)((mb)))[4 * i] = ((const uint8*)((buffer)))[3 * i];
				((uint8*)((mb)))[4 * i + 1] = ((const uint8*)((buffer)))[3 * i + 1];
				((uint8*)((mb)))[4 * i + 2] = ((const uint8*)((buffer)))[3 * i + 2];
				((uint8*)((mb)))[4 * i + 3] = 255;
			}
		}
		else
			memcpy(mb, buffer, static_cast<size_t>(buffer_size.d_width) * static_cast<size_t>(buffer_size.d_height) * 4);

		void *bmb = core::memory::Allocate(xs * ys * 4, core::memory::GENERIC_POOL);
		memset(bmb, 0, xs * ys * 4);
		for(unsigned i = 0; i < xs * ys * 4; i++)
			assert(((char*)bmb)[i] == 0);
		for(size_t i = 0;i < static_cast<size_t>( buffer_size.d_height);i++)
		{
			memcpy((uint8*)((bmb)) + i * xs * 4, (uint8*)((mb)) + i * static_cast<size_t>(buffer_size.d_width) * 4, static_cast<size_t>(buffer_size.d_width) * 4);
		}
		if( xs == static_cast<size_t>(buffer_size.d_width))
		{
			std::cout << "Checking mbm" << std::endl;
			for(unsigned i = 0; i < xs * ys * 4; i++)
			{
				assert(((char*)bmb)[i] == ((char*)mb)[i]);
			}
		}

		core::memory::Free(mb, core::memory::GENERIC_POOL);
		m_Texture->loadTexture(renderer::TextureType::TEXTURE_2D, 0, renderer::TextureInternalFormat::RGBA8, renderer::TextureFormat::RGBA, renderer::TextureStorage::UNSIGNED_BYTE, xs, ys, const_cast<void*>(bmb));
		core::memory::Free(bmb, core::memory::GENERIC_POOL);
	}
	else
		m_Texture->loadTexture(renderer::TextureType::TEXTURE_2D, 0, renderer::TextureInternalFormat::RGBA8, renderer::TextureFormat::RGBA, renderer::TextureStorage::UNSIGNED_BYTE, xs, ys, NULL);
	m_DataSize = buffer_size;
	m_TextureSize.d_width = xs;
	m_TextureSize.d_height = ys;
	m_Scaling.d_x = 1.0 / xs;
	m_Scaling.d_y = 1.0 / ys;
	m_Texture->setMagFilter(renderer::TextureFiltering::LINEAR);
	m_Texture->setMinFilter(renderer::TextureFiltering::LINEAR);
	m_Texture->clampS(renderer::TextureClamping::CLAMP);
	m_Texture->clampT(renderer::TextureClamping::CLAMP);
	std::cout << "[CEGUI]: Texture created: " << xs << " " << ys << std::endl;
}

void FreyaTexture::saveToMemory(void *buffer)
{
	if(!m_Texture)
		return;

	memcpy(buffer, m_Texture->map(), static_cast<size_t>(m_TextureSize.d_width) * static_cast<size_t>(m_TextureSize.d_width) * 4);
	m_Texture->unmap();
}
renderer::Texture *FreyaTexture::getFreyaTexture()
{
	return m_Texture;
}

void FreyaTexture::setFreyaTexture(renderer::Texture *tex,size_t w,size_t h)
{
	m_Texture = tex;
	m_TextureSize.d_width = w;
	m_TextureSize.d_height = h;
	m_Scaling.d_x = 1.0 / w;
	m_Scaling.d_y = 1.0 / h;
	m_DataSize = m_TextureSize;
}

}
}
