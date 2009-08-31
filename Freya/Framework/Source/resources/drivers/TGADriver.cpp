/*
 * TGADriver.cpp
 *
 *  Created on: 07.07.2009
 *      Author: vedenko
 */

#include "TGADriver.h"

#include <cstring>

#include "core/EngineCore.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"
#include "core/filesystem/Filesystem.h"

#include <vector>
#include "core/memory/MemoryAllocator.h"
#include "resources/ResourceFactory.h"
#include "resources/Resource.h"

#include "core/taskmanager/Task.h"
#include "core/taskmanager/TaskManager.h"
#include <cmath>
namespace resources
{

namespace drivers
{
//++++ sub-routines +++++++++ inherited from old class
#define max(a,b) (a >= b) ? a : b
#define min(a,b) (a <= b) ? a : b

using namespace std;

struct TGAHeader {
	unsigned char	IdLength;
	unsigned char	ColorMap;
	unsigned char	DataType;
	unsigned char	ColorMapInfo[5];
	unsigned char	X_Y_Origin[4];
	unsigned short	Width;
	unsigned short  Height;
	unsigned char	Bpp;
};

//++++++++ synchronous loader +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace __tga_sync_internal
{
void __calculateMipMap(unsigned level, unsigned width, unsigned height,void* memory,unsigned bpp,renderer::Texture* tex)
{
	unsigned w = width >> level;
	if(w == 0)
		w = 1;
	unsigned h = height >> level;
	if(h == 0)
		h = 1;
	//Ok, algorithm idea.
	//Consumptions: texture is a power of two one
	unsigned char* nmem = reinterpret_cast<unsigned char*> (core::memory::Allocate(bpp*w*h));
	//We sum blocks of size max(1 << level, w), max (1 << level ,h)
	unsigned wb = min((1u << level),width);
	unsigned hb = min((1u << level),height);
	//unsigned offset = 0;
	for(unsigned i = 0;i < w; i++)
		for(unsigned j = 0; j < h; j++)
		{

			for(unsigned b = 0;b < bpp;b++)
			{
				unsigned sum = 0;
				for(unsigned _x = i*wb;_x< (i+1)*wb;_x++)
					for(unsigned _y = j*hb;_y < (j+1)*hb;_y++)
					{
						sum += reinterpret_cast<unsigned char*>(memory)[_x*height*bpp + _y*bpp + b];
					}
				sum /= wb*hb;
				nmem[(i*h + j)*bpp + b] = sum;
			}
		}
	if(bpp == 3)
		tex->loadTexture(renderer::TextureType::TEXTURE_2D,level,renderer::TextureInternalFormat::RGB8,
				renderer::TextureFormat::RGB,renderer::TextureStorage::UNSIGNED_BYTE,
				w,h,nmem);
	else
		tex->loadTexture(renderer::TextureType::TEXTURE_2D,level,renderer::TextureInternalFormat::RGBA8,
				renderer::TextureFormat::RGBA,renderer::TextureStorage::UNSIGNED_BYTE,
				w,h,nmem);
	core::memory::Free(nmem);
}


renderer::Texture*	__load(const EString& path,bool mipMaps)
{
	unsigned char*	file = reinterpret_cast<unsigned char*> (core::EngineCore::getFilesystem()->read(path));
	unsigned char*  data = file + sizeof(TGAHeader);
	//BYTES per pixel
	TGAHeader head;
	::memcpy(&head,file,sizeof(TGAHeader));
	int Bpp = head.Bpp >> 3;
	unsigned char rgb[4];

	//Allocate enough memory
	unsigned char* mem = reinterpret_cast<unsigned char*> (core::memory::Allocate(Bpp*head.Width*head.Height));
	if(mem == NULL)
		throw EngineException();
	unsigned	n = 0; //Number of processed pixels

	if(head.DataType == 2) //Uncompressed
	{
		//Read block data
		while(n < static_cast<unsigned>(head.Width*head.Height))
		{
			::memcpy(rgb,data,Bpp);
			data+=Bpp;

			if(Bpp == 3)
			{
				mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
				mem[n*3 + 1] = rgb[1];
				mem[n*3 + 2] = rgb[0];
			}
			else
			{
				mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
				mem[n*4 + 1] = rgb[1];
				mem[n*4 + 2] = rgb[0];
				mem[n*4 + 3] = rgb[3];
			}

			n++;
		}

	}
	else if(head.DataType == 10) //RLE compressed
	{
		while(n < static_cast<unsigned>(head.Width*head.Height))
		{
			unsigned char chunkHead;
			chunkHead = *data;
			++data;
			bool isRLE = chunkHead & 128;
			unsigned numPix = (chunkHead & 127) + 1;

			if(isRLE)
			{
				::memcpy(rgb,data,Bpp);
				data+=Bpp;


				for(unsigned i = 0; i< numPix; i++) //Fill with pixels
				{
					if(Bpp == 3)
					{
						mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*3 + 1] = rgb[1];
						mem[n*3 + 2] = rgb[0];
					}
					else
					{
						mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*4 + 1] = rgb[1];
						mem[n*4 + 2] = rgb[0];
						mem[n*4 + 3] = rgb[3];
					}
					n++;
				}
			}
			else	//No rle compression
			{
				for(unsigned i = 0; i< numPix; i++) //Fill with pixels
				{
					::memcpy(rgb,data,Bpp);
					data+=Bpp;

					if(Bpp == 3)
					{
						mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*3 + 1] = rgb[1];
						mem[n*3 + 2] = rgb[0];
					}
					else
					{
						mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*4 + 1] = rgb[1];
						mem[n*4 + 2] = rgb[0];
						mem[n*4 + 3] = rgb[3];
					}
					n++;
				}

			}
		}
	}
	//Create texture now
	renderer::Texture* tex = core::EngineCore::getRenderingDriver()->createTexture();
	//Load main level.
	if(Bpp == 3)
		tex->loadTexture(renderer::TextureType::TEXTURE_2D,0,renderer::TextureInternalFormat::RGB8,
				renderer::TextureFormat::RGB,renderer::TextureStorage::UNSIGNED_BYTE,
				head.Width,head.Height,mem);
	else
		tex->loadTexture(renderer::TextureType::TEXTURE_2D,0,renderer::TextureInternalFormat::RGBA8,
				renderer::TextureFormat::RGBA,renderer::TextureStorage::UNSIGNED_BYTE,
				head.Width,head.Height,mem);
	//Clean up and return
	//Now, we need to   calculate mipmaps
	if(mipMaps)
	{
		unsigned m = max(head.Width,head.Height);
		unsigned lev = 1;
		while(m >> lev)
		{
			__calculateMipMap(lev++, head.Width,head.Height,mem,Bpp,tex);
		}
	}
	core::memory::Free(mem);
	core::memory::Free(file);
	return tex;
}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++ Asynchronous loader +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace __tga_async_internal
{
class ASyncTGALoader : public core::taskmanager::Task
{
public:
	ASyncTGALoader() : mode(LOADING),level(0)
	{

	}
	virtual int operator ()()
	{
		switch(mode)
		{
		case	LOADING:
		{
			unsigned char*	file = reinterpret_cast<unsigned char*> (core::EngineCore::getFilesystem()->read(path));
			unsigned char*  data = file + sizeof(TGAHeader);
			//BYTES per pixel
			TGAHeader head;
			::memcpy(&head,file,sizeof(TGAHeader));
			Bpp = head.Bpp >> 3;
			unsigned char rgb[4];
			width = head.Width;
			height = head.Height;
			//Allocate enough memory
			unsigned char* mem = reinterpret_cast<unsigned char*> (core::memory::Allocate(Bpp*head.Width*head.Height));
			if(mem == NULL)
				throw EngineException();
			unsigned	n = 0; //Number of processed pixels

			if(head.DataType == 2) //Uncompressed
			{
				//Read block data
				while(n < static_cast<unsigned>(head.Width*head.Height))
				{
					::memcpy(rgb,data,Bpp);
					data+=Bpp;

					if(Bpp == 3)
					{
						mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*3 + 1] = rgb[1];
						mem[n*3 + 2] = rgb[0];
					}
					else
					{
						mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
						mem[n*4 + 1] = rgb[1];
						mem[n*4 + 2] = rgb[0];
						mem[n*4 + 3] = rgb[3];
					}

					n++;
				}

			}
			else if(head.DataType == 10) //RLE compressed
			{
				while(n < static_cast<unsigned>(head.Width*head.Height))
				{
					unsigned char chunkHead;
					chunkHead = *data;
					++data;
					bool isRLE = chunkHead & 128;
					unsigned numPix = (chunkHead & 127) + 1;

					if(isRLE)
					{
						::memcpy(rgb,data,Bpp);
						data+=Bpp;


						for(unsigned i = 0; i< numPix; i++) //Fill with pixels
						{
							if(Bpp == 3)
							{
								mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
								mem[n*3 + 1] = rgb[1];
								mem[n*3 + 2] = rgb[0];
							}
							else
							{
								mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
								mem[n*4 + 1] = rgb[1];
								mem[n*4 + 2] = rgb[0];
								mem[n*4 + 3] = rgb[3];
							}
							n++;
						}
					}
					else	//No rle compression
					{
						for(unsigned i = 0; i< numPix; i++) //Fill with pixels
						{
							::memcpy(rgb,data,Bpp);
							data+=Bpp;

							if(Bpp == 3)
							{
								mem[n*3 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
								mem[n*3 + 1] = rgb[1];
								mem[n*3 + 2] = rgb[0];
							}
							else
							{
								mem[n*4 + 0] = rgb[2]; //Let us believe, that we are all under little endian machines
								mem[n*4 + 1] = rgb[1];
								mem[n*4 + 2] = rgb[0];
								mem[n*4 + 3] = rgb[3];
							}
							n++;
						}

					}
				}
			}
			memory = nmem = mem;
			mode = TEXTUREFILL;
			maxlevel = max(width,height);
			maxlevel = ceil(log2(maxlevel));
			w = width;
			h = height;
			return ASyncTGALoader::MAIN_THREAD;
		}
		break;
		case 	MIPMAP:
		{
			w = width >> level;
			if(w == 0)
				w = 1;
			h = height >> level;
			if(h == 0)
				h = 1;
			//Ok, algorithm idea.
			//Consumptions: texture is a power of two one
			nmem = reinterpret_cast<unsigned char*> (core::memory::Allocate(Bpp*w*h));
			//We sum blocks of size max(1 << level, w), max (1 << level ,h)
			unsigned wb = min((1u << level),width);
			unsigned hb = min((1u << level),height);
			//unsigned offset = 0;
			for(unsigned i = 0;i < w; i++)
				for(unsigned j = 0; j < h; j++)
				{

					for(unsigned b = 0;b < Bpp;b++)
					{
						unsigned sum = 0;
						for(unsigned _x = i*wb;_x< (i+1)*wb;_x++)
							for(unsigned _y = j*hb;_y < (j+1)*hb;_y++)
							{
								sum += reinterpret_cast<unsigned char*>(memory)[_x*height*Bpp + _y*Bpp + b];
							}
						sum /= wb*hb;
						nmem[(i*h + j)*Bpp + b] = sum;
					}
				}
			mode = TEXTUREFILL;
			return ASyncTGALoader::MAIN_THREAD;
		}
		break;
		case	TEXTUREFILL:
		{
			if(level <= maxlevel)
			{
				if(Bpp == 3)
					tex->loadTexture(renderer::TextureType::TEXTURE_2D,level,renderer::TextureInternalFormat::RGB8,
							renderer::TextureFormat::RGB,renderer::TextureStorage::UNSIGNED_BYTE,
							w,h,nmem);
				else
					tex->loadTexture(renderer::TextureType::TEXTURE_2D,level,renderer::TextureInternalFormat::RGBA8,
							renderer::TextureFormat::RGBA,renderer::TextureStorage::UNSIGNED_BYTE,
							w,h,nmem);
				if(level > 0)
					core::memory::Free(nmem);
				level++;
				mode = MIPMAP;
				if(level <= maxlevel)
					return ASyncTGALoader::SECONDARY_THREAD;
			}
		}
		break;
		}
		core::memory::Free(memory);
		resources::__internal::finalizeResource(res);
		return ASyncTGALoader::DONE;
	}

	enum Mode
	{
		LOADING,MIPMAP,TEXTUREFILL
	};
	Mode mode;
	unsigned maxlevel;
	unsigned level;
	void*	 memory;
	unsigned char*	 nmem;
	unsigned width,w;
	unsigned height,h;
	unsigned Bpp;
	renderer::Texture* tex;
	EString path;
	bool mipMaps;
	resources::Resource* res;
};
}

