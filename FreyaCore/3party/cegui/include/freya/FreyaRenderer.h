/*
 * FreyaRenderer.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYARENDERER_H_
#define FREYARENDERER_H_

/*
 *
 */
#include "CEGUIRenderer.h"
#include "CEGUIMemory.h"

#include "CEGUIRenderingRoot.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"

#include "freya/FreyaTexture.h"
#include "freya/FreyaTextureTarget.h"
#include "freya/FreyaWindowTarget.h"
#include "freya/FreyaGeometryBuffer.h"

#include <vector>
#include "core/memory/MemoryArena.h"

#include "renderer.h"

namespace CEGUI
{

namespace freya
{

class FreyaRenderer : public CEGUI::Renderer, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaRenderer( );
	virtual ~FreyaRenderer( );

	virtual RenderingRoot& getDefaultRenderingRoot();
	virtual GeometryBuffer& createGeometryBuffer();
	virtual void destroyGeometryBuffer(const GeometryBuffer& buffer);
	virtual void destroyAllGeometryBuffers();
	virtual TextureTarget* createTextureTarget();
	virtual void destroyTextureTarget(TextureTarget* target);
	virtual void destroyAllTextureTargets();
	virtual Texture& createTexture();
	virtual Texture& createTexture(const String& filename, const String& resourceGroup);
	virtual Texture& createTexture(const Size& size);
	virtual void destroyTexture(Texture& texture);
	virtual void destroyAllTextures();
	virtual void beginRendering();
	virtual void endRendering();
	virtual void setDisplaySize(const Size& sz);
	virtual const Size& getDisplaySize() const;
	virtual const Vector2& getDisplayDPI() const;
	virtual uint getMaxTextureSize() const;
	virtual const String& getIdentifierString() const;

private:
	renderer::RenderingAPIDriver*			m_Rapi;
	Size									m_DisplaySize;
	RenderingRoot*							m_Root;
	RenderTarget*							m_DefaultTarget;

	renderer::Shader*						m_Shader;
	unsigned								m_SamplerLoc;

	typedef		std::vector<FreyaTexture*,core::memory::MemoryAllocator<FreyaTexture*> > Textures;
	typedef		std::vector<FreyaTextureTarget*,core::memory::MemoryAllocator<FreyaTextureTarget*> > TextureTargets;
	typedef		std::vector<FreyaGeometryBuffer*,core::memory::MemoryAllocator<FreyaGeometryBuffer*> > GeometryBuffers;

	Textures								m_Textures;
	TextureTargets							m_TextureTargets;
	GeometryBuffers							m_GeometryBuffers;

	math::matrix4x4				m_OldProjection;
	math::matrix4x4				m_OldView;
	math::matrix4x4				m_OldWorld;
};

}

}

#endif /* FREYARENDERER_H_ */
