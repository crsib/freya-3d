// PNGLoader.cpp
//Created on: 05.05.2010
//Authors :
//  Sverchinskij Vitalij

#include "PNGLoader.h"

namespace png_driver_internal {

	namespace png_freya_interface {
		png_voidp allocate(png_structp, png_size_t sz) {
			png_voidp ret = static_cast<png_voidp>(core::memory::Allocate(sz, core::memory::GENERIC_POOL));
			return ret;
		}

		void free(png_structp, png_voidp ptr) {
			core::memory::Free(ptr, core::memory::GENERIC_POOL);
		}

		void read(png_structp header, png_bytep ptr, png_size_t sz) {
			PNGFile* png_file = static_cast<PNGFile*>(::png_get_io_ptr(header));
			png_file->read(static_cast<void*>(ptr), sz);
		}
	}

	PNGLoader::PNGLoader(const EString& path) : m_file(path) {
		m_surface = NULL;
		m_png_header = NULL;
		m_png_info = NULL;
		const size_t sig_bytes_num = 8;
		unsigned char sig_bytes[sig_bytes_num];
		m_file.read(static_cast<unsigned char*>(sig_bytes), sig_bytes_num);
		if(png_sig_cmp(reinterpret_cast<png_bytep>(sig_bytes), 0, sig_bytes_num))
			throw(PNGException(m_file.getFilename() + EString("is not png file.")));
		m_png_header = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL, NULL, 
			reinterpret_cast<png_malloc_ptr>(&png_freya_interface::allocate),
			reinterpret_cast<png_free_ptr>(&png_freya_interface::free));
		m_png_info = png_create_info_struct(m_png_header);
		png_set_sig_bytes(m_png_header, sig_bytes_num);
		png_set_read_fn(m_png_header, static_cast<png_voidp>(&m_file), reinterpret_cast<png_rw_ptr>(&png_freya_interface::read));
		png_read_info(m_png_header, m_png_info);
	}

	void PNGLoader::readImage() {
		if(m_surface != NULL)
			throw PNGException(m_file.getFilename() + EString(" is already allocated in memory."));
		unsigned height = png_get_image_height(m_png_header, m_png_info);
		unsigned row_sz = png_get_rowbytes(m_png_header, m_png_info);
		m_surface = core::memory::Allocate(row_sz * height,
			core::memory::GENERIC_POOL);
		png_bytepp row_ptrs = static_cast<png_bytepp>(core::memory::Allocate(sizeof(png_bytep) * height, core::memory::GENERIC_POOL));
		for(unsigned i = 0; i < height; i++)
			row_ptrs[height - i - 1] = static_cast<png_bytep>(m_surface) + (i * row_sz);
		png_read_image(m_png_header, row_ptrs);
		png_read_end(m_png_header, m_png_info);
		m_file.close();
	}

}//namespace png_driver_internal