TGADriver::TGADriver()
{

}

TGADriver::~TGADriver()
{

}

bool	TGADriver::unique() const
{
	return true;
}

EString TGADriver::id() const
{
	return "tga";
}

Resource*	TGADriver::loadSynchronous(const EString& ID)
{
	//we trully have the :tga: in front, as the driver is never called directly
	EString IDch = ID.substr(5);
	bool mipMaps = false;
	size_t nmaps = IDch.find("mipmaps");
	if(nmaps != EString::npos)
	{
		if(nmaps == 0)
		{
			mipMaps = true;
			IDch = IDch.substr(8);
		}
		else
		{
			if(IDch[nmaps-1] == ':')
			{
				mipMaps = true;
				IDch = IDch.substr(0,nmaps-1);
			}
		}
	}
	if(IDch.find(':') != EString::npos)
		throw resources::ResourceException("Malformed resource ID");
	renderer::Texture* tex;
	try
	{
		tex = __tga_sync_internal::__load(IDch,mipMaps);
	}
	catch(::EngineException& ex)
	{
		throw resources::ResourceException(EString("Failed to load resource: ") + ex.message());
	}
	catch(...)
	{
		throw resources::ResourceException("Unknown exception");
	}
	resources::Resource *res = resources::__internal::createResource(tex);
	resources::__internal::finalizeResource(res);
	return res;
}

