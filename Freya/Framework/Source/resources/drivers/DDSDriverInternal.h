/* DDSDriverInternal.h
 * Created on: 28.04.2010
 *      Author: Sverchinskij
 */

#ifndef DDSDRIVERINTERNAL_H_
#define DDSDRIVERINTERNAL_H_

#include "core/PluginCore.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"
#include "core/filesystem/Filesystem.h"

#include <vector>
#include "core/memory/MemoryAllocator.h"
#include "resources/Resource.h"

#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"
#include <cmath>

#include <iostream>

namespace resources
{
namespace __internal
{
template<>
resources::Resource* 	createResource(renderer::Texture*	resource);

template<>
resources::Resource*
setResource(Resource* res,renderer::Texture*	resource);
}
}

#define DDS_FOUR_CHARS_TO_DWORD(ch1, ch2, ch3, ch4) ((ch1) | (ch2 << 8) | (ch3 << 16) | (ch4 << 24))

namespace dds_driver_internal {

	//PixelFormat structure used in dds
	struct DDSPixelFormat {
		    uint32_t size;//of this structure
			uint32_t flags;
			uint32_t fourcc;
			uint32_t rgb_bitcount;
			uint32_t rbit_mask;
			uint32_t gbit_mask;
			uint32_t bbit_mask;
			uint32_t abit_mask;
	};

	//Structure used to describe DX9 DDS file header
	struct DDSHeader {
		    uint32_t size;//of this structure
			uint32_t flags;
			uint32_t height;
			uint32_t width;
			uint32_t linear_size;
			uint32_t depth;
			uint32_t mipmap_count;
			uint32_t reserved1[11];
			DDSPixelFormat pf;
			//capabilities extensions
			uint32_t caps;
			uint32_t caps2;
			uint32_t caps3;
			uint32_t caps4;
			uint32_t reserved2;

	};

	//Additional to DDSHeader structure used in DX10 DDS files
	struct DDSHeader10 {
		//Empty yet. Could be realized in future.
	};

	//only actual PixelFormat::flags values
	enum PFFlags {
		FOURCC = 0x4
	};


	enum PFFourCC {
		DXT1 = DDS_FOUR_CHARS_TO_DWORD('D', 'X', 'T', '1'),
		DXT3 = DDS_FOUR_CHARS_TO_DWORD('D', 'X', 'T', '3'),
		DXT5 = DDS_FOUR_CHARS_TO_DWORD('D', 'X', 'T', '5'),
		//it is not a compression type, but indicates that DX10 header is presented
		DX10 = DDS_FOUR_CHARS_TO_DWORD('D', 'X', '1', '0')
	};

	//only actual and required flags
	enum DDSHeaderFlags {
		//CAPS = 0x1,
		//HEIGHT = 0x2,
		//WIDTH = 0x4,
		//PITCH = 0x8,
		//PF = 0x1000,
		MIPMAP_COUNT = 0x20000,
		//LINEARSIZE = 0x80000,
		//DEPTH = 0x800000
	};

	enum DDSHeaderCaps {
		//COMPLEX = 0x8,
		MIPMAP = 0x400000,
		//TEXTURE = 0x1000
	};

	enum DDSHeaderCaps2 {
		CUBEMAP = 0x200,
		CUBEMAP_POSITIVE_X = 0x400,
		CUBEMAP_NEGATIVE_X = 0x800,
		CUBEMAP_POSITIVE_Y = 0x1000,
		CUBEMAP_NEGATIVE_Y = 0x2000,
		CUBEMAP_POSITIVE_Z = 0x4000,
		CUBEMAP_NEGATIVE_Z = 0x8000,
		VOLUME = 0x200000
	};

	class DDSException : public EngineException {
	public :
		DDSException(const EString& msg = "no user message") : m_message("DDSDriver exception : ") {
			m_message.append(msg);
		}
		virtual ~DDSException() throw() { }
		
		virtual EString message() const {
			return m_message;
		}
	private :
		EString m_message;
	};


	class DDSDriverAsyncLoader : public core::taskmanager::Task {
	public :

		enum State {
			LOADING,
			TEXTUREFILL,
		};

		DDSDriverAsyncLoader(const EString& path = "", const bool mipmaps = false) : m_cube_sides(), m_path(path) {			
			m_state = LOADING;
			m_lvl = 0;
			m_cube_disp = 0;
			m_tex_fmt_type = renderer::TextureFormat::RGBA;//by def. will be changed if DXT1 used.
			m_tex = NULL;
			m_res = resources::__internal::createResource((renderer::Texture*)0);
			m_mipmaps = mipmaps;
			m_only_main = false;
		}

		virtual int operator() ();

		resources::Resource* getResource() {
			return m_res;
		}

	protected :

		void loadFile();
		void fillTextures();

	private :

		//returns minimal container size in which val could be placed
		inline unsigned match_container(const unsigned val) const {
			return (val & 3) == 0 ? val : val + 4 - (3 & val);
		}

		EString			m_path;		//path to dds file
		State			m_state;	//texture loading state
		unsigned		m_lvl;		//current mipmap level
		DDSHeader		m_header;
		void*	m_data;		//pointer to a texture data allocated in heap
		void*	m_cur_ptr;  //pointer to a current mipmap level
		
		std::vector<renderer::CubeTextureSide::type> m_cube_sides; //contains names of presented sides if texture is a cubemap 
		size_t										 m_cube_disp; //for cubemap. displacement between two different nearest mips of the same level
		bool m_mipmaps;
		bool m_only_main;
		
		renderer::TextureType::type				m_tex_type;
		renderer::TextureInternalFormat::type	m_tex_int_type;
		renderer::TextureFormat::type			m_tex_fmt_type;

		renderer::Texture*		m_tex;
		resources::Resource*	m_res;
	};

}

#endif//DDSDRIVERINTERNAL_H_
