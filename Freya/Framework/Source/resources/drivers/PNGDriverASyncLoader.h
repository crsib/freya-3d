// PNGDriverASyncLoader.h
//Created on 05.05.2010
//Authors: 
//	Sverchinskij Vitalij

#ifndef PNGDRIVERASYNCLOADER_H_
#define PNGDRIVERASYNCLOADER_H_

#include "core/taskmanager/Task.h"
#include "renderer/3DConstants.h"

namespace renderer {
	class Texture;
}

namespace resources {
	class Resource;
}

namespace png_driver_internal {

	template<renderer::TextureInternalFormat::type Ct>
	class ColorTypeInfo;

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::RGB8> {
	public :
		typedef unsigned char channel_t;
		typedef unsigned accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::RGBA8> {
	public :
		typedef unsigned char channel_t;
		typedef unsigned accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8> {
	public :
		typedef unsigned char channel_t;
		typedef unsigned accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE8_ALPHA8> {
	public :
		typedef unsigned char channel_t;
		typedef unsigned accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::RGB16> {
	public :
		typedef unsigned short channel_t;
		typedef unsigned __int64 accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::RGBA16> {
	public :
		typedef unsigned short channel_t;
		typedef unsigned __int64 accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16> {
	public :
		typedef unsigned short channel_t;
		typedef unsigned __int64 accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	template<>
	class ColorTypeInfo<renderer::TextureInternalFormat::LUMINANCE16_ALPHA16> {
	public :
		typedef unsigned short channel_t;
		typedef unsigned __int64 accum_t;
		static const size_t size;
		static const unsigned channel_num;
	};

	class PNGDriverASyncLoader : public core::taskmanager::Task {
	public :
		enum State {
			LOADING,
			MIPMAPS,
			TEXTUREFILL,
			CREATE_TEXTURE
		};
		
		PNGDriverASyncLoader(const EString& path, const bool mipmaps);

		virtual int operator() ();

		resources::Resource* getResource();
	protected :
		void loadPNG();
	private :
		template<renderer::TextureInternalFormat::type>
		void genMipMap();

		template<renderer::TextureInternalFormat::type>
		inline void packBlock(void*, const void*);

		unsigned char* m_surface;
		unsigned m_lvl;
		unsigned m_max_lvl;
		bool m_mipmaps;
		State m_state;
		resources::Resource* m_res;
		renderer::Texture* m_tex;
		EString m_path;
		unsigned m_width;
		unsigned m_height;
		unsigned m_bit_depth;
		renderer::TextureFormat::type m_tex_fmt;
		renderer::TextureInternalFormat::type m_tex_int_fmt;
		renderer::TextureStorage::type m_tex_storage;
	};

}//namespace png_driver_internal

#endif//PNGDRIVERASYNCLOADER_H_