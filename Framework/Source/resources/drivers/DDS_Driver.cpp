#include <renderer/DriverSubsystems/Texture.h>
#include <renderer/RenderingAPIDriver.h>
#include <core/filesystem/Filesystem.h>
#include <core/EngineException.h>
#include "DDS_Driver.h"

//packs 4 char codes to integer according to its order 
#define CHARS_TO_UNSIGNED(a,b,c,d) (unsigned(a) << 24) | (unsigned(b) << 16) | (unsigned(c) << 8) | (unsigned(d))

//TODO: add floating point RGBA32F and RGBA16F formats

namespace __dds_driver {

	class PixelMask {
		PixelMask() {} //depricated
	public :
		const unsigned r() const {
			return _M_r;
		}
		const unsigned g() const {
			return _M_g;
		}
		const unsigned b() const {
			return _M_b;
		}
		const unsigned a() const {
			return _M_a;
		}
		
		PixelMask(unsigned __r, unsigned __g, unsigned __b, unsigned __a) : 
		_M_r(__r), _M_g(__g), _M_b(__b), _M_a(__a) {
		}

		PixelMask(const PixelMask& __pf) :
		_M_r(__pf.r()), _M_g(__pf.g()), _M_b(__pf.b()), _M_a(__pf.a()) {
		}

		bool operator ==(const PixelMask& __pf) const {
			return (_M_r == __pf.r()) && (_M_g == __pf.g()) && (_M_b == __pf.b()) && (_M_a == __pf.a());
		}

		static const PixelMask RGBA8;
		static const PixelMask ARGB8;
		static const PixelMask ABGR8;
		
		static const PixelMask RGB8;
		static const PixelMask BGR8;
	private :
		unsigned _M_r;
		unsigned _M_g;
		unsigned _M_b;
		unsigned _M_a;
	};

	//values used to determine which DXT compression version is used
	enum FourCC {
		DXT1 = CHARS_TO_UNSIGNED('D','X','T','1'),
		FP16 = CHARS_TO_UNSIGNED('D','X','T','2'),
		DXT3 = CHARS_TO_UNSIGNED('D','X','T','3'),
		FP32 = CHARS_TO_UNSIGNED('D','X','T','4'),
		DXT5 = CHARS_TO_UNSIGNED('D','X','T','5')
	};

	struct DDSPixelFormat {
		enum {
			RGB, //texture is uncompressed
			FOURCC, //texture compressed with DXT algorith
			ALPHAPIXELS // uncompressed texture contains alpha channel(do not significant if FOURCC used instead RGB)
		};
		unsigned size; //structure size
		unsigned flags; // see enum below
		FourCC fourcc; // DXT version(if FOURCC flag is used)
		unsigned bpp; // bit per pixel(if RGB flag is used)
		PixelMask pixel_mask; // structure used to describe uncompressed texture format
	};

	//DDS file extensions
	struct DDSCaps {
		enum {
			C1_COMPLEX, //file contains additional surfaces besides main surface(e.g. mipmaps, volume, cubmap)
			C1_MIPMAP, //contains mipmap(s)
			C1_TEXTURE, //requried flag
			
			C2_CUBEMAP, //cubemap texture
			//next 6 flags describe which sides of cubemap are presented
			C2_POS_X,
			C2_NEG_X,
			C2_POS_Y,
			C2_NEG_Y,
			C2_POS_Z,
			C2_NEG_Z,

			C2_VOLUME //volumemap
		};

		unsigned caps1; // C1_*
		unsigned caps2; // C2_*
		unsigned caps3; // not used
		unsigned caps4; // not used
	};

