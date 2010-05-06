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
		void genMipMap();
	private :
		unsigned char* m_surface;
		unsigned m_lvl;
		unsigned m_max_lvl;
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