Resource*	TGADriver::loadAsynchronous(const EString& ID)
{
	//we trully have the :tga: in front, as the driver is never called directly
	EString IDch = ID.substr(5);
	bool mipMaps = false;
	size_t nmaps = IDch.find("mipmaps");
	if(nmaps != EString::npos)
	{
		if(nmaps == 0)
		{
			mipMaps = true;
			IDch = IDch.substr(8);
		}
		else
		{
			if(IDch[nmaps-1] == ':')
			{
				mipMaps = true;
				IDch = IDch.substr(0,nmaps-1);
			}
		}
	}
	if(IDch.find(':') != EString::npos)
		throw resources::ResourceException("Malformed resource ID");
	renderer::Texture* tex = core::EngineCore::getRenderingDriver()->createTexture();
	__tga_async_internal::ASyncTGALoader*	loader = new __tga_async_internal::ASyncTGALoader;
	loader->res = resources::__internal::createResource(tex);
	loader->tex = tex;
	loader->mipMaps = mipMaps;
	loader->path = IDch;
	core::EngineCore::getTaskManager()->addAsynchronousTask(loader);
	return loader->res;
}

void 		TGADriver::destroy(Resource* res)
{
	renderer::Texture* tex = res->get<renderer::Texture*>();
	core::EngineCore::getRenderingDriver()->destroyTexture(tex);
	resources::__internal::destroyResource(res);
}

}

}