	//DDS file heap used in DX9 version
	struct DDSHeap9 {
		//structure field validation flags
		enum {
			CAPS,
			HEIGHT,
			WIDTH,
			PITCH,
			PIXELFORMAT,
			MIPMAP_COUNT,
			LINEAR_SIZE,
			DEPTH
		};
		unsigned magic; //DDS file magic number
		unsigned size; //structure size
		unsigned flags; //validation flags
		unsigned height; //main surface height(in pixel, even if texture is compressed)
		unsigned width; //main surface width
		union {
			unsigned pitch;//DWORD aligned. Number of bytes per scan line in an uncompressed texture 
			unsigned linear_size;//total size of compressed main surface
		};
		unsigned depth; // depth of volumemap
		unsigned mipmap_count; //mipmap count if presented
	private :
		unsigned reserved[11];
	public :
		DDSPixelFormat pixel_format; //texture pixel format
		DDSCaps caps; //extensions used in current file
	private :
		unsigned reserved2;
	};

	struct DDSHeap10 {

	};
	
	//converts DX pixelformat representation into Freya format
	renderer::TextureInternalFormat::type getTextureInternalFormat(const DDSPixelFormat& __pf) {		
		typedef renderer::TextureInternalFormat::type tif_type;
		//compressed or floating point texture type
		if(__pf.flags & DDSPixelFormat::FOURCC)
			switch(__pf.fourcc) {
				case FourCC::DXT1 : 
					return tif_type::RGBA_DXT1;
				case FourCC::FP16 :
					return tif_type::RGB16F;
				case FourCC::DXT3 :
					return tif_type::RGBA_DXT3;
				case FourCC::FP32 :
					return tif_type::RGB32F;
				case FourCC::DXT5 :
					return tif_type::RGBA_DXT5;
				default :
					throw EngineException();
			};
		//uncompressed texture with alpha channel
		/*if(__pf.flags & DDSPixelFormat::ALPHAPIXELS) {
			switch(__pf.pixel_mask) {
				case(PixelMask::RGBA8) :
					return tif_type::RGBA8;
				default :
					throw EngineException();
			};
		}
		//uncompressed texture without alpha
		switch(__pf.pixel_mask) {
			case(PixelMask::RGB8) :
				return tif_type::RGB8;
			default :
				throw EngineException();
		};*/
		throw EngineException();
	}

	//determines texture type by extension flags used if file
	renderer::TextureType::type getTextureType(const DDSCaps& __caps) {
		typedef renderer::TextureType::type tex_type;
		if(!(__caps.caps1 & DDSCaps::C1_TEXTURE))
			throw(EngineException());
		if(__caps.caps1 & DDSCaps::C1_COMPLEX) {
			if(__caps.caps1 & DDSCaps::C2_CUBEMAP)
				return tex_type::TEXTURE_CUBE;
			if(__caps.caps1 & DDSCaps::C2_VOLUME)
				return tex_type::TEXTURE_3D;
		}
		return tex_type::TEXTURE_2D;
	}

	//returns texture storage format, that describe which color components are presented
	renderer::TextureFormat::type getTextureStorageFormat(renderer::TextureInternalFormat::type __tex_internal_format) {
		typedef renderer::TextureInternalFormat::type tif_type;
		typedef renderer::TextureFormat::type tf_type;
		switch(__tex_internal_format) {
			case tif_type::RGBA_DXT1 :
				return tf_type::RGBA;
			case tif_type::RGBA_DXT3 :
				return tf_type::RGBA;
			case tif_type::RGBA_DXT5 :
				return tf_type::RGBA;
			case tif_type::RGBA8 :
				return tf_type::RGBA;
			case tif_type::RGB8 :
				return tf_type::RGB;
			case tif_type::RGB16F :
				return tf_type::RGB;
			case tif_type::RGB32F :
				return tf_type::RGB;
			default :
				throw EngineException();
		};
	}

	//returns type that represent each color component
	renderer::TextureStorage::type getTextureStorage(renderer::TextureInternalFormat::type __tex_internal_format) {
		typedef renderer::TextureInternalFormat::type tif_type;
		typedef renderer::TextureStorage::type ts_type;
		switch(__tex_internal_format) {
			case tif_type::RGBA_DXT1 :
				return ts_type::BYTE;
			case tif_type::RGBA_DXT3 :
				return ts_type::BYTE;
			case tif_type::RGBA_DXT5 :
				return ts_type::BYTE;
			case tif_type::RGBA8 :
				return ts_type::UNSIGNED_BYTE;
			case tif_type::RGB8 :
				return ts_type::UNSIGNED_BYTE;
			case tif_type::RGB16F :
				return ts_type::FLOAT;
			case tif_type::RGB32F :
				return ts_type::FLOAT;
			default :
				throw EngineException();
		};
	}

