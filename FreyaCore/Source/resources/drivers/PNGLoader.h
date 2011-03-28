// PNG.h
//Created on: 05.05.2010
//Authors :
//	Sverchinskij Vitalij

#ifndef PNGLOADER_H_
#define PNGLOADER_H_

#define PNG_USER_MEM_SUPPORTED
//#define PNG_SETJMP_NOT_SUPPORTED

#include "png.h"
#include "core/EngineException.h"
#include "core/PluginCore.h"
#include "core/filesystem/FilesystemException.h"
#include "core/filesystem/Filesystem.h"
#include "core/memory/MemoryAllocator.h"

namespace png_driver_internal {

	class PNGException : public EngineException {
	public :
		PNGException(const EString& msg = EString("no user message.")) : m_msg("PNGDriver Exception : ") { 
			m_msg.append(msg);
		}
		virtual ~PNGException() throw() { }

		virtual EString message() const {
			return m_msg;
		}
	private :
		EString m_msg;
	};//class PNGException

	class PNGFile {
	public :
		PNGFile(const EString& path) : m_path(path) {
			m_stream = static_cast<unsigned char*>(core::CoreInstance->getFilesystem()->read(m_path));
			m_length = core::CoreInstance->getFilesystem()->fileSize(path);
			m_position = 0;
		}
		~PNGFile() {
			if(m_stream)
				core::memory::Free(m_stream, core::memory::GENERIC_POOL);
		}

		void read(void* dst, const size_t sz) {
			if(dst == NULL)
				throw PNGException(m_path.append(" PNGFile::read() invalid address."));
			if((m_position + sz) > m_length)
				throw PNGException(m_path.append(" PNGFile::read() range check error."));
			memcpy(dst, static_cast<void*>(m_stream + m_position), sz);
			m_position += sz;
		}

		void close() {
			if(m_stream)
				core::memory::Free(m_stream, core::memory::GENERIC_POOL);
			m_stream = NULL;
		}

		const EString& getFilename() const {
			return m_path;
		}
	private :
		EString			m_path;
		unsigned char*	m_stream;
		size_t			m_position;
		size_t			m_length;
	};//class PNGFile

	enum PNGColorType {
		GRAY = PNG_COLOR_TYPE_GRAY,
		GRAY_ALPHA = PNG_COLOR_TYPE_GRAY_ALPHA,
		RGB = PNG_COLOR_TYPE_RGB,
		RGBA = PNG_COLOR_TYPE_RGBA
	};//enum PNGColorType

	class PNGLoader {
	public :
		PNGLoader(const EString& path);
		
		~PNGLoader() {
			png_destroy_read_struct(&m_png_header, &m_png_info, NULL);
			if(m_surface)
				core::memory::Free(m_surface, core::memory::GENERIC_POOL);
		}

		void setXYLimits(const unsigned width, const unsigned height) {
			png_set_user_limits(m_png_header, width, height);
		}
		
		void setExpandGrayToByte() {
			png_set_gray_1_2_4_to_8(m_png_header);
		}

		void updateInfo() {
			png_read_update_info(m_png_header, m_png_info);
		}

		void readImage();

		const void* getSurface() const {
			return m_surface;
		}

		PNGColorType getColorType() const {
			return static_cast<PNGColorType>(png_get_color_type(m_png_header, m_png_info));
		}
		unsigned getWidth() const {
			return static_cast<unsigned>(png_get_image_width(m_png_header, m_png_info));
		}
		unsigned getHeight() const {
			return static_cast<unsigned>(png_get_image_height(m_png_header, m_png_info));
		}
		unsigned getBitDepth() const {
			return static_cast<unsigned>(png_get_bit_depth(m_png_header, m_png_info));
		}
		unsigned getRowSize() const {
			return static_cast<unsigned>(png_get_rowbytes(m_png_header, m_png_info));
		}

	private :
		PNGFile		m_file;
		png_structp	m_png_header;
		png_infop	m_png_info;
		void*		m_surface;
	};//class PNGLoader

}//namespace png_driver_internal

#endif//PNGLOADER_H_