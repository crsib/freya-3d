/*
 * FreyaTexture.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYATEXTURE_H_
#define FREYATEXTURE_H_

/*
 *
 */
#include "CEGUITexture.h"
#include "CEGUIMemory.h"

#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/Texture.h"
#include "core/EngineCore.h"

#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUIImageCodec.h"

namespace CEGUI
{

namespace freya
{

class FreyaTexture : public CEGUI::Texture, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaTexture( );
	virtual ~FreyaTexture( );
	virtual const Size& getSize() const;
	virtual const Size& getOriginalDataSize() const;
	virtual const Vector2& getTexelScaling() const;
	virtual void loadFromFile(const String& filename, const String& resourceGroup);
	virtual void loadFromMemory(const void* buffer, const Size& buffer_size,
	                        PixelFormat pixel_format);
	virtual void saveToMemory(void* buffer);

	renderer::Texture*		getFreyaTexture();
	void					setFreyaTexture(renderer::Texture*	tex,size_t w,size_t h);
private:
	Size					m_TextureSize;
	Size					m_DataSize;
	renderer::Texture*		m_Texture;
	Vector2					m_Scaling;
};

}

}

#endif /* FREYATEXTURE_H_ */
