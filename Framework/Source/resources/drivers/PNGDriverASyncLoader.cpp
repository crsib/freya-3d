// PNGDriverASyncLoader.cpp
//Created on 05.05.2010
//Authors: 
//	Sverchinskij Vitalij

#include "PNGLoader.h"
#include "PNGDriverASyncLoader.h"
#include "core/PluginCore.h"
#include "resources/Resource.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"

namespace png_driver_internal {

	resources::Resource* PNGDriverASyncLoader::getResource() {
		return m_res;
	}


	PNGDriverASyncLoader::PNGDriverASyncLoader(const EString& path, const bool mipmaps) : m_path(path){
		m_state = LOADING;
		m_tex = NULL;
		m_res = resources::__internal::createResource((renderer::Texture*)0);
		m_lvl = 0;
		if(mipmaps) {
		/**/
		} else
			m_max_lvl = 0;
	}

	void PNGDriverASyncLoader::loadPNG() {
		PNGLoader png(m_path);
		m_bit_depth = png.getBitDepth();
		bool is_updated = false;
		switch(png.getColorType()) {
		case RGB :
			m_tex_fmt = renderer::TextureFormat::RGB;
			if(m_bit_depth == 8)
				m_tex_int_fmt = renderer::TextureInternalFormat::RGB8;
			else
				m_tex_int_fmt = renderer::TextureInternalFormat::RGB16;
			break;
		case RGBA :
			m_tex_fmt = renderer::TextureFormat::RGBA;
			if(m_bit_depth == 8)
				m_tex_int_fmt = renderer::TextureInternalFormat::RGBA8;
			else
				m_tex_int_fmt = renderer::TextureInternalFormat::RGBA16;
			break;
		case GRAY :
			m_tex_fmt = renderer::TextureFormat::LUMINANCE;
			if(m_bit_depth == 16)
				m_tex_int_fmt = renderer::TextureInternalFormat::LUMINANCE16;
			else {
				m_tex_int_fmt = renderer::TextureInternalFormat::LUMINANCE8;
				if(m_bit_depth < 8) {
					png.setExpandGrayToByte();
					is_updated = true;
				}
			}
			break;
		case GRAY_ALPHA :
			m_tex_fmt = renderer::TextureFormat::LUMINANCE_ALPHA;
			if(m_bit_depth == 16)
				m_tex_int_fmt = renderer::TextureInternalFormat::LUMINANCE16_ALPHA16;
			else
				m_tex_int_fmt = renderer::TextureInternalFormat::LUMINANCE8_ALPHA8;
			break;
		default :
			throw PNGException(m_path + EString(" unsuported color type."));
		};//switch bitdepth
		if(is_updated) {
			png.updateInfo();
			m_bit_depth = png.getBitDepth();
		}
		switch(m_bit_depth) {
		case 16 :
			m_tex_storage = renderer::TextureStorage::UNSIGNED_SHORT;
			break;
		case 8 :
			m_tex_storage = renderer::TextureStorage::UNSIGNED_BYTE;
			break;
		default :
			throw PNGException(m_path + EString(" unsupported bit depth."));
		};
		m_width = png.getWidth();
		m_height = png.getHeight();
		png.readImage();
		size_t sz = png.getRowSize() * m_height;
		m_surface = static_cast<unsigned char*>(core::memory::Allocate(sz, core::memory::GENERIC_POOL));
		memcpy(static_cast<void*>(m_surface), png.getSurface(), sz);
	}//loadPNG

	int PNGDriverASyncLoader::operator() () {
		switch(m_state) {
		case LOADING :
			loadPNG();
			//create texture from main thread
			m_state = CREATE_TEXTURE;
			return PNGDriverASyncLoader::MAIN_THREAD;
			break;
		case CREATE_TEXTURE :
			if(m_tex == NULL) {
				m_tex = core::CoreInstance->getRenderingDriver()->createTexture();
				m_res = resources::__internal::setResource(m_res, m_tex);
			}
			//don't wait. Upload to accelerator loaded surface.			
			m_state = TEXTUREFILL;
		case TEXTUREFILL :
			m_tex->loadTexture(renderer::TextureType::TEXTURE_2D, m_lvl, m_tex_int_fmt, m_tex_fmt, m_tex_storage, m_width, m_height,
				m_surface);
			//continue mips generating
			if(m_lvl < m_max_lvl) {
				m_state = MIPMAPS;
				return PNGDriverASyncLoader::SECONDARY_THREAD;
			}
			//all done
			core::memory::Free(m_surface, core::memory::GENERIC_POOL);
			resources::__internal::finalizeResource(m_res);
			return PNGDriverASyncLoader::DONE;
		case MIPMAPS :
			//genMipMap();
			throw PNGException("mipmaps is not allowed for now.");
			++m_lvl;
			m_state = TEXTUREFILL;
			return PNGDriverASyncLoader::MAIN_THREAD;
		};//switch m_state
	}

}//namespace png_driver_internal