	// pass if texture internal format and texture type are compotable
	void checkFormatIntegrity(renderer::TextureInternalFormat::type __tex_internal_format, renderer::TextureType::type __tex_type) {
		typedef renderer::TextureInternalFormat::type tif_type;
		typedef renderer::TextureType::type tex_type;
		if(__tex_internal_format & (tif_type::RGBA_DXT1 | tif_type::RGBA_DXT3 | tif_type::RGBA_DXT5))
			if(__tex_type == tex_type::TEXTURE_3D)
				throw EngineException();
	}

	/*textureLoader* chooseTextureLoader(renderer::TextureInternalFormat::type __tex_internal_format, renderer::TextureType::type __tex_type) throw(EngineException) {
		
	}*/

	//dds9 file loader
	renderer::Texture* dds9Load(const EString& __filepath) {
		unsigned char* __file = reinterpret_cast<unsigned char*>(core::CoreInstance->getFilesystem()->read(__filepath));
		const DDSHeap9* __heap= reinterpret_cast<const DDSHeap9*>(__file);
		//required fields
		const unsigned __req_fields = DDSHeap9::CAPS | DDSHeap9::HEIGHT | DDSHeap9::WIDTH | DDSHeap9::PIXELFORMAT;

		//checking some values
		if(__heap->magic != CHARS_TO_UNSIGNED('D','D','S',' '))
			throw EngineException();
		if(__heap->size != sizeof(DDSHeap9))
			throw EngineException();
		if((__heap->flags & __req_fields) != __req_fields)
			throw EngineException();

		//gathering information about texture(s) presented in file
		renderer::TextureInternalFormat::type __tex_internal_format = getTextureInternalFormat(__heap->pixel_format);
		renderer::TextureType::type __tex_type = getTextureType(__heap->caps);
		renderer::TextureFormat::type __tex_storage_format = getTextureStorageFormat(__tex_internal_format);
		renderer::TextureStorage::type __tex_storage = getTextureStorage(__tex_internal_format);
		checkFormatIntegrity(__tex_internal_format, __tex_type);//it's OK
		//choose texture loader function according to it's type

		//now we have enough information to allocate memory and load texture(s)

		//short debug version...
		if(__tex_type != renderer::TextureType::TEXTURE_2D)
			throw EngineException();
		if(__tex_internal_format = renderer::TextureInternalFormat::RGBA_DXT5) {
			renderer::Texture* __tex = core::CoreInstance->getRenderingDriver()->createTexture();
			__tex->loadTexture(__tex_type, 0, __tex_internal_format, _tex_storage_format, __tex_storag,
								__heap->width, __heap->height, __file + sizeof(DDSHeap9));
			return __tex;
		}
		throw EngineException();
	}

}//namespace __dds_diver

namespace resources {
	namespace drivers {
		
		template<>
		DDSDriverID<DDSDriver9>::DDSDriverID() {
		}

		template<>
		DDSDriverID<DDSDriver10>::DDSDriverID() {
		}

		template<>
		EString DDSDriverID<DDSDriver9>::id() const {
			return EString("DDS9");
		}

		template<>
		EString DDSDriverID<DDSDriver10>::id() const {
			return EString("DDSA");
		}

		resources::Resource* DDSDriver9::loadSynchronous(const EString& __ID) {
			
		}

		resources::Resource* DDSDriver9::loadAsynchronous(const EString& __ID) {
		}

		void DDSDriver9::destroy(Resource* __res)
		{
			if(!res->ready())
				return;
			renderer::Texture* tex = res->get<renderer::Texture*>();
			core::CoreInstance->getRenderingDriver()->destroyTexture(tex);
			resources::__internal::destroyResource(res);
		}

	}
}

#undef CHARS_TO_UNSIGNED