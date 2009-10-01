/*
 * DDSDiver.cpp
 *
 *  Created on: 18.07.2009
 *      Author: vedenko
 */
#include "renderer/DriverSubsystems/Texture.h"
#include "core/EngineException.h"
#include "core/EngineCore.h"
#include "renderer/RenderingAPIDriver.h"
#include "core/filesystem/Filesystem.h"

namespace drivers {

enum _E_DDS_PixelFormat_Flags {
	UNCOMPRESSED,
	COMPRESSED,
	CONTAINS_ALPHA_DATA
};

enum _E_DDS_HeaderFlags {
	CAPS,
	HEIGHT,
	WIDTH,
	PITCH,
	PIXELFORMAT,
	MIPMAPCOUNT,
	LINEARSIZE,
	DEPTH
};
enum _E_DDS_CAPS1 {
	COMPLEX,
	MIPMAP,
	TEXTURE
};

enum _E_S3tc_version {
	DXT1,
	DXT2,
	DXT3,
	DXT4,
	DXT5
};

struct _S_BitMasks {
	unsigned int RMask;
	unsigned int GMask;
	unsigned int BMask;
	unsigned int AMask;
};

struct _S_DDS_PixelFormat{
	unsigned int mSize;			//structure size = 32bytes
	unsigned int mFlags;		//_E_DDS_Format_Flags
	unsigned int mFourCC;		//_E_S3tc_version
	unsigned int mBppCount;  	//bits per pixel
	_S_BitMasks  mBitMasks;     //
};//_S_DDS_PixelFormat

struct _S_DDS_Caps {
	unsigned int mCaps1;
	unsigned int mCaps2;
	unsigned int mCaps3;
	unsigned int mCaps4;
};//_S_DDS_Cups

struct _S_DDS_Header {
public:
	static const unsigned int header_size;

	unsigned int mSize;				//size of structure = 124bytes
	unsigned int mFlags;			//_E_DDS_HeaderFlags
	unsigned int mHeight;
	unsigned int mWidth;
	unsigned int mLinearSize;
	unsigned int mDepth;
	unsigned int mMipMapCount;
private:
	unsigned int __reserverd[11];
public:
	_S_DDS_PixelFormat mPixelFormat;
	_S_DDS_Caps mCaps;
private:
	unsigned int __reserver2;
};//struct _S_DDS_Header

//static member initialization
const unsigned int _S_DDS_Header::header_size = 124;

renderer::Texture* __sync_load_dds(const EString& path) throw(EngineException) {
	unsigned char* __file = reinterpret_cast<unsigned char*>(core::EngineCore::getFilesystem()->read(path));
	_S_DDS_Header* __header = reinterpret_cast<_S_DDS_Header*>(__file);
	renderer::Texture* __ret_tex;

	if(__header->mSize != _S_DDS_Header::header_size)
		throw EngineException();
	//checking valid flags
	if(!((__header->mFlags | HEIGHT) && (__header->mFlags | WIDTH) &&
		(__header->mFlags | CAPS) && (__header->mFlags | PIXELFORMAT)) &&
		(__header->mCaps.mCaps1 | TEXTURE))
		throw EngineException();

	__ret_tex = core::EngineCore::getRenderingDriver()->createTexture();
	return __ret_tex;
}

}// namespace drivers
