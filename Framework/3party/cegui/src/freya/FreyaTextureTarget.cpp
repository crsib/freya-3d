#include "freya/FreyaTextureTarget.h"

namespace CEGUI
{
namespace freya
{

FreyaTextureTarget::FreyaTextureTarget()
{
	m_Fbo = m_Rapi->createFramebuffer();
	m_Texture = new FreyaTexture;
	m_Texture->setFreyaTexture(m_Rapi->createTexture(),0,0);
	//m_Texture->
	//m_Fbo->attachTexture(renderer::FramebufferAttachment::COLOR_ATTACHMENT0,m_Texture->getFreyaTexture());
	//m_Fbo->setDimensions(0,0);
	declareRenderSize(Size(128,128));
}

FreyaTextureTarget::~FreyaTextureTarget()
{
	m_Rapi->destroyFramebuffer(m_Fbo);
	delete m_Texture;
	//Texture is auto-freed;
}

bool
FreyaTextureTarget::isImageryCache() const
{
	return true;
}

void FreyaTextureTarget::declareRenderSize(const Size & sz)
{
	if ((m_Viewport.getWidth() >= sz.d_width) && (m_Viewport.getHeight() >=sz.d_height))
	        return;
	m_Texture->getFreyaTexture()->loadTexture(renderer::TextureType::TEXTURE_2D,0,renderer::TextureInternalFormat::RGBA8,renderer::TextureFormat::RGBA,renderer::TextureStorage::BYTE,static_cast<unsigned>(sz.d_width),static_cast<unsigned>(sz.d_height),NULL);
	//m_Texture->loadFromMemory(0,sz,Texture::PF_RGBA);

	//FreyaRenderTarget::setArea(Rect(m_Viewport.getPosition(), m_Texture->getSize()));
	FreyaRenderTarget::setArea(Rect(m_Viewport.getPosition(), sz));
	m_Texture->setFreyaTexture(m_Texture->getFreyaTexture(),static_cast<unsigned>(sz.d_width),static_cast<unsigned>(sz.d_height));

	//m_Fbo->setDimensions(static_cast<unsigned>(m_Texture->getSize().d_width),static_cast<unsigned>(m_Texture->getSize().d_height));
	m_Fbo->setDimensions(static_cast<unsigned>(sz.d_width),static_cast<unsigned>(sz.d_height));
	m_Fbo->attachTexture(renderer::FramebufferAttachment::COLOR_ATTACHMENT0,m_Texture->getFreyaTexture());
	if(!m_Fbo->status() == renderer::FramebufferStatus::FRAMEBUFFER_COMPLETE)
	{
		throw RendererException("CEGUI::FreyaTextureTarget - failed to resize target");
	}
	clear();
}

bool
FreyaTextureTarget::isRenderingInverted() const
{
	return true;
}

Texture &
FreyaTextureTarget::getTexture() const
{
	return *m_Texture;
}

void FreyaTextureTarget::deactivate()
{
	FreyaRenderTarget::deactivate();
	m_Fbo->unbind();
}

void FreyaTextureTarget::clear()
{
	m_Fbo->bind();
	m_Rapi->clearColorValue(0,0,0,0);
	m_Rapi->clearColor();
	m_Fbo->unbind();
}

void FreyaTextureTarget::activate()
{
	m_Fbo->bind();
	FreyaRenderTarget::activate();
}

}
}
