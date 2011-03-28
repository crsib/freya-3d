/*
 * FreyaTextureTarget.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYATEXTURETARGET_H_
#define FREYATEXTURETARGET_H_

/*
 *
 */
#include "FreyaRenderTarget.h"
#include "CEGUITextureTarget.h"
#include "CEGUIMemory.h"

#include "renderer/DriverSubsystems/Framebuffer.h"

#include "freya/FreyaTexture.h"

namespace CEGUI
{

namespace freya
{

class FreyaTextureTarget : public CEGUI::freya::FreyaRenderTarget, public CEGUI::TextureTarget, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaTextureTarget( );
	virtual ~FreyaTextureTarget( );
	virtual void activate();
	virtual void deactivate();
	// implementation of RenderTarget interface
	virtual bool isImageryCache() const;
	// implementation of TextureTarget interface
	virtual void clear();
	Texture& getTexture() const;
	virtual void declareRenderSize(const Size& sz);
	virtual bool isRenderingInverted() const;

private:
	renderer::Framebuffer*		m_Fbo;
	FreyaTexture*				m_Texture;
};

}

}

#endif /* FREYATEXTURETARGET_H_ */
