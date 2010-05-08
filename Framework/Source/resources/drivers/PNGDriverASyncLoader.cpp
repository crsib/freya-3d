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

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::RGB8>::size = sizeof(unsigned char) * 3;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::RGB8>::channel_num = 3;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::RGBA8>::size = sizeof(unsigned char) * 4;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::RGBA8>::channel_num = 4;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8>::size = sizeof(unsigned char);
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8>::channel_num = 1;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8_ALPHA8>::size = sizeof(unsigned char) * 2;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8_ALPHA8>::channel_num = 2;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::RGB16>::size = sizeof(unsigned short) * 3;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::RGB16>::channel_num = 3;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::RGBA16>::size = sizeof(unsigned short) * 4;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::RGBA16>::channel_num = 4;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16>::size = sizeof(unsigned short);
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16>::channel_num = 1;

	const size_t ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16_ALPHA16>::size = sizeof(unsigned short) * 2;
	const unsigned ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16_ALPHA16>::channel_num = 2;

	resources::Resource* PNGDriverASyncLoader::getResource() {
		return m_res;
	}


	PNGDriverASyncLoader::PNGDriverASyncLoader(const EString& path, const bool mipmaps) : m_path(path){
		m_state = LOADING;
		m_tex = NULL;
		m_res = resources::__internal::createResource((renderer::Texture*)0);
		m_lvl = 0;
		m_max_lvl = 0;
		m_mipmaps = mipmaps;
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
		m_surface = core::memory::Allocate(sz, core::memory::GENERIC_POOL);
		memcpy(m_surface, png.getSurface(), sz);
		if(m_mipmaps) {
			unsigned max_sz = m_width > m_height ? m_width : m_height;
			while(max_sz > 1) {
				++m_max_lvl;
				max_sz >>= 1;
			}
		}
	}//loadPNG

	template<renderer::TextureInternalFormat::type Ct>
	void PNGDriverASyncLoader::genMipMap() {
		unsigned w = m_width >> 1;
		unsigned h = m_height >> 1;
		w += static_cast<unsigned>(w == 0);
		h += static_cast<unsigned>(h == 0);

		typename ColorTypeInfo<Ct>::channel_t* ret = 
			static_cast<ColorTypeInfo<Ct>::channel_t*>(core::memory::Allocate(w * h * ColorTypeInfo<Ct>::size, core::memory::GENERIC_POOL));
		unsigned row_sz = m_width * ColorTypeInfo<Ct>::size;
		unsigned mip_row_sz = w * ColorTypeInfo<Ct>::size;
		typename ColorTypeInfo<Ct>::accum_t accum[ColorTypeInfo<Ct>::channel_num] = {0};
		for(unsigned h_i = 0; h_i < h; h_i++) 
			for(unsigned w_i = 0; w_i < w; w_i++) {
				ColorTypeInfo<Ct>::channel_t* block_ptr 
					= static_cast<ColorTypeInfo<Ct>::channel_t*>(m_surface) + w_i * 2 * ColorTypeInfo<Ct>::size + h_i * 2 * row_sz;

				for(unsigned c = 0; c < ColorTypeInfo<Ct>::channel_num; c++) {
					accum[c] =  block_ptr[c];
					accum[c] += block_ptr[c + ColorTypeInfo<Ct>::size];
					accum[c] += block_ptr[c + row_sz];					
					accum[c] += block_ptr[c + row_sz + ColorTypeInfo<Ct>::size];
					accum[c] >>= 2;
					ret[w_i * ColorTypeInfo<Ct>::size + h_i * mip_row_sz + c] = static_cast<ColorTypeInfo<Ct>::channel_t>(accum[c]);
				}
			}
		core::memory::Free(m_surface, core::memory::GENERIC_POOL);
		m_width = w;
		m_height = h;
		m_surface = static_cast<void*>(ret);
	}//genMipMap()

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
			switch(m_tex_int_fmt) {
			case renderer::TextureInternalFormat::RGB8 :
					genMipMap<renderer::TextureInternalFormat::RGB8>();
					break;
			case renderer::TextureInternalFormat::RGBA8 :
					genMipMap<renderer::TextureInternalFormat::RGBA8>();
					break;
			case renderer::TextureInternalFormat::RGB16 :
					genMipMap<renderer::TextureInternalFormat::RGB16>();
					break;
			case renderer::TextureInternalFormat::RGBA16 :
					genMipMap<renderer::TextureInternalFormat::RGB16>();
					break;
			case renderer::TextureInternalFormat::LUMINANCE8 :
					genMipMap<renderer::TextureInternalFormat::LUMINANCE8>();
					break;
			case renderer::TextureInternalFormat::LUMINANCE8_ALPHA8 :
					genMipMap<renderer::TextureInternalFormat::LUMINANCE8_ALPHA8>();
					break;
			case renderer::TextureInternalFormat::LUMINANCE16 :
					genMipMap<renderer::TextureInternalFormat::LUMINANCE16>();
					break;
			case renderer::TextureInternalFormat::LUMINANCE16_ALPHA16 :
					genMipMap<renderer::TextureInternalFormat::LUMINANCE16_ALPHA16>();
					break;
			};
			++m_lvl;
			m_state = TEXTUREFILL;
			return PNGDriverASyncLoader::MAIN_THREAD;
		};//switch m_state
		throw(PNGException());
	}

}//namespace png_driver_internal