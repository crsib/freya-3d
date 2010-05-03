/* DDSDriverInternal.cpp
 * Created on: 28.04.2010
 *      Author: Sverchinskij
 */
#include "DDSDriverInternal.h"

#include "core/PluginCore.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"
#include "core/filesystem/Filesystem.h"

#include "core/memory/MemoryAllocator.h"
#include "resources/Resource.h"

#include <iostream>
#include <vector>

namespace resources
{
	namespace __internal
	{
		template<>
		resources::Resource* 	createResource(renderer::Texture*	resource)
		{
			resources::Resource* res = new resources::Resource;
			if(resource == NULL)
				return res;
			res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
			if(res->m_Resource == NULL)
				throw resources::ResourceException ("Failed to create resource");
			return res;
		}	

		template<>
		resources::Resource* 	setResource(Resource* res,renderer::Texture*	resource)
		{
			res->m_Resource = dynamic_cast<EngineSubsystem*>(resource);
			if(res->m_Resource == NULL)
				throw resources::ResourceException ("Failed to create resource");
			return res;
		}

	}
}

namespace dds_driver_internal {


	void DDSDriverAsyncLoader::loadFile() {
		unsigned char* file = reinterpret_cast<unsigned char*>(core::CoreInstance->getFilesystem()->read(m_path));
		//we believe that the data we request to exists
		unsigned int dds_magic = *reinterpret_cast<unsigned int*>(file);
		memcpy(&m_header, reinterpret_cast<unsigned char*>(file + sizeof(int)), sizeof(DDSHeader));
		bool ok = true;
		//First 4 bytes contains 0x20534444. Some checks to verify we've deal with dds...		
		ok &= (dds_magic == DDS_FOUR_CHARS_TO_DWORD('D', 'D', 'S', ' '));
		ok &= (m_header.size == sizeof(DDSHeader));
		ok &= (m_header.pf.size == sizeof(DDSPixelFormat));
		//oops
		if(!ok)
			throw(EngineException());
		//we realy interested in compressed textures
		if(!(m_header.pf.flags & FOURCC))
			throw(EngineException());
		switch(m_header.pf.fourcc) {
			case DXT3 :
				m_tex_int_type = renderer::TextureInternalFormat::RGBA_DXT3;
				break;
			case DXT5 :
				m_tex_int_type = renderer::TextureInternalFormat::RGBA_DXT5;
				break;
			default :
				throw(EngineException());
		};

		//if no mip levels presented DDSHeader::mipmap_count could contain any value.
		//1 means that only main surface(s) presented
		switch(m_mipmaps) {
		case true :
			if(!(m_header.caps & MIPMAP))
				throw(EngineException());
			break;
		case false :
			if(!(m_header.caps & MIPMAP))
				m_header.mipmap_count = 1;//anyway it neccessary to provide some calculates... 
			m_only_main = true;
			break;
		}
		
		//if(!(m_header.flags & LINEARSIZE))
			//linearsize field is not provided
			//m_header.linear_size = match_container(m_header.width) * match_container(m_header.height);

		if(m_header.caps2 & CUBEMAP) {
			unsigned w_i = m_header.width;
			unsigned h_i = m_header.height;
			for(unsigned i = 0; i < m_header.mipmap_count; i++) {
				unsigned diff = match_container(w_i) * match_container(h_i);
				m_cube_disp += diff;
				w_i >>= 1;
				h_i >>= 1;
				w_i += (w_i == 0);
				h_i += (h_i == 0);
			}

			m_tex_type = renderer::TextureType::TEXTURE_CUBE;
			
			if(m_header.caps2 & CUBEMAP_POSITIVE_X)
				m_cube_sides.push_back(renderer::CubeTextureSide::X_POSITIVE);
			if(m_header.caps2 & CUBEMAP_POSITIVE_Y)
				m_cube_sides.push_back(renderer::CubeTextureSide::Y_POSITIVE);
			if(m_header.caps2 & CUBEMAP_POSITIVE_Z)
				m_cube_sides.push_back(renderer::CubeTextureSide::Z_POSITIVE);
			if(m_header.caps2 & CUBEMAP_NEGATIVE_X)
				m_cube_sides.push_back(renderer::CubeTextureSide::X_NEGATIVE);
			if(m_header.caps2 & CUBEMAP_NEGATIVE_Y)
				m_cube_sides.push_back(renderer::CubeTextureSide::Y_NEGATIVE);
			if(m_header.caps2 & CUBEMAP_NEGATIVE_Z)
				m_cube_sides.push_back(renderer::CubeTextureSide::Z_NEGATIVE);
		}
		else
			m_tex_type = renderer::TextureType::TEXTURE_2D;

		//we've the right to suppose that remaining part of file is fully consist of the texture data
		size_t sz = (core::CoreInstance->getFilesystem()->fileSize(m_path)) - sizeof(int) - sizeof(DDSHeader);
		m_data = reinterpret_cast<unsigned char*>(core::memory::Allocate(sz, core::memory::GENERIC_POOL));
		memcpy(m_data, file + sizeof(int) + sizeof(DDSHeader), sz);
		m_cur_ptr = m_data;
		
		core::memory::Free(file,core::memory::GENERIC_POOL);
	}

	void DDSDriverAsyncLoader::fillTextures() {
		unsigned w = m_header.width >> m_lvl;
		unsigned h = m_header.height >> m_lvl;
		//set dim size to 1 if it equals to zero;
		w += (w == 0);
		h += (h == 0);
		switch(m_tex_type) {
		case renderer::TextureType::TEXTURE_CUBE :
			for(unsigned i = 0; i < m_cube_sides.size(); i++)
				m_tex->loadTexture(m_tex_type, m_lvl, m_tex_int_type, m_tex_fmt_type, renderer::TextureStorage::UNSIGNED_BYTE,
					w, h, m_cube_sides.at(i), m_cur_ptr + m_cube_disp*i);
			break;
		case renderer::TextureType::TEXTURE_2D : 
			m_tex->loadTexture(m_tex_type, m_lvl, m_tex_int_type, m_tex_fmt_type, renderer::TextureStorage::UNSIGNED_BYTE,
				w, h, m_cur_ptr);
			break;
		default :
			throw(EngineException());
		};
		//one mip layer uploaded. go back.
		//if((m_header.width & 3) != 0)
		//	std::cout << "ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ ÏÅ×ÅÍÜÊÈ" << std::endl;
		m_cur_ptr += match_container(m_header.width >> m_lvl) * match_container(m_header.height >> m_lvl);
		++m_lvl;

	}
	
	int DDSDriverAsyncLoader::operator() () {
		switch(m_state) {
		case LOADING :
			loadFile();
			//now texture data allocated in heap. we could start to send it into video memory.
			m_state = TEXTUREFILL;

			return DDSDriverAsyncLoader::MAIN_THREAD;
		case TEXTUREFILL :
			if(m_tex == NULL) {
				m_tex = core::CoreInstance->getRenderingDriver()->createTexture();
				m_res = resources::__internal::setResource(m_res, m_tex);
			}
			//ignore mipmaps
			if(m_only_main)
				fillTextures();
			//texture surfaces would be uploaded to accelerator by one mip level at a time.
			else if (m_lvl < m_header.mipmap_count) {
				fillTextures();
				return DDSDriverAsyncLoader::MAIN_THREAD;			
			}
			core::memory::Free(m_data, core::memory::GENERIC_POOL);
			resources::__internal::finalizeResource(m_res);
			return DDSDriverAsyncLoader::DONE;
		default :
			//kh.... smthing realy strange happened
			throw(EngineException());
		};
	}

}